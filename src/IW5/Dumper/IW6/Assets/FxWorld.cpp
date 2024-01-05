#include "stdafx.hpp"

#include "FxWorld.hpp"
#include "Converter/IW6/Assets/FxWorld.hpp"
#include "IW6/Assets/FxWorld.hpp"

namespace ZoneTool::IW5::IW6Dumper
{
	void dump(FxWorld* asset, ZoneMemory* mem)
	{
		// generate IW6 fxworld
		auto* iw6_asset = IW6Converter::convert(asset, mem);

		// dump IW6 fxworld
		IW6::IFxWorld::dump(iw6_asset);
	}
}