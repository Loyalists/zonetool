#include "stdafx.hpp"

#include "ComWorld.hpp"
#include "Converter/IW6/Assets/ComWorld.hpp"
#include "IW6/Assets/ComWorld.hpp"

namespace ZoneTool::IW5::IW6Dumper
{
	void dump(ComWorld* asset, ZoneMemory* mem)
	{
		// generate iw6 comworld
		auto* iw6_asset = IW6Converter::convert(asset, mem);

		// dump iw6 comworld
		IW6::IComWorld::dump(iw6_asset);
	}
}