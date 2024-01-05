#include "stdafx.hpp"

#include "XAnimParts.hpp"
#include "Converter/H1/Assets/XAnimParts.hpp"
#include "H1/Assets/XAnimParts.hpp"

namespace ZoneTool::IW5::H1Dumper
{
	void dump(XAnimParts* asset, ZoneMemory* mem, const std::function<const char* (uint16_t)>& convertToString)
	{
		// generate h1 anims
		auto h1_asset = H1Converter::convert(asset, mem);

		// dump h1 anims
		H1::IXAnimParts::dump(h1_asset, convertToString);
	}
}