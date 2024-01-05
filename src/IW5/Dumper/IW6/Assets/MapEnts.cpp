#include "stdafx.hpp"

#include "MapEnts.hpp"
#include "Converter/IW6/Assets/MapEnts.hpp"
#include "IW6/Assets/MapEnts.hpp"

namespace ZoneTool::IW5::IW6Dumper
{
	void dump(MapEnts* asset, ZoneMemory* mem)
	{
		// generate IW6 mapents
		auto* iw6_asset = IW6Converter::convert(asset, mem);

		// dump IW6 mapents
		IW6::IMapEnts::dump(iw6_asset, SL_ConvertToString);

		// dump spawns
		mapents2spawns::dump_spawns(filesystem::get_dump_path() + asset->name + ".ents.spawnList"s, asset->entityString);
	}
}