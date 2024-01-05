#include "stdafx.hpp"

#include "ClipMap.hpp"
#include "Converter/IW6/Assets/ClipMap.hpp"
#include "IW6/Assets/ClipMap.hpp"

namespace ZoneTool::IW5::IW6Dumper
{
	void dump(clipMap_t* asset, ZoneMemory* mem)
	{
		// generate iw6 clipmap
		auto* iw6_asset = IW6Converter::convert(asset, mem);

		// dump iw6 clipmap
		IW6::IClipMap::dump(iw6_asset, SL_ConvertToString);
	}
}