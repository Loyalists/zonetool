#include "stdafx.hpp"

#include "GfxWorld.hpp"
#include "Converter/IW6/Assets/GfxWorld.hpp"
#include "IW6/Assets/GfxWorld.hpp"

namespace ZoneTool::IW5::IW6Dumper
{
	void dump(GfxWorld* asset, ZoneMemory* mem)
	{
		// generate IW6 gfxworld
		auto* iw6_asset = IW6Converter::convert(asset, mem);

		// dump IW6 gfxworld
		IW6::IGfxWorld::dump(iw6_asset);
	}
}