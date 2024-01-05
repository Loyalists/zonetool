#include "stdafx.hpp"
#include "../Include.hpp"

#include "GlassWorld.hpp"

namespace ZoneTool::IW5
{
	namespace IW6Converter
	{
		IW6::GlassWorld* GenerateIW6GlassWorld(GlassWorld* asset, ZoneMemory* mem)
		{
			// allocate IW6 GlassWorld structure
			const auto iw6_asset = mem->Alloc<IW6::GlassWorld>();

			iw6_asset->name = asset->name;
			iw6_asset->g_glassData = mem->Alloc<IW6::G_GlassData>();
			iw6_asset->g_glassData->pieceCount = asset->g_glassData->pieceCount;
			iw6_asset->g_glassData->glassPieces = mem->Alloc<IW6::G_GlassPiece>(iw6_asset->g_glassData->pieceCount);
			for (unsigned int i = 0; i < iw6_asset->g_glassData->pieceCount; i++)
			{
				iw6_asset->g_glassData->glassPieces[i].damageTaken = asset->g_glassData->glassPieces[i].damageTaken;
				iw6_asset->g_glassData->glassPieces[i].collapseTime = asset->g_glassData->glassPieces[i].collapseTime;
				iw6_asset->g_glassData->glassPieces[i].lastStateChangeTime = asset->g_glassData->glassPieces[i].lastStateChangeTime;
				iw6_asset->g_glassData->glassPieces[i].impactDir = asset->g_glassData->glassPieces[i].impactDir;
				iw6_asset->g_glassData->glassPieces[i].impactPos[0] = asset->g_glassData->glassPieces[i].impactPos[0];
				iw6_asset->g_glassData->glassPieces[i].impactPos[1] = asset->g_glassData->glassPieces[i].impactPos[1];
			}
			iw6_asset->g_glassData->damageToWeaken = asset->g_glassData->damageToWeaken;
			iw6_asset->g_glassData->damageToDestroy = asset->g_glassData->damageToDestroy;
			iw6_asset->g_glassData->glassNameCount = asset->g_glassData->glassNameCount;
			iw6_asset->g_glassData->glassNames = mem->Alloc<IW6::G_GlassName>(iw6_asset->g_glassData->glassNameCount);
			for (unsigned int i = 0; i < iw6_asset->g_glassData->glassNameCount; i++)
			{
				iw6_asset->g_glassData->glassNames[i].nameStr = asset->g_glassData->glassNames[i].nameStr;
				iw6_asset->g_glassData->glassNames[i].name = static_cast<IW6::scr_string_t>(asset->g_glassData->glassNames[i].name);
				iw6_asset->g_glassData->glassNames[i].pieceCount = asset->g_glassData->glassNames[i].pieceCount;
				iw6_asset->g_glassData->glassNames[i].pieceIndices = reinterpret_cast<unsigned __int16* __ptr64>(asset->g_glassData->glassNames[i].pieceIndices);
			}
			memcpy(&iw6_asset->g_glassData->pad, asset->g_glassData->pad, sizeof(asset->g_glassData->pad));

			return iw6_asset;
		}

		IW6::GlassWorld* convert(GlassWorld* asset, ZoneMemory* mem)
		{
			// generate IW6 glassworld
			return GenerateIW6GlassWorld(asset, mem);
		}
	}
}