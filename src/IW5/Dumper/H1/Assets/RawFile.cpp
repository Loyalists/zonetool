#include "stdafx.hpp"
#include "RawFile.hpp"

#include "Converter/H1/Assets/RawFile.hpp"
#include "H1/Assets/RawFile.hpp"

namespace ZoneTool::IW5::H1Dumper
{
	void dump(RawFile* asset, ZoneMemory* mem)
	{
		// generate h1 rawfile
		auto* h1_asset = H1Converter::convert(asset, mem);

		// dump rawfile
		H1::IRawFile::dump(h1_asset);
	}
}