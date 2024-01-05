#include "stdafx.hpp"

#include "XModel.hpp"
#include "Converter/IW6/Assets/XModel.hpp"
#include "IW6/Assets/XModel.hpp"

namespace ZoneTool::IW5::IW6Dumper
{
	void dump(XModel* asset, ZoneMemory* mem, const std::function<const char* (uint16_t)>& convertToString)
	{
		// generate IW6 model
		auto iw6_asset = IW6Converter::convert(asset, mem);

		// dump IW6 model
		IW6::IXModel::dump(iw6_asset, convertToString);
	}
}