#include "stdafx.hpp"

#include "MapEnts.hpp"
#include "Converter/H1/Assets/MapEnts.hpp"
#include "H1/Assets/MapEnts.hpp"

namespace ZoneTool::IW5::H1Dumper
{
	void dump(MapEnts* asset, ZoneMemory* mem)
	{
		// generate h1 mapents
		auto* iw6_asset = H1Converter::convert(asset, mem);

		// dump h1 mapents
		H1::IMapEnts::dump(iw6_asset, SL_ConvertToString);

		// dump spawns
		mapents2spawns::dump_spawns(filesystem::get_dump_path() + asset->name + ".ents.spawnList"s, asset->entityString);
	}
}