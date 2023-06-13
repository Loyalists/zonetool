#include "stdafx.hpp"
#include "H1/Assets/XModel.hpp"
#include "H1/Assets/XSurface.hpp"

namespace ZoneTool
{
	namespace
	{
		namespace PackedShit
		{
			using namespace IW3;

#define _BYTE uint8_t
#define _WORD uint16_t
#define _DWORD uint32_t
#define _QWORD uint64_t

#define LOBYTE(x) (*((_BYTE *)&(x)))   // low byte
#define LOWORD(x) (*((_WORD *)&(x)))   // low word
#define LODWORD(x) (*((_DWORD *)&(x))) // low dword
#define HIBYTE(x) (*((_BYTE *)&(x) + 1))
#define HIWORD(x) (*((_WORD *)&(x) + 1))
#define HIDWORD(x) (*((_DWORD *)&(x) + 1))
#define BYTEn(x, n) (*((_BYTE *)&(x) + n))
#define WORDn(x, n) (*((_WORD *)&(x) + n))
#define BYTE1(x) BYTEn(x, 1) // byte 1 (counting from 0)
#define BYTE2(x) BYTEn(x, 2)

			PackedTexCoords Vec2PackTexCoords(float* in)
			{
				/*int v2; // eax
				int v3; // esi
				int v4; // eax
				int v5; // ecx
				PackedTexCoords result; // eax
				int v7; // [esp+8h] [ebp+8h]
				int v8; // [esp+8h] [ebp+8h]

				v7 = LODWORD(in[0]);
				v2 = (int)((2 * v7) ^ 0x80003FFF) >> 14;
				if (v2 < 0x3FFF)
				{
					if (v2 <= -16384)
						LOWORD(v2) = -16384;
				}
				else
				{
					LOWORD(v2) = 0x3FFF;
				}
				v3 = (v7 >> 16) & 0xC000 | v2 & 0x3FFF;
				v8 = LODWORD(in[1]);
				v4 = (int)((2 * v8) ^ 0x80003FFF) >> 14;
				v5 = (v8 >> 16) & 0xC000;
				if (v4 < 0x3FFF)
				{
					if (v4 <= -16384)
						LOWORD(v4) = -16384;
					result.packed = v3 + ((v5 | v4 & 0x3FFF) << 16);
				}
				else
				{
					result.packed = v3 + ((v5 | 0x3FFF) << 16);
				}
				return result;*/

				__m128 xmm0 = _mm_loadu_ps(in);
				__m128i xmmi0 = _mm_cvtps_ph(xmm0, 3);
				uint32_t result = _mm_cvtsi128_si32(xmmi0);
				return { result };
			}

			void Vec2UnpackTexCoords(const PackedTexCoords in, float* out) // iw5 func
			{
				unsigned int val;

				if (LOWORD(in.packed))
					val = ((LOWORD(in.packed) & 0x8000) << 16) | (((((in.packed & 0x3FFF) << 14) - (~(LOWORD(in.packed) << 14) & 0x10000000)) ^ 0x80000001) >> 1);
				else
					val = 0;

				out[0] = *reinterpret_cast<float*>(&val);

				if (HIWORD(in.packed))
					val = ((HIWORD(in.packed) & 0x8000) << 16) | (((((HIWORD(in.packed) & 0x3FFF) << 14)
						- (~(HIWORD(in.packed) << 14) & 0x10000000)) ^ 0x80000001) >> 1);
				else
					val = 0;

				out[1] = *reinterpret_cast<float*>(&val);
			}

			PackedUnitVec Vec3PackUnitVec(float* in) // h1 func
			{
				unsigned int bits;

				bits = ((unsigned int)floor(((((fmaxf(-1.0f, fminf(1.0f, in[2])) + 1.0f) * 0.5f) * 1023.0f) + 0.5f)) | 0xFFFFFC00) << 10;
				bits = ((unsigned int)floor(((((fmaxf(-1.0f, fminf(1.0f, in[1])) + 1.0f) * 0.5f) * 1023.0f) + 0.5f)) | bits) << 10;
				bits = ((unsigned int)floor(((((fmaxf(-1.0f, fminf(1.0f, in[0])) + 1.0f) * 0.5f) * 1023.0f) + 0.5f)) | bits);

				return { bits };
			}

			PackedUnitVec Vec3PackUnitVecWithAlpha(float* in, float alpha) // h1 func
			{
				unsigned int bits;

				bits = ((unsigned int)floor(((((fmaxf(-1.0f, fminf(1.0f, alpha)) + 1.0f) * 0.5f) * 1023.0f) + 0.5f)) | 0xFFFFFC00) << 10;
				bits = ((unsigned int)floor(((((fmaxf(-1.0f, fminf(1.0f, in[2])) + 1.0f) * 0.5f) * 1023.0f) + 0.5f)) | bits) << 10;
				bits = ((unsigned int)floor(((((fmaxf(-1.0f, fminf(1.0f, in[1])) + 1.0f) * 0.5f) * 1023.0f) + 0.5f)) | bits) << 10;
				bits = ((unsigned int)floor(((((fmaxf(-1.0f, fminf(1.0f, in[0])) + 1.0f) * 0.5f) * 1023.0f) + 0.5f)) | bits);

				return { bits };
			}

			void Vec3UnpackUnitVec(const PackedUnitVec in, float *out) // t6 func
			{
				float decodeScale;

				decodeScale = (in.array[3] - -192.0f) / 32385.0f;
				out[0] = (in.array[0] - 127.0f) * decodeScale;
				out[1] = (in.array[1] - 127.0f) * decodeScale;
				out[2] = (in.array[2] - 127.0f) * decodeScale;
			}
		}
	}

	namespace IW3
	{
		void GenerateH1BlendVertsShit(H1::XSurface *surf)
		{
			unsigned short a = 0;
			unsigned short b = 0;
			unsigned short index = 1;
			for (short s = 0; s < (surf->blendVertCounts[0]); s++)
			{
				surf->blendVertsTable[a].b[0] = surf->blendVerts[b + 0] / 64;
				surf->blendVertsTable[a].b[1] = 0;
				surf->blendVertsTable[a].b[2] = 0;
				surf->blendVertsTable[a].b[3] = 0;
				surf->blendVertsTable[a].b[4] = 0;
				surf->blendVertsTable[a].b[5] = 0;
				surf->blendVertsTable[a].b[6] = 0;
				surf->blendVertsTable[a].b[7] = 0;

				surf->blendVertsTable[a].b[8] = 0;
				surf->blendVertsTable[a].b[9] = 0;
				surf->blendVertsTable[a].b[10] = 0;
				surf->blendVertsTable[a].b[11] = 0;
				surf->blendVertsTable[a].b[12] = 0;
				surf->blendVertsTable[a].b[13] = 0;
				surf->blendVertsTable[a].b[14] = 0;

				surf->blendVertsTable[a].blendVertCountIndex = index;

				a++;
				b += 1;
			}
			index++;

			for (short s = 0; s < (surf->blendVertCounts[1]); s++)
			{
				surf->blendVertsTable[a].b[0] = surf->blendVerts[b + 0] / 64;
				surf->blendVertsTable[a].b[1] = surf->blendVerts[b + 1] / 64;
				surf->blendVertsTable[a].b[2] = 0;
				surf->blendVertsTable[a].b[3] = 0;
				surf->blendVertsTable[a].b[4] = 0;
				surf->blendVertsTable[a].b[5] = 0;
				surf->blendVertsTable[a].b[6] = 0;
				surf->blendVertsTable[a].b[7] = 0;

				surf->blendVertsTable[a].b[8] = surf->blendVerts[b + 2];
				surf->blendVertsTable[a].b[9] = 0;
				surf->blendVertsTable[a].b[10] = 0;
				surf->blendVertsTable[a].b[11] = 0;
				surf->blendVertsTable[a].b[12] = 0;
				surf->blendVertsTable[a].b[13] = 0;
				surf->blendVertsTable[a].b[14] = 0;

				surf->blendVertsTable[a].blendVertCountIndex = index;

				a++;
				b += 3;
			}
			index++;

			for (short s = 0; s < (surf->blendVertCounts[2]); s++)
			{
				surf->blendVertsTable[a].b[0] = surf->blendVerts[b + 0] / 64;
				surf->blendVertsTable[a].b[1] = surf->blendVerts[b + 1] / 64;
				surf->blendVertsTable[a].b[2] = surf->blendVerts[b + 3] / 64;
				surf->blendVertsTable[a].b[3] = 0;
				surf->blendVertsTable[a].b[4] = 0;
				surf->blendVertsTable[a].b[5] = 0;
				surf->blendVertsTable[a].b[6] = 0;
				surf->blendVertsTable[a].b[7] = 0;

				surf->blendVertsTable[a].b[8] = surf->blendVerts[b + 2];
				surf->blendVertsTable[a].b[9] = surf->blendVerts[b + 4];
				surf->blendVertsTable[a].b[10] = 0;
				surf->blendVertsTable[a].b[11] = 0;
				surf->blendVertsTable[a].b[12] = 0;
				surf->blendVertsTable[a].b[13] = 0;
				surf->blendVertsTable[a].b[14] = 0;

				surf->blendVertsTable[a].blendVertCountIndex = index;

				a++;
				b += 5;
			}
			index++;

			for (short s = 0; s < (surf->blendVertCounts[3]); s++)
			{
				surf->blendVertsTable[a].b[0] = surf->blendVerts[b + 0] / 64;
				surf->blendVertsTable[a].b[1] = surf->blendVerts[b + 1] / 64;
				surf->blendVertsTable[a].b[2] = surf->blendVerts[b + 3] / 64;
				surf->blendVertsTable[a].b[3] = surf->blendVerts[b + 5] / 64;
				surf->blendVertsTable[a].b[4] = 0;
				surf->blendVertsTable[a].b[5] = 0;
				surf->blendVertsTable[a].b[6] = 0;
				surf->blendVertsTable[a].b[7] = 0;

				surf->blendVertsTable[a].b[8] = surf->blendVerts[b + 2];
				surf->blendVertsTable[a].b[9] = surf->blendVerts[b + 4];
				surf->blendVertsTable[a].b[10] = surf->blendVerts[b + 6];
				surf->blendVertsTable[a].b[11] = 0;
				surf->blendVertsTable[a].b[12] = 0;
				surf->blendVertsTable[a].b[13] = 0;
				surf->blendVertsTable[a].b[14] = 0;

				surf->blendVertsTable[a].blendVertCountIndex = index;

				a++;
				b += 7;
			}
			index++;
		}

		void PrepareVertexWeights(H1::XSurface* asset)
		{
			// from: https://github.com/Scobalula/Greyhound/blob/15641dae5383190e43b2396d12b8868723735917/src/WraithXCOD/WraithXCOD/CoDXModelTranslator.cpp#L577
			// The index of read weight data
			uint32_t WeightDataIndex = 0;
			int blendVertsTotal = asset->blendVertCounts[0] + asset->blendVertCounts[1] + asset->blendVertCounts[2] + asset->blendVertCounts[3];
			auto blendVerts = asset->blendVerts;
			int currentPosition = 0;
			struct WeightsData
			{
				unsigned short BoneValues[4];
				unsigned short WeightValues[4];
				uint8_t WeightCount;
			};

			std::vector<WeightsData> Weights = std::vector<WeightsData>(asset->vertCount);
			// ZONETOOL_INFO("vertCount: %d", asset->vertCount);
			// ZONETOOL_INFO("blendVertsTotal: %d", blendVertsTotal);
			// ZONETOOL_INFO("rigidVertListCount: %d", asset->rigidVertListCount);

			// Prepare the simple, rigid weights
			for (uint32_t i = 0; i < asset->rigidVertListCount; i++)
			{
				// Simple weights build, rigid, just apply the proper bone id
				uint32_t VertexCount = 0;
				uint32_t BoneIndex = 0;

				// Read rigid struct, QS does not have the pointer
				auto RigidInfo = asset->rigidVertLists;
				VertexCount = RigidInfo[i].vertCount;
				BoneIndex = RigidInfo[i].boneOffset / 64;
				// ZONETOOL_INFO("VertexCount: %d", VertexCount);
				// ZONETOOL_INFO("BoneIndex: %d", BoneIndex);

				// Apply bone ids properly
				for (uint32_t w = 0; w < VertexCount; w++)
				{
					if (WeightDataIndex >= asset->vertCount)
					{
						// how could this even happen
						break;
					}
					Weights[WeightDataIndex].WeightCount = 1;
					// Apply
					Weights[WeightDataIndex].BoneValues[0] = BoneIndex;
					Weights[WeightDataIndex].WeightValues[0] = 65536;
					// Advance
					WeightDataIndex++;
				}
			}

			// Prepare single bone weights
			for (uint32_t w = 0; w < asset->blendVertCounts[0]; w++)
			{
				Weights[WeightDataIndex].WeightCount = 1;
				// Apply
				Weights[WeightDataIndex].BoneValues[0] = (blendVerts[currentPosition++] / 64);
				Weights[WeightDataIndex].WeightValues[0] = 65536;
				// Advance
				WeightDataIndex++;
			}

			// Prepare two bone weights
			for (uint32_t w = 0; w < asset->blendVertCounts[1]; w++)
			{
				// Set size
				Weights[WeightDataIndex].WeightCount = 2;

				// Read IDs (1, 2)
				Weights[WeightDataIndex].BoneValues[0] = (blendVerts[currentPosition++] / 64);
				Weights[WeightDataIndex].BoneValues[1] = (blendVerts[currentPosition++] / 64);
				// Read value for 2 and calculate 1
				Weights[WeightDataIndex].WeightValues[1] = blendVerts[currentPosition++];
				Weights[WeightDataIndex].WeightValues[0] = (65536 - Weights[WeightDataIndex].WeightValues[1]);

				// Advance
				WeightDataIndex++;
			}

			// Prepare three bone weights
			for (uint32_t w = 0; w < asset->blendVertCounts[2]; w++)
			{
				// Set size
				Weights[WeightDataIndex].WeightCount = 3;

				// Read 2 IDs (1, 2)
				Weights[WeightDataIndex].BoneValues[0] = (blendVerts[currentPosition++] / 64);
				Weights[WeightDataIndex].BoneValues[1] = (blendVerts[currentPosition++] / 64);
				// Read value for 2
				Weights[WeightDataIndex].WeightValues[1] = blendVerts[currentPosition++];
				// Read 1 ID (3)
				Weights[WeightDataIndex].BoneValues[2] = (blendVerts[currentPosition++] / 64);
				// Read value for 3
				Weights[WeightDataIndex].WeightValues[2] = blendVerts[currentPosition++];
				// Calculate first value
				Weights[WeightDataIndex].WeightValues[0] = (65536 - (Weights[WeightDataIndex].WeightValues[1] + Weights[WeightDataIndex].WeightValues[2]));

				// Advance
				WeightDataIndex++;
			}

			// Prepare four bone weights
			for (uint32_t w = 0; w < asset->blendVertCounts[3]; w++)
			{
				// Set size
				Weights[WeightDataIndex].WeightCount = 4;

				// Read 2 IDs (1, 2)
				Weights[WeightDataIndex].BoneValues[0] = (blendVerts[currentPosition++] / 64);
				Weights[WeightDataIndex].BoneValues[1] = (blendVerts[currentPosition++] / 64);
				// Read value for 2
				Weights[WeightDataIndex].WeightValues[1] = blendVerts[currentPosition++];
				// Read 1 ID (3)
				Weights[WeightDataIndex].BoneValues[2] = (blendVerts[currentPosition++] / 64);
				// Read value for 3
				Weights[WeightDataIndex].WeightValues[2] = blendVerts[currentPosition++];
				// Read 1 ID (4)
				Weights[WeightDataIndex].BoneValues[3] = (blendVerts[currentPosition++] / 64);
				// Read value for 4
				Weights[WeightDataIndex].WeightValues[3] = blendVerts[currentPosition++];
				// Calculate first value
				Weights[WeightDataIndex].WeightValues[0] = (65536 - (Weights[WeightDataIndex].WeightValues[1] + Weights[WeightDataIndex].WeightValues[2] + Weights[WeightDataIndex].WeightValues[3]));

				// Advance
				WeightDataIndex++;
			}

			auto blendVertsTable = asset->blendVertsTable;
			for (uint32_t i = 0; i < asset->vertCount; i++)
			{
				blendVertsTable[i].blendVertCountIndex = Weights[i].WeightCount;
				for (uint32_t bonePos = 0; bonePos < Weights[i].WeightCount; bonePos++)
				{
					blendVertsTable[i].b[bonePos] = Weights[i].BoneValues[bonePos];
					// the first weight is to be computed so fall back
					uint32_t weightPos = bonePos + 8 - 1;
					if (bonePos != 0)
					{
						blendVertsTable[i].b[weightPos] = Weights[i].WeightValues[bonePos];
					}
				}
			}
		}

		void GenerateH1XSurface(H1::XSurface *h1_asset, XSurface *asset, ZoneMemory *mem)
		{
			h1_asset->flags = asset->tileMode;
			h1_asset->flags |= asset->deformed ? H1::SURF_FLAG_SKINNED : 0;
			// h1_asset->flags |= H1::SURF_FLAG_VERTCOL_NONE;

			h1_asset->vertCount = asset->vertCount;
			h1_asset->triCount = asset->triCount;
			h1_asset->rigidVertListCount = asset->vertListCount;

			// blend verts
			memcpy(&h1_asset->blendVertCounts, &asset->vertInfo.vertCount, sizeof(asset->vertInfo.vertCount));
			h1_asset->blendVerts = reinterpret_cast<unsigned short *__ptr64>(asset->vertInfo.vertsBlend);

			h1_asset->blendVertsTable = mem->Alloc<H1::BlendVertsUnknown>(asset->vertCount);
			//GenerateH1BlendVertsShit(h1_asset);

			// triIndices
			h1_asset->triIndices = reinterpret_cast<H1::Face *__ptr64>(asset->triIndices); // this is draw indices?
			h1_asset->triIndices2 = mem->Alloc<H1::Face>(asset->triCount);				   // this is collision indices?
			for (unsigned short i = 0; i < asset->triCount; i++)
			{
				memcpy(&h1_asset->triIndices2[i], &h1_asset->triIndices[i], sizeof(H1::Face));
			}

			// verts
			// h1_asset->verts0.packedVerts0 = reinterpret_cast<IW6::GfxPackedVertex* __ptr64>(asset->verticies);
			h1_asset->verts0.packedVerts0 = mem->Alloc<H1::GfxPackedVertex>(asset->vertCount);
			for (unsigned short i = 0; i < asset->vertCount; i++)
			{
				memcpy(&h1_asset->verts0.packedVerts0[i], &asset->verts0[i], sizeof(IW3::GfxPackedVertex));

				float texCoord_unpacked[2]{ 0.0f, 0.0f };
				PackedShit::Vec2UnpackTexCoords(asset->verts0[i].texCoord, texCoord_unpacked);
				std::swap(texCoord_unpacked[0], texCoord_unpacked[1]); // these are inverted...
				h1_asset->verts0.packedVerts0[i].texCoord.packed = PackedShit::Vec2PackTexCoords(texCoord_unpacked).packed;

				// re-calculate these...
				float normal_unpacked[3]{ 0.0f, 0.0f, 0.0f };
				PackedShit::Vec3UnpackUnitVec(asset->verts0[i].normal, normal_unpacked);

				float tangent_unpacked[3]{ 0.0f, 0.0f, 0.0f };
				PackedShit::Vec3UnpackUnitVec(asset->verts0[i].tangent, tangent_unpacked);

				float normal[3] = { normal_unpacked[0], normal_unpacked[1], normal_unpacked[2] };
				float tangent[3] = { tangent_unpacked[0], tangent_unpacked[1], tangent_unpacked[2] };

				float sign = 0.0f;
				if (asset->verts0[i].binormalSign == -1.0f)
				{
					sign = 1.0f;
				}

				h1_asset->verts0.packedVerts0[i].normal.packed = PackedShit::Vec3PackUnitVecWithAlpha(normal, 1.0f).packed;
				h1_asset->verts0.packedVerts0[i].tangent.packed = PackedShit::Vec3PackUnitVecWithAlpha(tangent, sign).packed;

				// correct color : bgra->rgba
				h1_asset->verts0.packedVerts0[i].color.array[0] = asset->verts0[i].color.array[2];
				h1_asset->verts0.packedVerts0[i].color.array[1] = asset->verts0[i].color.array[1];
				h1_asset->verts0.packedVerts0[i].color.array[2] = asset->verts0[i].color.array[0];
				h1_asset->verts0.packedVerts0[i].color.array[3] = asset->verts0[i].color.array[3];
			}

			// unknown
			h1_asset->unknown0 = mem->Alloc<H1::UnknownXSurface0>(asset->vertCount); // related to indices2?
			for (unsigned short i = 0; i < asset->vertCount; i++)
			{
				h1_asset->unknown0[i].xyz[0] = h1_asset->verts0.packedVerts0[i].xyz[0];
				h1_asset->unknown0[i].xyz[1] = h1_asset->verts0.packedVerts0[i].xyz[1];
				h1_asset->unknown0[i].xyz[2] = h1_asset->verts0.packedVerts0[i].xyz[2];
				h1_asset->unknown0[i].normal = h1_asset->verts0.packedVerts0[i].normal;
			}

			// rigidVertLists
			h1_asset->rigidVertLists = mem->Alloc<H1::XRigidVertList>(asset->vertListCount);
			for (int i = 0; i < asset->vertListCount; i++)
			{
				h1_asset->rigidVertLists[i].boneOffset = asset->vertList[i].boneOffset;
				h1_asset->rigidVertLists[i].vertCount = asset->vertList[i].vertCount;
				h1_asset->rigidVertLists[i].triOffset = asset->vertList[i].triOffset;
				h1_asset->rigidVertLists[i].triCount = asset->vertList[i].triCount;

				if (asset->vertList[i].collisionTree)
				{
					h1_asset->rigidVertLists[i].collisionTree = mem->Alloc<H1::XSurfaceCollisionTree>();
					memcpy(&h1_asset->rigidVertLists[i].collisionTree->trans, &asset->vertList[i].collisionTree->trans,
						   sizeof(asset->vertList[i].collisionTree->trans));
					memcpy(&h1_asset->rigidVertLists[i].collisionTree->scale, &asset->vertList[i].collisionTree->scale,
						   sizeof(asset->vertList[i].collisionTree->scale));

					h1_asset->rigidVertLists[i].collisionTree->nodeCount = asset->vertList[i].collisionTree->nodeCount;
					h1_asset->rigidVertLists[i].collisionTree->nodes = mem->Alloc<H1::XSurfaceCollisionNode>(
						asset->vertList[i].collisionTree->nodeCount);
					for (int j = 0; j < asset->vertList[i].collisionTree->nodeCount; j++)
					{
						memcpy(&h1_asset->rigidVertLists[i].collisionTree->nodes[j].aabb.mins,
							   &asset->vertList[i].collisionTree->nodes[j].aabb.mins,
							   sizeof(asset->vertList[i].collisionTree->nodes[j].aabb.mins));
						memcpy(&h1_asset->rigidVertLists[i].collisionTree->nodes[j].aabb.maxs,
							   &asset->vertList[i].collisionTree->nodes[j].aabb.maxs,
							   sizeof(asset->vertList[i].collisionTree->nodes[j].aabb.maxs));

						h1_asset->rigidVertLists[i].collisionTree->nodes[j].childBeginIndex =
							asset->vertList[i].collisionTree->nodes[j].childBeginIndex;
						h1_asset->rigidVertLists[i].collisionTree->nodes[j].childCount =
							asset->vertList[i].collisionTree->nodes[j].childCount;
					}

					h1_asset->rigidVertLists[i].collisionTree->leafCount = asset->vertList[i].collisionTree->leafCount;
					h1_asset->rigidVertLists[i].collisionTree->leafs = mem->Alloc<H1::XSurfaceCollisionLeaf>(
						asset->vertList[i].collisionTree->leafCount);
					for (int j = 0; j < asset->vertList[i].collisionTree->leafCount; j++)
					{
						h1_asset->rigidVertLists[i].collisionTree->leafs[j].triangleBeginIndex =
							asset->vertList[i].collisionTree->leafs[j].triangleBeginIndex;
					}
				}
			}
			PrepareVertexWeights(h1_asset);

			// partBits
			memcpy(&h1_asset->partBits, &asset->partBits, sizeof(asset->partBits));
		}

		H1::XModelSurfs *GenerateH1XModelSurfs(XModel *model, int index, ZoneMemory *mem)
		{
			// allocate H1 XModelSurfs structure
			const auto h1_asset = mem->Alloc<H1::XModelSurfs>();

			h1_asset->name = mem->StrDup(va("%s_lod%d", model->name, index));
			h1_asset->numsurfs = model->lodInfo[index].numsurfs;

			if (h1_asset->numsurfs > 16)
			{
				h1_asset->numsurfs = 16;
				//__debugbreak();
			}

			memcpy(&h1_asset->partBits, &model->lodInfo[index].partBits, sizeof(model->lodInfo[index].partBits));

			h1_asset->surfs = mem->Alloc<H1::XSurface>(h1_asset->numsurfs);

			for (unsigned short i = 0; i < h1_asset->numsurfs; i++)
			{
				GenerateH1XSurface(&h1_asset->surfs[i], &model->surfs[model->lodInfo[index].surfIndex + i], mem);

				/// if (i != model->collLod)
				//{
				//	auto target = &h1_asset->surfs[i];
				//	for (unsigned char k = 0; k < target->rigidVertListCount; k++)
				//	{
				//		target->rigidVertLists[k].collisionTree = nullptr; // Only collod is used
				//	}
				//}
			}

			return h1_asset;
		}

		void surf_convert_from_iw3(H1::XSurface *surf, XSurface *asset, ZoneMemory *mem)
		{
			// character assets have this set as 6 while weapons set this as 2...
			surf->flags = 0;
			surf->flags |= asset->deformed ? H1::SURF_FLAG_SKINNED : 0;
			// h1_asset->flags |= H1::SURF_FLAG_VERTCOL_NONE;

			surf->vertCount = asset->vertCount;
			surf->triCount = asset->triCount;
			surf->rigidVertListCount = asset->vertListCount;
			memcpy(&surf->blendVertCounts, &asset->vertInfo.vertCount, sizeof(asset->vertInfo.vertCount));

			int blendVertsDataLength = asset->vertInfo.vertCount[0] + 3 * asset->vertInfo.vertCount[1] + 5 * asset->vertInfo.vertCount[2] + 7 * asset->vertInfo.vertCount[3];

			int blendVertsTotal = asset->vertInfo.vertCount[0] + asset->vertInfo.vertCount[1] + asset->vertInfo.vertCount[2] + asset->vertInfo.vertCount[3];

			auto packedVerts0 = new H1::GfxPackedVertex[asset->vertCount]();
			auto unknown0 = new H1::UnknownXSurface0[asset->vertCount]();

			for (unsigned short i = 0; i < asset->vertCount; i++)
			{
				auto& vert = packedVerts0[i];
				memcpy(&vert, &asset->verts0[i], sizeof(IW3::GfxPackedVertex));

				float texCoord_unpacked[2]{ 0.0f, 0.0f };
				PackedShit::Vec2UnpackTexCoords(asset->verts0[i].texCoord, texCoord_unpacked);
				std::swap(texCoord_unpacked[0], texCoord_unpacked[1]); // these are inverted...
				vert.texCoord.packed = PackedShit::Vec2PackTexCoords(texCoord_unpacked).packed;

				// re-calculate these...
				float normal_unpacked[3]{ 0.0f, 0.0f, 0.0f };
				PackedShit::Vec3UnpackUnitVec(asset->verts0[i].normal, normal_unpacked);

				float tangent_unpacked[3]{ 0.0f, 0.0f, 0.0f };
				PackedShit::Vec3UnpackUnitVec(asset->verts0[i].tangent, tangent_unpacked);

				float normal[3] = { normal_unpacked[0], normal_unpacked[1], normal_unpacked[2] };
				float tangent[3] = { tangent_unpacked[0], tangent_unpacked[1], tangent_unpacked[2] };

				float sign = 0.0f;
				if (asset->verts0[i].binormalSign == -1.0f)
				{
					sign = 1.0f;
				}

				vert.normal.packed = PackedShit::Vec3PackUnitVecWithAlpha(normal, 1.0f).packed;
				//vert.tangent.packed = PackedShit::Vec3PackUnitVecWithAlpha(tangent, sign).packed;
				vert.tangent.packed = vert.normal.packed;

				// correct color : bgra->rgba
				vert.color.array[0] = asset->verts0[i].color.array[2];
				vert.color.array[1] = asset->verts0[i].color.array[1];
				vert.color.array[2] = asset->verts0[i].color.array[0];
				vert.color.array[3] = asset->verts0[i].color.array[3];

				memcpy(unknown0[i].xyz, vert.xyz, sizeof(unknown0[i].xyz));
				unknown0[i].normal = vert.normal;
			}

			surf->unknown0 = reinterpret_cast<H1::UnknownXSurface0 *__ptr64>(unknown0);
			surf->verts0.packedVerts0 = reinterpret_cast<H1::GfxPackedVertex *__ptr64>(packedVerts0);

			// auto triIndices = new H1::Face[asset->triCount]();
			// auto triIndices2 = new H1::Face[asset->triCount]();
			// for (int f = 0; f < asset->triCount; f++)
			//{
			//	auto& face = triIndices[f];
			//	face.v1 = asset->triIndices[f].v1;
			//	face.v2 = asset->triIndices[f].v2;
			//	face.v3 = asset->triIndices[f].v3;
			// }
			// memcpy(triIndices2, triIndices, asset->triCount * sizeof(H1::Face));
			// surf->triIndices = reinterpret_cast<std::uint64_t>(triIndices);
			// surf->triIndices2 = reinterpret_cast<std::uint64_t>(triIndices2);

			// triIndices
			surf->triIndices = reinterpret_cast<H1::Face *__ptr64>(asset->triIndices); // this is draw indices?
			surf->triIndices2 = mem->Alloc<H1::Face>(asset->triCount);				   // this is collision indices?
			for (unsigned short i = 0; i < asset->triCount; i++)
			{
				memcpy(&surf->triIndices2[i], &surf->triIndices[i], sizeof(H1::Face));
			}

			surf->rigidVertListCount = asset->vertListCount;
			auto vertList = new H1::XRigidVertList[asset->vertListCount]();
			for (int j = 0; j < asset->vertListCount; j++)
			{
				vertList[j].boneOffset = asset->vertList[j].boneOffset;
				vertList[j].vertCount = asset->vertList[j].vertCount;
				vertList[j].triOffset = asset->vertList[j].triOffset;
				vertList[j].triCount = asset->vertList[j].triCount;
				vertList[j].collisionTree = 0;

				if (asset->vertList[j].collisionTree)
				{
					auto collisionTree = new H1::XSurfaceCollisionTree();
					memcpy(collisionTree->trans, asset->vertList[j].collisionTree->trans, sizeof(asset->vertList[j].collisionTree->trans));
					memcpy(collisionTree->scale, asset->vertList[j].collisionTree->scale, sizeof(asset->vertList[j].collisionTree->scale));
					collisionTree->nodeCount = asset->vertList[j].collisionTree->nodeCount;
					auto nodes = new H1::XSurfaceCollisionNode[collisionTree->nodeCount]();
					for (int n = 0; n < collisionTree->nodeCount; n++)
					{
						memcpy(nodes[n].aabb.mins, asset->vertList[j].collisionTree->nodes[n].aabb.mins, sizeof(asset->vertList[j].collisionTree->nodes[n].aabb.mins));
						memcpy(nodes[n].aabb.maxs, asset->vertList[j].collisionTree->nodes[n].aabb.maxs, sizeof(asset->vertList[j].collisionTree->nodes[n].aabb.maxs));
						nodes[n].childBeginIndex = asset->vertList[j].collisionTree->nodes[n].childBeginIndex;
						nodes[n].childCount = asset->vertList[j].collisionTree->nodes[n].childCount;
					}
					collisionTree->nodes = reinterpret_cast<H1::XSurfaceCollisionNode *__ptr64>(nodes);

					collisionTree->leafCount = asset->vertList[j].collisionTree->leafCount;
					auto leafs = new H1::XSurfaceCollisionLeaf[collisionTree->leafCount]();
					for (int n = 0; n < collisionTree->leafCount; n++)
					{
						leafs[n].triangleBeginIndex = asset->vertList[j].collisionTree->leafs[n].triangleBeginIndex;
					}
					collisionTree->leafs = reinterpret_cast<H1::XSurfaceCollisionLeaf *__ptr64>(leafs);

					vertList[j].collisionTree = reinterpret_cast<H1::XSurfaceCollisionTree *__ptr64>(collisionTree);
				}
			}
			surf->rigidVertLists = reinterpret_cast<H1::XRigidVertList *__ptr64>(vertList);

			if (blendVertsTotal > 0)
			{
				auto blendVerts = new H1::XBlendInfo[blendVertsDataLength]();
				for (int j = 0; j < blendVertsDataLength; j++)
				{
					blendVerts[j] = asset->vertInfo.vertsBlend[j];
				}
				surf->blendVerts = reinterpret_cast<H1::XBlendInfo *__ptr64>(blendVerts);
			}

			auto blendVertsTable = new H1::BlendVertsUnknown[asset->vertCount]();
			surf->blendVertsTable = reinterpret_cast<H1::BlendVertsUnknown *__ptr64>(blendVertsTable);
			PrepareVertexWeights(surf);
			//GenerateH1BlendVertsShit(surf);

			memcpy(surf->partBits, asset->partBits, sizeof(XSurface::partBits));
		}

		H1::XModelSurfs *convert_from_iw3(XModel *model, int index, ZoneMemory *mem)
		{
			// allocate H1 XModelSurfs structure
			const auto h1_asset = mem->Alloc<H1::XModelSurfs>();

			h1_asset->name = mem->StrDup(va("%s_lod%d", model->name, index));
			h1_asset->numsurfs = model->lodInfo[index].numsurfs;
			memcpy(&h1_asset->partBits, &model->lodInfo[index].partBits, sizeof(model->lodInfo[index].partBits));

			h1_asset->surfs = mem->Alloc<H1::XSurface>(h1_asset->numsurfs);

			for (unsigned short i = 0; i < h1_asset->numsurfs; i++)
			{
				surf_convert_from_iw3(&h1_asset->surfs[i], &model->surfs[model->lodInfo[index].surfIndex + i], mem);
			}

			return h1_asset;
		}

		namespace
		{
			H1::CSurfaceFlags surf_flags_conversion_table[29]{
				H1::SURF_FLAG_DEFAULT,
				H1::SURF_FLAG_BARK,
				H1::SURF_FLAG_BRICK,
				H1::SURF_FLAG_CARPET,
				H1::SURF_FLAG_CLOTH,
				H1::SURF_FLAG_CONCRETE,
				H1::SURF_FLAG_DIRT,
				H1::SURF_FLAG_FLESH,
				H1::SURF_FLAG_FOLIAGE_DEBRIS,
				H1::SURF_FLAG_GLASS,
				H1::SURF_FLAG_GRASS,
				H1::SURF_FLAG_GRAVEL,
				H1::SURF_FLAG_ICE,
				H1::SURF_FLAG_METAL_SOLID,
				H1::SURF_FLAG_MUD,
				H1::SURF_FLAG_PAPER,
				H1::SURF_FLAG_PLASTER,
				H1::SURF_FLAG_ROCK,
				H1::SURF_FLAG_SAND,
				H1::SURF_FLAG_SNOW,
				H1::SURF_FLAG_WATER_WAIST,
				H1::SURF_FLAG_WOOD_SOLID,
				H1::SURF_FLAG_ASPHALT,
				H1::SURF_FLAG_CERAMIC,
				H1::SURF_FLAG_PLASTIC_SOLID,
				H1::SURF_FLAG_RUBBER,
				H1::SURF_FLAG_CUSHION,
				H1::SURF_FLAG_FRUIT,
				H1::SURF_FLAG_PAINTEDMETAL,
			};
			IW3::CSurfaceFlags;

			int convert_surf_flags(int flags)
			{
				int h1_flags = surf_flags_conversion_table[flags >> 20];
				auto convert = [&](IW3::CSurfaceFlags a, H1::CSurfaceFlags b)
				{
					h1_flags |= ((flags & a) == a) ? b : 0;
				};
				convert(IW3::CSurfaceFlags::SURF_FLAG_OPAQUEGLASS, H1::CSurfaceFlags::SURF_FLAG_DEFAULT);
				convert(IW3::CSurfaceFlags::SURF_FLAG_CLIPMISSILE, H1::CSurfaceFlags::SURF_FLAG_CLIPMISSILE);
				convert(IW3::CSurfaceFlags::SURF_FLAG_AI_NOSIGHT, H1::CSurfaceFlags::SURF_FLAG_AI_NOSIGHT);
				convert(IW3::CSurfaceFlags::SURF_FLAG_CLIPSHOT, H1::CSurfaceFlags::SURF_FLAG_CLIPSHOT);
				convert(IW3::CSurfaceFlags::SURF_FLAG_PLAYERCLIP, H1::CSurfaceFlags::SURF_FLAG_PLAYERCLIP);
				convert(IW3::CSurfaceFlags::SURF_FLAG_MONSTERCLIP, H1::CSurfaceFlags::SURF_FLAG_MONSTERCLIP);
				convert(IW3::CSurfaceFlags::SURF_FLAG_VEHICLECLIP, H1::CSurfaceFlags::SURF_FLAG_VEHICLECLIP);
				convert(IW3::CSurfaceFlags::SURF_FLAG_ITEMCLIP, H1::CSurfaceFlags::SURF_FLAG_ITEMCLIP);
				convert(IW3::CSurfaceFlags::SURF_FLAG_NODROP, H1::CSurfaceFlags::SURF_FLAG_NODROP);
				convert(IW3::CSurfaceFlags::SURF_FLAG_NONSOLID, H1::CSurfaceFlags::SURF_FLAG_NONSOLID);
				convert(IW3::CSurfaceFlags::SURF_FLAG_DETAIL, H1::CSurfaceFlags::SURF_FLAG_DETAIL);
				convert(IW3::CSurfaceFlags::SURF_FLAG_STRUCTURAL, H1::CSurfaceFlags::SURF_FLAG_STRUCTURAL);
				convert(IW3::CSurfaceFlags::SURF_FLAG_PORTAL, H1::CSurfaceFlags::SURF_FLAG_PORTAL);
				convert(IW3::CSurfaceFlags::SURF_FLAG_CANSHOOTCLIP, H1::CSurfaceFlags::SURF_FLAG_CANSHOOTCLIP);
				convert(IW3::CSurfaceFlags::SURF_FLAG_ORIGIN, H1::CSurfaceFlags::SURF_FLAG_ORIGIN);
				convert(IW3::CSurfaceFlags::SURF_FLAG_SKY, H1::CSurfaceFlags::SURF_FLAG_SKY);
				convert(IW3::CSurfaceFlags::SURF_FLAG_NOCASTSHADOW, H1::CSurfaceFlags::SURF_FLAG_NOCASTSHADOW);
				convert(IW3::CSurfaceFlags::SURF_FLAG_PHYSICSGEOM, H1::CSurfaceFlags::SURF_FLAG_PHYSICSGEOM);
				convert(IW3::CSurfaceFlags::SURF_FLAG_LIGHTPORTAL, H1::CSurfaceFlags::SURF_FLAG_LIGHTPORTAL);
				convert(IW3::CSurfaceFlags::SURF_FLAG_SLICK, H1::CSurfaceFlags::SURF_FLAG_SLICK);
				convert(IW3::CSurfaceFlags::SURF_FLAG_NOIMPACT, H1::CSurfaceFlags::SURF_FLAG_NOIMPACT);
				convert(IW3::CSurfaceFlags::SURF_FLAG_NOMARKS, H1::CSurfaceFlags::SURF_FLAG_NOMARKS);
				convert(IW3::CSurfaceFlags::SURF_FLAG_NOPENETRATE, H1::CSurfaceFlags::SURF_FLAG_NOPENETRATE);
				convert(IW3::CSurfaceFlags::SURF_FLAG_LADDER, H1::CSurfaceFlags::SURF_FLAG_LADDER);
				convert(IW3::CSurfaceFlags::SURF_FLAG_NODAMAGE, H1::CSurfaceFlags::SURF_FLAG_NODAMAGE);
				convert(IW3::CSurfaceFlags::SURF_FLAG_MANTLEON, H1::CSurfaceFlags::SURF_FLAG_MANTLEON);
				convert(IW3::CSurfaceFlags::SURF_FLAG_MANTLEOVER, H1::CSurfaceFlags::SURF_FLAG_MANTLEOVER);
				convert(IW3::CSurfaceFlags::SURF_FLAG_NOSTEPS, H1::CSurfaceFlags::SURF_FLAG_NOSTEPS);
				convert(IW3::CSurfaceFlags::SURF_FLAG_NODRAW, H1::CSurfaceFlags::SURF_FLAG_NODRAW);
				convert(IW3::CSurfaceFlags::SURF_FLAG_NOLIGHTMAP, H1::CSurfaceFlags::SURF_FLAG_NOLIGHTMAP);
				convert(IW3::CSurfaceFlags::SURF_FLAG_NODLIGHT, H1::CSurfaceFlags::SURF_FLAG_NODLIGHT);
				return h1_flags;
			}
		}

		H1::XModel *GenerateH1Model(XModel *asset, ZoneMemory *mem)
		{
			// allocate H1 XModel structure
			auto *h1_asset = mem->Alloc<H1::XModel>();

			h1_asset->name = asset->name;
			h1_asset->numBones = asset->numBones;
			h1_asset->numRootBones = asset->numRootBones;
			h1_asset->numsurfs = asset->numsurfs;
			h1_asset->numReactiveMotionParts = 0;
			h1_asset->lodRampType = asset->lodRampType;
			h1_asset->scale = 1.0f;
			memset(h1_asset->noScalePartBits, 0, sizeof(unsigned int[8]));

			h1_asset->boneNames = mem->Alloc<H1::scr_string_t>(asset->numBones);
			for (auto i = 0; i < asset->numBones; i++)
			{
				h1_asset->boneNames[i] = static_cast<H1::scr_string_t>(asset->boneNames[i]);
			}

			REINTERPRET_CAST_SAFE(h1_asset->parentList, asset->parentList);
			h1_asset->tagAngles = reinterpret_cast<H1::XModelAngle *>(asset->quats);	 // this is fine
			h1_asset->tagPositions = reinterpret_cast<H1::XModelTagPos *>(asset->trans); // this is fine
			REINTERPRET_CAST_SAFE(h1_asset->partClassification, asset->partClassification);
			REINTERPRET_CAST_SAFE(h1_asset->baseMat, asset->baseMat);
			h1_asset->reactiveMotionParts = nullptr;
			h1_asset->reactiveMotionTweaks = nullptr;

			h1_asset->materialHandles = mem->Alloc<H1::Material *__ptr64>(asset->numsurfs);
			for (auto i = 0; i < asset->numsurfs; i++)
			{
				if (asset->materialHandles[i])
				{
					h1_asset->materialHandles[i] = mem->Alloc<H1::Material>();
					h1_asset->materialHandles[i]->name = mem->StrDup(asset->materialHandles[i]->name);
				}
			}

			for (auto i = 0; i < 6; i++)
			{
				h1_asset->lodInfo[i].dist = 1000000.00f;
			}

			// level of detail data
			for (auto i = 0; i < asset->numLods; i++)
			{
				h1_asset->lodInfo[i].dist = asset->lodInfo[i].dist;

				h1_asset->lodInfo[i].numsurfs = asset->lodInfo[i].numsurfs;
				h1_asset->lodInfo[i].surfIndex = asset->lodInfo[i].surfIndex;

				if (h1_asset->lodInfo[i].numsurfs > 16)
				{
					h1_asset->lodInfo[i].numsurfs = 16;
					//__debugbreak();
				}

				//h1_asset->lodInfo[i].modelSurfs = GenerateH1XModelSurfs(asset, i, mem);
				h1_asset->lodInfo[i].modelSurfs = convert_from_iw3(asset, i, mem);

				H1::IXSurface::dump(h1_asset->lodInfo[i].modelSurfs);

				memcpy(&h1_asset->lodInfo[i].partBits, &asset->lodInfo[i].partBits, sizeof(asset->lodInfo[i].partBits));

				// not sure if correct
				// memcpy(&h1_asset->lodInfo[i].unknown, &asset->lodInfo[i].lod, 4);
			}

			// h1_asset->maxLoadedLod = asset->maxLoadedLod;
			h1_asset->numLods = static_cast<char>(asset->numLods);
			h1_asset->collLod = static_cast<char>(asset->collLod);
			h1_asset->numCompositeModels = 0;
			h1_asset->flags = asset->flags;

			h1_asset->numCollSurfs = asset->numCollSurfs;
			h1_asset->collSurfs = mem->Alloc<H1::XModelCollSurf_s>(asset->numCollSurfs);
			for (auto i = 0; i < asset->numCollSurfs; i++)
			{
				memcpy(&h1_asset->collSurfs[i].bounds, bounds::compute(asset->collSurfs[i].mins, asset->collSurfs[i].maxs), sizeof(float[2][3]));

				h1_asset->collSurfs[i].boneIdx = asset->collSurfs[i].boneIdx;
				h1_asset->collSurfs[i].contents = asset->collSurfs[i].contents;
				h1_asset->collSurfs[i].surfFlags = convert_surf_flags(asset->collSurfs[i].surfFlags);
			}

			h1_asset->contents = asset->contents;

			h1_asset->boneInfo = mem->Alloc<H1::XBoneInfo>(asset->numBones);
			for (char i = 0; i < asset->numBones; ++i)
			{
				auto *target = &h1_asset->boneInfo[i];
				auto *source = &asset->boneInfo[i];

				target->radiusSquared = source->radiusSquared;

				memcpy(&target->bounds, bounds::compute(source->bounds[0], source->bounds[1]), sizeof(float[2][3]));
				target->bounds.midPoint[0] += source->offset[0];
				target->bounds.midPoint[1] += source->offset[1];
				target->bounds.midPoint[2] += source->offset[2];
			}

			h1_asset->radius = asset->radius;
			memcpy(&h1_asset->bounds, bounds::compute(asset->mins, asset->maxs), sizeof(float[2][3]));
			h1_asset->memUsage = asset->memUsage;

			if (asset->physPreset)
			{
				h1_asset->physPreset = mem->Alloc<H1::PhysPreset>();
				h1_asset->physPreset->name = mem->StrDup(asset->physPreset->name);
			}

			if (asset->physGeoms)
			{
				// todo:
				h1_asset->physCollmap = nullptr;
			}

			// idk
			h1_asset->invHighMipRadius = mem->Alloc<unsigned short>(asset->numsurfs);
			for (unsigned char i = 0; i < asset->numsurfs; i++)
			{
				h1_asset->invHighMipRadius[i] = 0xFFFF;
			}

			h1_asset->quantization = 0.0f; // 1.0f;

			return h1_asset;
		}

		void IXModel::dump(XModel *asset, ZoneMemory *mem)
		{
			// generate h1 model
			auto h1_asset = GenerateH1Model(asset, mem);

			// dump h1 model
			H1::IXModel::dump(h1_asset, SL_ConvertToString);
		}
	}
}