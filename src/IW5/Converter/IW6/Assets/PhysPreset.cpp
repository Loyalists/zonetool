#include "stdafx.hpp"
#include "../Include.hpp"

#include "PhysPreset.hpp"

namespace ZoneTool::IW5
{
	namespace IW6Converter
	{
		IW6::PhysPreset* GenerateIW6Asset(PhysPreset* asset, ZoneMemory* mem)
		{
			auto* iw6_asset = mem->Alloc<IW6::PhysPreset>();
			
			iw6_asset->name = asset->name;
			iw6_asset->type = asset->type; // convert?
			iw6_asset->mass = asset->mass;
			iw6_asset->bounce = asset->bounce;
			iw6_asset->friction = asset->friction;
			iw6_asset->bulletForceScale = asset->bulletForceScale;
			iw6_asset->explosiveForceScale = asset->explosiveForceScale;
			iw6_asset->sndAliasPrefix = asset->sndAliasPrefix;
			iw6_asset->piecesSpreadFraction = asset->piecesSpreadFraction;
			iw6_asset->piecesUpwardVelocity = asset->piecesUpwardVelocity;
			iw6_asset->minMomentum = asset->minMomentum;
			iw6_asset->maxMomentum = asset->maxMomentum;
			iw6_asset->minPitch = asset->minPitch;
			iw6_asset->maxPitch = asset->maxPitch;
			iw6_asset->volumeType = static_cast<IW6::PhysPresetScaling>(asset->volumeType);
			iw6_asset->pitchType = static_cast<IW6::PhysPresetScaling>(asset->pitchType);
			iw6_asset->tempDefaultToCylinder = asset->tempDefaultToCylinder;
			iw6_asset->perSurfaceSndAlias = asset->perSurfaceSndAlias;

			return iw6_asset;
		}

		IW6::PhysPreset* convert(PhysPreset* asset, ZoneMemory* mem)
		{
			// generate IW6 asset
			return GenerateIW6Asset(asset, mem);
		}
	}
}