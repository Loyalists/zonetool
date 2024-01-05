#include "stdafx.hpp"

#include "PhysPreset.hpp"
#include "Converter/H1/Assets/PhysPreset.hpp"
#include "H1/Assets/PhysPreset.hpp"

namespace ZoneTool::IW5::H1Dumper
{
	void dump(PhysPreset* asset, ZoneMemory* mem)
	{
		// generate h1 asset
		auto* h1_asset = H1Converter::convert(asset, mem);

		// dump asset
		H1::IPhysPreset::dump(h1_asset);
	}
}