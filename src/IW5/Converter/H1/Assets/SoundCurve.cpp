#include "stdafx.hpp"
#include "../Include.hpp"

#include "SoundCurve.hpp"

namespace ZoneTool::IW5
{
	namespace H1Converter
	{
		H1::SndCurve* GenerateH1SoundCurve(SndCurve* asset, ZoneMemory* mem)
		{
			auto* h1_asset = mem->Alloc<H1::SndCurve>();

			h1_asset->name = asset->filename;
			h1_asset->knotCount = asset->knotCount;
			memcpy(h1_asset->knots, asset->knots, sizeof(IW5::vec2_t[16]));

			return h1_asset;
		}

		H1::SndCurve* convert(SndCurve* asset, ZoneMemory* mem)
		{
			// generate h1 asset
			return GenerateH1SoundCurve(asset, mem);
		}
	}
}