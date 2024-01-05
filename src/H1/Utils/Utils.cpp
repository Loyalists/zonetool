#include <stdafx.hpp>
#include "Utils.hpp"

#include <immintrin.h>

namespace PackedVec
{
#define _BYTE  uint8_t
#define _WORD  uint16_t
#define _DWORD uint32_t
#define _QWORD uint64_t

#define LOBYTE(x)   (*((_BYTE*)&(x)))   // low byte
#define LOWORD(x)   (*((_WORD*)&(x)))   // low word
#define LODWORD(x)  (*((_DWORD*)&(x)))  // low dword
#define HIBYTE(x)   (*((_BYTE*)&(x)+1))
#define HIWORD(x)   (*((_WORD*)&(x)+1))
#define HIDWORD(x)  (*((_DWORD*)&(x)+1))
#define BYTEn(x, n)   (*((_BYTE*)&(x)+n))
#define WORDn(x, n)   (*((_WORD*)&(x)+n))
#define BYTE1(x)   BYTEn(x,  1)         // byte 1 (counting from 0)
#define BYTE2(x)   BYTEn(x,  2)

	uint32_t Vec2PackTexCoords(float* in)
	{
		__m128 xmm0 = _mm_loadu_ps(in);
		__m128i xmmi0 = _mm_cvtps_ph(xmm0, 3);
		uint32_t result = _mm_cvtsi128_si32(xmmi0);
		return result;
	}

	void Vec2UnpackTexCoords(const uint32_t in, float* out) // iw5 func
	{
		uint32_t val;

		if (LOWORD(in))
			val = ((LOWORD(in) & 0x8000) << 16) | (((((in & 0x3FFF) << 14) - (~(LOWORD(in) << 14) & 0x10000000)) ^ 0x80000001) >> 1);
		else
			val = 0;

		out[0] = *reinterpret_cast<float*>(&val);

		if (HIWORD(in))
			val = ((HIWORD(in) & 0x8000) << 16) | (((((HIWORD(in) & 0x3FFF) << 14)
				- (~(HIWORD(in) << 14) & 0x10000000)) ^ 0x80000001) >> 1);
		else
			val = 0;

		out[1] = *reinterpret_cast<float*>(&val);
	}

	uint32_t Vec3PackUnitVec(float* in) // h1 func
	{
		uint32_t bits;

		bits = ((uint32_t)floor(((((fmaxf(-1.0f, fminf(1.0f, in[2])) + 1.0f) * 0.5f) * 1023.0f) + 0.5f)) | 0xFFFFFC00) << 10;
		bits = ((uint32_t)floor(((((fmaxf(-1.0f, fminf(1.0f, in[1])) + 1.0f) * 0.5f) * 1023.0f) + 0.5f)) | bits) << 10;
		bits = ((uint32_t)floor(((((fmaxf(-1.0f, fminf(1.0f, in[0])) + 1.0f) * 0.5f) * 1023.0f) + 0.5f)) | bits);

		return bits;
	}

	uint32_t Vec3PackUnitVecWithAlpha(float* in, float alpha) // h1 func
	{
		uint32_t bits;

		bits = ((uint32_t)floor(((((fmaxf(-1.0f, fminf(1.0f, alpha)) + 1.0f) * 0.5f) * 1023.0f) + 0.5f)) | 0xFFFFFC00) << 10;
		bits = ((uint32_t)floor(((((fmaxf(-1.0f, fminf(1.0f, in[2])) + 1.0f) * 0.5f) * 1023.0f) + 0.5f)) | bits) << 10;
		bits = ((uint32_t)floor(((((fmaxf(-1.0f, fminf(1.0f, in[1])) + 1.0f) * 0.5f) * 1023.0f) + 0.5f)) | bits) << 10;
		bits = ((uint32_t)floor(((((fmaxf(-1.0f, fminf(1.0f, in[0])) + 1.0f) * 0.5f) * 1023.0f) + 0.5f)) | bits);

		return bits;
	}

	void Vec3UnpackUnitVec(const uint8_t* in, float* out) // t6 func
	{
		float decodeScale;

		decodeScale = (in[3] - -192.0f) / 32385.0f;
		out[0] = (in[0] - 127.0f) * decodeScale;
		out[1] = (in[1] - 127.0f) * decodeScale;
		out[2] = (in[2] - 127.0f) * decodeScale;
	}
}