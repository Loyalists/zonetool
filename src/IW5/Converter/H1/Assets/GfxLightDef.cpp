#include "stdafx.hpp"
#include "../Include.hpp"

#include "GfxLightDef.hpp"

namespace ZoneTool::IW5
{
	namespace H1Converter
	{
		H1::GfxLightDef* GenerateH1GfxLightDef(GfxLightDef* asset, ZoneMemory* mem)
		{
			auto* h1_asset = mem->Alloc<H1::GfxLightDef>();
			h1_asset->name = asset->name;
			if (asset->attenuation.image)
			{
				h1_asset->attenuation.image = mem->Alloc<H1::GfxImage>();
				h1_asset->attenuation.image->name = asset->attenuation.image->name;
			}
			h1_asset->attenuation.samplerState = asset->attenuation.samplerState;
			if (asset->cucoloris.image)
			{
				h1_asset->cucoloris.image = mem->Alloc<H1::GfxImage>();
				h1_asset->cucoloris.image->name = asset->cucoloris.image->name;
			}
			h1_asset->cucoloris.samplerState = asset->cucoloris.samplerState;
			h1_asset->lmapLookupStart = asset->lmapLookupStart;
			return h1_asset;
		}

		H1::GfxLightDef* convert(GfxLightDef* asset, ZoneMemory* mem)
		{
			// generate h1 lightdef
			return GenerateH1GfxLightDef(asset, mem);
		}
	}
}