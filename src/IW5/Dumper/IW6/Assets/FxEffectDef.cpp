#include "stdafx.hpp"

#include "FxEffectDef.hpp"
#include "Converter/IW6/Assets/FxEffectDef.hpp"
#include "IW6/Assets/FxEffectDef.hpp"

namespace ZoneTool::IW5::IW6Dumper
{
	void dump(FxEffectDef* asset, ZoneMemory* mem)
	{
		// generate IW6 fx
		auto* iw6_asset = IW6Converter::convert(asset, mem);

		// dump fx
		IW6::IFxEffectDef::dump(iw6_asset);
	}
}