#include "stdafx.hpp"

#include "XAnimParts.hpp"
#include "Converter/IW6/Assets/XAnimParts.hpp"
#include "IW6/Assets/XAnimParts.hpp"

namespace ZoneTool::IW5::IW6Dumper
{
	void dump(XAnimParts* asset, ZoneMemory* mem, const std::function<const char* (uint16_t)>& convertToString)
	{
		// generate IW6 anims
		auto iw6_asset = IW6Converter::convert(asset, mem);

		// dump IW6 anims
		IW6::IXAnimParts::dump(iw6_asset, convertToString);
	}
}