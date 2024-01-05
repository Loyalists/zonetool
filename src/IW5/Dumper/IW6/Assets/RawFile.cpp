#include "stdafx.hpp"
#include "RawFile.hpp"

#include "Converter/IW6/Assets/RawFile.hpp"
#include "IW6/Assets/RawFile.hpp"

namespace ZoneTool::IW5::IW6Dumper
{
	void dump(RawFile* asset, ZoneMemory* mem)
	{
		// generate IW6 rawfile
		auto* iw6_asset = IW6Converter::convert(asset, mem);

		// dump rawfile
		IW6::IRawFile::dump(iw6_asset);
	}
}