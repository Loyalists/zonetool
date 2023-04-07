#include "stdafx.hpp"
#include "H1/Assets/MapEnts.hpp"

namespace ZoneTool
{
	namespace IW5
	{
		H1::MapEnts* GenerateH1MapEnts(MapEnts* asset, ZoneMemory* mem)
		{
			// allocate H1 MapEnts structure
			const auto h1_asset = mem->Alloc<H1::MapEnts>();

			h1_asset->name = asset->name;

			h1_asset->entityString = asset->entityString;
			h1_asset->numEntityChars = asset->numEntityChars;

			h1_asset->trigger.count = asset->trigger.modelCount;
			h1_asset->trigger.models = reinterpret_cast<H1::TriggerModel*>(asset->trigger.models);
			h1_asset->trigger.hullCount = asset->trigger.hullCount;
			h1_asset->trigger.hulls = reinterpret_cast<H1::TriggerHull*>(asset->trigger.hulls);
			h1_asset->trigger.slabCount = asset->trigger.slabCount;
			h1_asset->trigger.slabs = reinterpret_cast<H1::TriggerSlab*>(asset->trigger.slabs);

			h1_asset->clientTrigger.trigger.count = asset->clientTrigger.trigger.modelCount;
			h1_asset->clientTrigger.trigger.models = reinterpret_cast<H1::TriggerModel*>(asset->clientTrigger.trigger.models);
			h1_asset->clientTrigger.trigger.hullCount = asset->clientTrigger.trigger.hullCount;
			h1_asset->clientTrigger.trigger.hulls = reinterpret_cast<H1::TriggerHull*>(asset->clientTrigger.trigger.hulls);
			h1_asset->clientTrigger.trigger.slabCount = asset->clientTrigger.trigger.slabCount;
			h1_asset->clientTrigger.trigger.slabs = reinterpret_cast<H1::TriggerSlab*>(asset->clientTrigger.trigger.slabs);
			h1_asset->clientTrigger.numClientTriggerNodes = asset->clientTrigger.numClientTriggerNodes;
			h1_asset->clientTrigger.clientTriggerAabbTree = reinterpret_cast<H1::ClientTriggerAabbNode*>(asset->clientTrigger.clientTriggerAabbTree);
			h1_asset->clientTrigger.triggerStringLength = asset->clientTrigger.triggerStringLength;
			h1_asset->clientTrigger.triggerString = asset->clientTrigger.triggerString;
			h1_asset->clientTrigger.visionSetTriggers = asset->clientTrigger.visionSetTriggers;
			h1_asset->clientTrigger.blendLookup = mem->Alloc<short>(asset->clientTrigger.trigger.modelCount); // todo?
			h1_asset->clientTrigger.unk1 = mem->Alloc<short>(asset->clientTrigger.trigger.modelCount); // todo?
			h1_asset->clientTrigger.triggerType = mem->Alloc<short>(asset->clientTrigger.numClientTriggerNodes);
			for (auto i = 0; i < asset->clientTrigger.numClientTriggerNodes; i++)
			{
				h1_asset->clientTrigger.triggerType[i] = asset->clientTrigger.triggerType[i]; // convert?
			}
			h1_asset->clientTrigger.origins = reinterpret_cast<float(*__ptr64)[3]>(asset->clientTrigger.origins);
			h1_asset->clientTrigger.scriptDelay = asset->clientTrigger.scriptDelay;
			h1_asset->clientTrigger.audioTriggers = mem->Alloc<short>(asset->clientTrigger.trigger.modelCount);
			h1_asset->clientTrigger.unk2 = mem->Alloc<short>(asset->clientTrigger.trigger.modelCount); // todo?
			h1_asset->clientTrigger.unk3 = mem->Alloc<short>(asset->clientTrigger.trigger.modelCount); // todo?
			h1_asset->clientTrigger.unk4 = mem->Alloc<short>(asset->clientTrigger.trigger.modelCount); // todo?
			h1_asset->clientTrigger.unk5 = mem->Alloc<short>(asset->clientTrigger.trigger.modelCount); // todo?
			h1_asset->clientTrigger.unk6 = mem->Alloc<short>(asset->clientTrigger.trigger.modelCount); // todo?

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