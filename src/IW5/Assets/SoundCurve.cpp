#include "stdafx.hpp"
#include "H1/Assets/SoundCurve.hpp"

namespace ZoneTool
{
	namespace IW5
	{
		H1::SndCurve* GenerateH1SoundCurve(SndCurve* asset, ZoneMemory* mem)
		{
			auto* h1_asset = mem->Alloc<H1::SndCurve>();

			h1_asset->name = asset->name;
			h1_asset->knotCount = asset->knotCount;
			memcpy(h1_asset->knots, asset->knots, sizeof(IW5::vec2_t[16]));

			return h1_asset;
		}

		void ISoundCurve::dump(SndCurve* asset, ZoneMemory* mem)
		{
			// generate h1 asset
			auto* h1_asset = GenerateH1SoundCurve(asset, mem);

			// dump lightdef
			H1::ISoundCurve::dump(h1_asset);
		}
	}
}