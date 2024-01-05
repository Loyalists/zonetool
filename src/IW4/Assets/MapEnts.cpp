#include "stdafx.hpp"
#include "H1/Assets/MapEnts.hpp"
#include "IW5/Assets/MapEnts.hpp"

namespace ZoneTool
{
	namespace IW4
	{
		void IMapEnts::dump(MapEnts* asset, ZoneMemory* mem)
		{
			auto* new_asset = mem->Alloc<IW5::MapEnts>();
			new_asset->name = asset->name;
			new_asset->entityString = asset->entityString;
			new_asset->numEntityChars = asset->numEntityChars;
			memcpy(&new_asset->trigger, &asset->trigger, sizeof(MapTriggers)); static_assert(sizeof(IW4::MapTriggers) == sizeof(IW5::MapTriggers));
			new_asset->clientTrigger; // 0
			memset(&new_asset->clientTrigger, 0, sizeof(IW5::ClientTriggers));

			IW5::IMapEnts::dump(new_asset, mem);
		}
	}
}
