#include "stdafx.hpp"

#include "FxEffectDef.hpp"
#include "Converter/H1/Assets/FxEffectDef.hpp"
#include "H1/Assets/FxEffectDef.hpp"

namespace ZoneTool::IW5::H1Dumper
{
	void dump(FxEffectDef* asset, ZoneMemory* mem)
	{
		// generate h1 fx
		auto* h1_asset = H1Converter::convert(asset, mem);

		// dump fx
		H1::IFxEffectDef::dump(h1_asset);
	}
}