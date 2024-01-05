#include "stdafx.hpp"

#include "GfxLightDef.hpp"
#include "Converter/IW6/Assets/GfxLightDef.hpp"
#include "IW6/Assets/GfxLightDef.hpp"

namespace ZoneTool::IW5::IW6Dumper
{
	void dump(GfxLightDef* asset, ZoneMemory* mem)
	{
		// generate IW6 lightdef
		auto* iw6_asset = IW6Converter::convert(asset, mem);

		// dump lightdef
		IW6::IGfxLightDef::dump(iw6_asset);
	}
}