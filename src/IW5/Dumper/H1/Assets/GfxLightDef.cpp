#include "stdafx.hpp"

#include "GfxLightDef.hpp"
#include "Converter/H1/Assets/GfxLightDef.hpp"
#include "H1/Assets/GfxLightDef.hpp"

namespace ZoneTool::IW5::H1Dumper
{
	void dump(GfxLightDef* asset, ZoneMemory* mem)
	{
		// generate h1 lightdef
		auto* h1_asset = H1Converter::convert(asset, mem);

		// dump lightdef
		H1::IGfxLightDef::dump(h1_asset);
	}
}