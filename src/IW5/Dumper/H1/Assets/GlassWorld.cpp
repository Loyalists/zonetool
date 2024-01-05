#include "stdafx.hpp"

#include "GlassWorld.hpp"
#include "Converter/H1/Assets/GlassWorld.hpp"
#include "H1/Assets/GlassWorld.hpp"

namespace ZoneTool::IW5::H1Dumper
{
	void dump(GlassWorld* asset, ZoneMemory* mem)
	{
		// generate h1 glassworld
		auto* h1_asset = H1Converter::convert(asset, mem);

		// dump h1 glassworld
		H1::IGlassWorld::dump(h1_asset);
	}
}