#include "stdafx.hpp"

#include "GfxWorld.hpp"
#include "Converter/H1/Assets/GfxWorld.hpp"
#include "H1/Assets/GfxWorld.hpp"

namespace ZoneTool::IW5::H1Dumper
{
	void dump(GfxWorld* asset, ZoneMemory* mem)
	{
		// generate h1 gfxworld
		auto* h1_asset = H1Converter::convert(asset, mem);

		// dump h1 gfxworld
		H1::IGfxWorld::dump(h1_asset);
	}
}