#include "stdafx.hpp"
#include "H1/Assets/MapEnts.hpp"

namespace ZoneTool
{
	namespace IW3
	{
		H1::MapEnts* GenerateH1MapEnts(MapEnts* asset, ZoneMemory* mem)
		{
			// allocate H1 MapEnts structure
			const auto h1_asset = mem->Alloc<H1::MapEnts>();

			h1_asset->name = asset->name;

			h1_asset->entityString = asset->entityString;
			h1_asset->numEntityChars = asset->numEntityChars;

			// ents
			std::string ents_string = std::string(asset->entityString, asset->numEntityChars - 1);
			auto ents = entitystrings::ents(ents_string);

			ents_string = ents.build();

			h1_asset->entityString = mem->StrDup(ents_string);
			h1_asset->numEntityChars = ents_string.length() + 1;

			h1_asset->trigger.count = asset->trigger.count;
			h1_asset->trigger.models = reinterpret_cast<H1::TriggerModel*>(asset->trigger.models);
			h1_asset->trigger.hullCount = asset->trigger.hullCount;
			h1_asset->trigger.hulls = reinterpret_cast<H1::TriggerHull*>(asset->trigger.hulls);
			h1_asset->trigger.slabCount = asset->trigger.slabCount;
			h1_asset->trigger.slabs = reinterpret_cast<H1::TriggerSlab*>(asset->trigger.slabs);

			h1_asset->clientTrigger.trigger.count = 0;
			h1_asset->clientTrigger.trigger.models = nullptr;
			h1_asset->clientTrigger.trigger.hullCount = 0;
			h1_asset->clientTrigger.trigger.hulls = nullptr;
			h1_asset->clientTrigger.trigger.slabCount = 0;
			h1_asset->clientTrigger.trigger.slabs = nullptr;
			h1_asset->clientTrigger.numClientTriggerNodes = 0;
			h1_asset->clientTrigger.clientTriggerAabbTree = nullptr;
			h1_asset->clientTrigger.triggerStringLength = 0;
			h1_asset->clientTrigger.triggerString = nullptr;
			h1_asset->clientTrigger.visionSetTriggers = nullptr;
			h1_asset->clientTrigger.blendLookup = nullptr;
			h1_asset->clientTrigger.unk1 = nullptr;
			h1_asset->clientTrigger.triggerType = nullptr;
			h1_asset->clientTrigger.origins = nullptr;
			h1_asset->clientTrigger.scriptDelay = nullptr;
			h1_asset->clientTrigger.audioTriggers = nullptr;
			h1_asset->clientTrigger.unk2 = nullptr;
			h1_asset->clientTrigger.unk3 = nullptr;
			h1_asset->clientTrigger.unk4 = nullptr;
			h1_asset->clientTrigger.unk5 = nullptr;
			h1_asset->clientTrigger.unk6 = nullptr;

			h1_asset->clientTriggerBlend.numClientTriggerBlendNodes = 0;
			h1_asset->clientTriggerBlend.blendNodes = nullptr;

			// generate spawnents with mapents2spawns
			h1_asset->spawnList.spawnsCount = 0;
			h1_asset->spawnList.spawns = nullptr;

			h1_asset->splineList.splineCount = 0;
			h1_asset->splineList.splines = nullptr;

			return h1_asset;
		}

		void IMapEnts::dump(MapEnts* asset, ZoneMemory* mem)
		{
			// generate h1 mapents
			auto iw6_asset = GenerateH1MapEnts(asset, mem);

			// dump h1 mapents
			H1::IMapEnts::dump(iw6_asset, SL_ConvertToString);

			// dump spawns
			mapents2spawns::dump_spawns(filesystem::get_dump_path() + asset->name + ".ents.spawnList"s, asset->entityString);
		}
	}
}