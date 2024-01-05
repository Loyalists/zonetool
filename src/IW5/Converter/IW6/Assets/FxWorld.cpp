#include "stdafx.hpp"
#include "../Include.hpp"

#include "FxWorld.hpp"

namespace ZoneTool::IW5
{
	namespace IW6Converter
	{
		IW6::FxWorld* GenerateIW6FxWorld(FxWorld* asset, ZoneMemory* mem)
		{
			// allocate IW6 FxWorld structure
			const auto iw6_asset = mem->Alloc<IW6::FxWorld>();

			iw6_asset->name = asset->name;

			iw6_asset->glassSys.time = asset->glassSys.time;
			iw6_asset->glassSys.prevTime = asset->glassSys.prevTime;
			iw6_asset->glassSys.defCount = asset->glassSys.defCount;
			iw6_asset->glassSys.pieceLimit = asset->glassSys.pieceLimit;
			iw6_asset->glassSys.pieceWordCount = asset->glassSys.pieceWordCount;
			iw6_asset->glassSys.initPieceCount = asset->glassSys.initPieceCount;
			iw6_asset->glassSys.cellCount = asset->glassSys.cellCount;
			iw6_asset->glassSys.activePieceCount = asset->glassSys.activePieceCount;
			iw6_asset->glassSys.firstFreePiece = asset->glassSys.firstFreePiece;
			iw6_asset->glassSys.geoDataLimit = asset->glassSys.geoDataLimit;
			iw6_asset->glassSys.geoDataCount = asset->glassSys.geoDataCount;
			iw6_asset->glassSys.initGeoDataCount = asset->glassSys.initGeoDataCount;

			iw6_asset->glassSys.defs = mem->Alloc<IW6::FxGlassDef>(iw6_asset->glassSys.defCount);
			for (unsigned int i = 0; i < iw6_asset->glassSys.defCount; i++)
			{
				iw6_asset->glassSys.defs[i].halfThickness = asset->glassSys.defs[i].halfThickness;
				memcpy(&iw6_asset->glassSys.defs[i].texVecs, &asset->glassSys.defs[i].texVecs, sizeof(float[2][2]));
				
				// correct color : bgra->rgba
				iw6_asset->glassSys.defs[i].color.array[0] = asset->glassSys.defs[i].color.array[2];
				iw6_asset->glassSys.defs[i].color.array[1] = asset->glassSys.defs[i].color.array[1];
				iw6_asset->glassSys.defs[i].color.array[2] = asset->glassSys.defs[i].color.array[0];
				iw6_asset->glassSys.defs[i].color.array[3] = asset->glassSys.defs[i].color.array[3];

				iw6_asset->glassSys.defs[i].material = reinterpret_cast<IW6::Material*>(asset->glassSys.defs[i].material);
				iw6_asset->glassSys.defs[i].materialShattered = reinterpret_cast<IW6::Material*>(asset->glassSys.defs[i].materialShattered);
				iw6_asset->glassSys.defs[i].physPreset = reinterpret_cast<IW6::PhysPreset*>(asset->glassSys.defs[i].physPreset);

				iw6_asset->glassSys.defs[i].pieceBreakEffect = mem->Alloc<IW6::FxEffectDef>();
				iw6_asset->glassSys.defs[i].pieceBreakEffect->name = mem->StrDup("fx/code/glass_shatter_piece");

				iw6_asset->glassSys.defs[i].shatterEffect = mem->Alloc<IW6::FxEffectDef>();
				iw6_asset->glassSys.defs[i].shatterEffect->name = mem->StrDup("fx/code/glass_shatter_64x64");

				iw6_asset->glassSys.defs[i].shatterSmallEffect = mem->Alloc<IW6::FxEffectDef>();
				iw6_asset->glassSys.defs[i].shatterSmallEffect->name = mem->StrDup("fx/code/glass_shatter_32x32");

				iw6_asset->glassSys.defs[i].crackDecalEffect = nullptr;

				iw6_asset->glassSys.defs[i].damagedSound = mem->Alloc<IW6::snd_alias_list_t>();
				iw6_asset->glassSys.defs[i].damagedSound->name = mem->StrDup("glass_pane_shatter");

				iw6_asset->glassSys.defs[i].destroyedSound = mem->Alloc<IW6::snd_alias_list_t>();
				iw6_asset->glassSys.defs[i].destroyedSound->name = mem->StrDup("glass_pane_blowout");

				iw6_asset->glassSys.defs[i].destroyedQuietSound = mem->Alloc<IW6::snd_alias_list_t>();
				iw6_asset->glassSys.defs[i].destroyedQuietSound->name = mem->StrDup("glass_pane_breakout");

				iw6_asset->glassSys.defs[i].numCrackRings = -1;
				iw6_asset->glassSys.defs[i].isOpaque = 0;
			}

			iw6_asset->glassSys.piecePlaces = mem->Alloc<IW6::FxGlassPiecePlace>(iw6_asset->glassSys.pieceLimit);
			for (unsigned int i = 0; i < iw6_asset->glassSys.pieceLimit; i++)
			{
				memcpy(&iw6_asset->glassSys.piecePlaces[i], &asset->glassSys.piecePlaces[i], sizeof(IW5::FxGlassPiecePlace));
			}

			iw6_asset->glassSys.pieceStates = mem->Alloc<IW6::FxGlassPieceState>(iw6_asset->glassSys.pieceLimit);
			for (unsigned int i = 0; i < iw6_asset->glassSys.pieceLimit; i++)
			{
				memcpy(&iw6_asset->glassSys.pieceStates[i].texCoordOrigin, &asset->glassSys.pieceStates[i].texCoordOrigin, sizeof(float[2]));
				iw6_asset->glassSys.pieceStates[i].supportMask = asset->glassSys.pieceStates[i].supportMask;
				iw6_asset->glassSys.pieceStates[i].initIndex = asset->glassSys.pieceStates[i].initIndex;
				iw6_asset->glassSys.pieceStates[i].geoDataStart = asset->glassSys.pieceStates[i].geoDataStart;
				iw6_asset->glassSys.pieceStates[i].lightingIndex = asset->glassSys.pieceStates[i].initIndex;
				iw6_asset->glassSys.pieceStates[i].defIndex = asset->glassSys.pieceStates[i].defIndex;
				iw6_asset->glassSys.pieceStates[i].vertCount = asset->glassSys.pieceStates[i].vertCount;
				iw6_asset->glassSys.pieceStates[i].holeDataCount = asset->glassSys.pieceStates[i].holeDataCount;
				iw6_asset->glassSys.pieceStates[i].crackDataCount = asset->glassSys.pieceStates[i].crackDataCount;
				iw6_asset->glassSys.pieceStates[i].fanDataCount = asset->glassSys.pieceStates[i].fanDataCount;
				iw6_asset->glassSys.pieceStates[i].flags = asset->glassSys.pieceStates[i].flags;
				iw6_asset->glassSys.pieceStates[i].areaX2 = asset->glassSys.pieceStates[i].areaX2;
			}

			iw6_asset->glassSys.pieceDynamics = mem->Alloc<IW6::FxGlassPieceDynamics>(iw6_asset->glassSys.pieceLimit);
			for (unsigned int i = 0; i < iw6_asset->glassSys.pieceLimit; i++)
			{
				iw6_asset->glassSys.pieceDynamics[i].fallTime = asset->glassSys.pieceDynamics[i].fallTime;
				iw6_asset->glassSys.pieceDynamics[i].physObjId = asset->glassSys.pieceDynamics[i].physObjId;
				iw6_asset->glassSys.pieceDynamics[i].physJointId = asset->glassSys.pieceDynamics[i].physJointId;
				memcpy(&iw6_asset->glassSys.pieceDynamics[i].vel, &asset->glassSys.pieceDynamics[i].vel, sizeof(float[3]));
				memcpy(&iw6_asset->glassSys.pieceDynamics[i].avel, &asset->glassSys.pieceDynamics[i].avel, sizeof(float[3]));
			}

			iw6_asset->glassSys.geoData = mem->Alloc<IW6::FxGlassGeometryData>(iw6_asset->glassSys.geoDataLimit);
			for (unsigned int i = 0; i < iw6_asset->glassSys.geoDataLimit; i++)
			{
				memcpy(&iw6_asset->glassSys.geoData[i], &asset->glassSys.geoData[i], sizeof(IW5::FxGlassGeometryData));
			}

			iw6_asset->glassSys.isInUse = mem->Alloc<unsigned int>(iw6_asset->glassSys.pieceWordCount);
			for (unsigned int i = 0; i < iw6_asset->glassSys.pieceWordCount; i++)
			{
				iw6_asset->glassSys.isInUse[i] = asset->glassSys.isInUse[i];
			}

			iw6_asset->glassSys.cellBits = mem->Alloc<unsigned int>(iw6_asset->glassSys.pieceWordCount * iw6_asset->glassSys.cellCount);
			for (unsigned int i = 0; i < iw6_asset->glassSys.pieceWordCount * iw6_asset->glassSys.cellCount; i++)
			{
				iw6_asset->glassSys.cellBits[i] = asset->glassSys.cellBits[i];
			}

			iw6_asset->glassSys.visData = mem->Alloc<unsigned char>((iw6_asset->glassSys.pieceLimit + 15) & 0xFFFFFFF0);
			for (unsigned int i = 0; i < ((iw6_asset->glassSys.pieceLimit + 15) & 0xFFFFFFF0); i++)
			{
				iw6_asset->glassSys.visData[i] = asset->glassSys.visData[i];
			}

			iw6_asset->glassSys.linkOrg = reinterpret_cast<float(*)[3]>(asset->glassSys.linkOrg);

			iw6_asset->glassSys.halfThickness = mem->Alloc<float>((iw6_asset->glassSys.pieceLimit + 3) & 0xFFFFFFFC);
			for (unsigned int i = 0; i < ((iw6_asset->glassSys.pieceLimit + 3) & 0xFFFFFFFC); i++)
			{
				iw6_asset->glassSys.halfThickness[i] = asset->glassSys.halfThickness[i];
			}

			iw6_asset->glassSys.lightingHandles = mem->Alloc<unsigned short>(iw6_asset->glassSys.initPieceCount);
			for (unsigned int i = 0; i < iw6_asset->glassSys.initPieceCount; i++)
			{
				iw6_asset->glassSys.lightingHandles[i] = asset->glassSys.lightingHandles[i];
			}

			iw6_asset->glassSys.initPieceStates = mem->Alloc<IW6::FxGlassInitPieceState>(iw6_asset->glassSys.initPieceCount);
			for (unsigned int i = 0; i < iw6_asset->glassSys.initPieceCount; i++)
			{
				memcpy(&iw6_asset->glassSys.initPieceStates[i].frame, &asset->glassSys.initPieceStates[i].frame, sizeof(IW5::FxSpatialFrame));
				iw6_asset->glassSys.initPieceStates[i].radius = asset->glassSys.initPieceStates[i].radius;
				memcpy(&iw6_asset->glassSys.initPieceStates[i].texCoordOrigin, &asset->glassSys.initPieceStates[i].texCoordOrigin, sizeof(float[2]));
				iw6_asset->glassSys.initPieceStates[i].supportMask = asset->glassSys.initPieceStates[i].supportMask;
				iw6_asset->glassSys.initPieceStates[i].areaX2 = asset->glassSys.initPieceStates[i].areaX2;
				iw6_asset->glassSys.initPieceStates[i].lightingIndex = 0;
				iw6_asset->glassSys.initPieceStates[i].defIndex = asset->glassSys.initPieceStates[i].defIndex;
				iw6_asset->glassSys.initPieceStates[i].vertCount = asset->glassSys.initPieceStates[i].vertCount;
				iw6_asset->glassSys.initPieceStates[i].fanDataCount = asset->glassSys.initPieceStates[i].fanDataCount;
			}

			iw6_asset->glassSys.initGeoData = mem->Alloc<IW6::FxGlassGeometryData>(iw6_asset->glassSys.initGeoDataCount);
			for (unsigned int i = 0; i < iw6_asset->glassSys.initGeoDataCount; i++)
			{
				memcpy(&iw6_asset->glassSys.initGeoData[i], &asset->glassSys.initGeoData[i], sizeof(IW5::FxGlassGeometryData));
			}

			iw6_asset->glassSys.needToCompactData = asset->glassSys.needToCompactData;
			iw6_asset->glassSys.initCount = asset->glassSys.initCount;
			iw6_asset->glassSys.effectChanceAccum = asset->glassSys.effectChanceAccum;
			iw6_asset->glassSys.lastPieceDeletionTime = asset->glassSys.lastPieceDeletionTime;

			return iw6_asset;
		}

		IW6::FxWorld* convert(FxWorld* asset, ZoneMemory* mem)
		{
			// generate IW6 fxworld
			return GenerateIW6FxWorld(asset, mem);
		}
	}
}