#include "stdafx.hpp"

#include "ComWorld.hpp"
#include "Converter/H1/Assets/ComWorld.hpp"
#include "H1/Assets/ComWorld.hpp"

namespace ZoneTool::IW5::H1Dumper
{
	void dump(ComWorld* asset, ZoneMemory* mem)
	{
		// generate h1 comworld
		auto* h1_asset = H1Converter::convert(asset, mem);

		// dump h1 comworld
		H1::IComWorld::dump(h1_asset);
	}
}