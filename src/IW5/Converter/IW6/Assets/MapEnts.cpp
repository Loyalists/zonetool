#include "stdafx.hpp"
#include "../Include.hpp"

#include "MapEnts.hpp"

namespace ZoneTool::IW5
{
	namespace IW6Converter
	{
		IW6::MapEnts* GenerateIW6MapEnts(MapEnts* asset, ZoneMemory* mem)
		{
			// allocate IW6 MapEnts structure
			const auto iw6_asset = mem->Alloc<IW6::MapEnts>();

			iw6_asset->name = asset->name;

			iw6_asset->entityString = asset->entityString;
			iw6_asset->numEntityChars = asset->numEntityChars;

			iw6_asset->trigger.count = asset->trigger.count;
			iw6_asset->trigger.models = reinterpret_cast<IW6::TriggerModel*>(asset->trigger.models);
			iw6_asset->trigger.hullCount = asset->trigger.hullCount;
			iw6_asset->trigger.hulls = reinterpret_cast<IW6::TriggerHull*>(asset->trigger.hulls);
			iw6_asset->trigger.slabCount = asset->trigger.slabCount;
			iw6_asset->trigger.slabs = reinterpret_cast<IW6::TriggerSlab*>(asset->trigger.slabs);

			iw6_asset->clientTrigger.trigger.count = asset->clientTrigger.trigger.count;
			iw6_asset->clientTrigger.trigger.models = reinterpret_cast<IW6::TriggerModel*>(asset->clientTrigger.trigger.models);
			iw6_asset->clientTrigger.trigger.hullCount = asset->clientTrigger.trigger.hullCount;
			iw6_asset->clientTrigger.trigger.hulls = reinterpret_cast<IW6::TriggerHull*>(asset->clientTrigger.trigger.hulls);
			iw6_asset->clientTrigger.trigger.slabCount = asset->clientTrigger.trigger.slabCount;
			iw6_asset->clientTrigger.trigger.slabs = reinterpret_cast<IW6::TriggerSlab*>(asset->clientTrigger.trigger.slabs);
			iw6_asset->clientTrigger.numClientTriggerNodes = asset->clientTrigger.numClientTriggerNodes;
			iw6_asset->clientTrigger.clientTriggerAabbTree = reinterpret_cast<IW6::ClientTriggerAabbNode*>(asset->clientTrigger.clientTriggerAabbTree);
			iw6_asset->clientTrigger.triggerStringLength = asset->clientTrigger.triggerStringLength;
			iw6_asset->clientTrigger.triggerString = asset->clientTrigger.triggerString;
			iw6_asset->clientTrigger.visionSetTriggers = mem->Alloc<short>(asset->clientTrigger.trigger.count); // todo?
			iw6_asset->clientTrigger.triggerType = mem->Alloc<char>(asset->clientTrigger.trigger.count);
			for (auto i = 0; i < asset->clientTrigger.trigger.count; i++)
			{
				iw6_asset->clientTrigger.triggerType[i] = asset->clientTrigger.triggerType[i]; // convert?
			}
			iw6_asset->clientTrigger.origins = reinterpret_cast<float(*__ptr64)[3]>(asset->clientTrigger.origins);
			iw6_asset->clientTrigger.scriptDelay = asset->clientTrigger.scriptDelay;
			iw6_asset->clientTrigger.audioTriggers = mem->Alloc<short>(asset->clientTrigger.trigger.count);
			iw6_asset->clientTrigger.blendLookup = mem->Alloc<short>(asset->clientTrigger.trigger.count); // todo?
			iw6_asset->clientTrigger.npcTriggers = mem->Alloc<short>(asset->clientTrigger.trigger.count); // todo?

			iw6_asset->clientTriggerBlend.numClientTriggerBlendNodes = 0;
			iw6_asset->clientTriggerBlend.blendNodes = nullptr;

			// generate spawnents with mapents2spawns
			iw6_asset->spawnList.spawnsCount = 0;
			iw6_asset->spawnList.spawns = nullptr;

			iw6_asset->splineList.splineCount = 0;
			iw6_asset->splineList.splines = nullptr;

			return iw6_asset;
		}

		IW6::MapEnts* convert(MapEnts* asset, ZoneMemory* mem)
		{
			// generate IW6 mapents
			return GenerateIW6MapEnts(asset, mem);
		}
	}
}