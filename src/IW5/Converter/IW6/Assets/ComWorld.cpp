#include "stdafx.hpp"
#include "../Include.hpp"

#include "ComWorld.hpp"

namespace ZoneTool::IW5
{
	namespace IW6Converter
	{
		IW6::ComWorld* GenerateIW6ComWorld(ComWorld* asset, ZoneMemory* mem)
		{
			// allocate IW6 ComWorld structure
			const auto iw6_asset = mem->Alloc<IW6::ComWorld>();

			iw6_asset->name = asset->name;
			iw6_asset->isInUse = asset->isInUse;
			iw6_asset->primaryLightCount = asset->primaryLightCount;
			iw6_asset->primaryLights = mem->Alloc<IW6::ComPrimaryLight>(iw6_asset->primaryLightCount);
			for (unsigned int i = 0; i < iw6_asset->primaryLightCount; i++)
			{
				iw6_asset->primaryLights[i].type = asset->primaryLights[i].type; // don't think there is a need for converting
				iw6_asset->primaryLights[i].canUseShadowMap = asset->primaryLights[i].canUseShadowMap;
				iw6_asset->primaryLights[i].exponent = asset->primaryLights[i].exponent;
				iw6_asset->primaryLights[i].unused = asset->primaryLights[i].unused;
				memcpy(&iw6_asset->primaryLights[i].color, &asset->primaryLights[i].color, sizeof(float[3]));
				memcpy(&iw6_asset->primaryLights[i].dir, &asset->primaryLights[i].dir, sizeof(float[3]));
				memcpy(&iw6_asset->primaryLights[i].up, &asset->primaryLights[i].up, sizeof(float[3]));
				memcpy(&iw6_asset->primaryLights[i].origin, &asset->primaryLights[i].origin, sizeof(float[3]));
				iw6_asset->primaryLights[i].radius = asset->primaryLights[i].radius;
				iw6_asset->primaryLights[i].cosHalfFovOuter = asset->primaryLights[i].cosHalfFovOuter;
				iw6_asset->primaryLights[i].cosHalfFovInner = asset->primaryLights[i].cosHalfFovInner;
				iw6_asset->primaryLights[i].cosHalfFovExpanded = asset->primaryLights[i].cosHalfFovExpanded;
				iw6_asset->primaryLights[i].rotationLimit = asset->primaryLights[i].rotationLimit;
				iw6_asset->primaryLights[i].translationLimit = asset->primaryLights[i].translationLimit;
				iw6_asset->primaryLights[i].cucRotationOffsetRad = 0;
				iw6_asset->primaryLights[i].cucRotationSpeedRad = 0;
				memset(&iw6_asset->primaryLights[i].cucScrollVector, 0, sizeof(float[2]));
				memset(&iw6_asset->primaryLights[i].cucScaleVector, 0, sizeof(float[2]));
				memset(&iw6_asset->primaryLights[i].cucTransVector, 0, sizeof(float[2]));
				iw6_asset->primaryLights[i].defName = asset->primaryLights[i].defName;

				if (iw6_asset->primaryLights[i].type == 2)
				{
					iw6_asset->primaryLights[i].cucScaleVector[0] = 1.0f;
					iw6_asset->primaryLights[i].cucScaleVector[1] = 1.0f;
				}
				else if (iw6_asset->primaryLights[i].type == 3)
				{
					iw6_asset->primaryLights[i].cucScaleVector[0] = 1.0f;
					iw6_asset->primaryLights[i].cucScaleVector[1] = 1.0f;
				}
			}

			iw6_asset->primaryLightEnvCount = iw6_asset->primaryLightCount + 1;
			iw6_asset->primaryLightEnvs = mem->Alloc<IW6::ComPrimaryLightEnv>(iw6_asset->primaryLightEnvCount);
			
			for (unsigned int i = 1; i < iw6_asset->primaryLightCount; i++)
			{
				iw6_asset->primaryLightEnvs[i].numIndices = 1;
				iw6_asset->primaryLightEnvs[i].primaryLightIndices[0] = i;
			}

			iw6_asset->primaryLightEnvs[iw6_asset->primaryLightEnvCount - 1].numIndices = 1;
			iw6_asset->primaryLightEnvs[iw6_asset->primaryLightEnvCount - 1].primaryLightIndices[0] = 2047;

			return iw6_asset;
		}

		IW6::ComWorld* convert(ComWorld* asset, ZoneMemory* mem)
		{
			// generate IW6 comworld
			return GenerateIW6ComWorld(asset, mem);
		}
	}
}