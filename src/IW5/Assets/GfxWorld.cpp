#include "stdafx.hpp"
#include "H1/Assets/GfxWorld.hpp"

namespace ZoneTool
{
	namespace
	{
		namespace PackedShit
		{
			using namespace IW5;

			PackedUnitVec Vec3PackUnitVec(float* in) // h1 func
			{
				unsigned int bits;

				bits = ((unsigned int)floor(((((fmaxf(-1.0f, fminf(1.0f, in[2])) + 1.0f) * 0.5f) * 1023.0f) + 0.5f)) | 0xFFFFFC00) << 10;
				bits = ((unsigned int)floor(((((fmaxf(-1.0f, fminf(1.0f, in[1])) + 1.0f) * 0.5f) * 1023.0f) + 0.5f)) | bits) << 10;
				bits = ((unsigned int)floor(((((fmaxf(-1.0f, fminf(1.0f, in[0])) + 1.0f) * 0.5f) * 1023.0f) + 0.5f)) | bits);

				return { bits };
			}

			PackedUnitVec Vec3PackUnitVecWithAlpha(float* in, float alpha) // h1 func
			{
				unsigned int bits;

				bits = ((unsigned int)floor(((((fmaxf(-1.0f, fminf(1.0f, alpha)) + 1.0f) * 0.5f) * 1023.0f) + 0.5f)) | 0xFFFFFC00) << 10;
				bits = ((unsigned int)floor(((((fmaxf(-1.0f, fminf(1.0f, in[2])) + 1.0f) * 0.5f) * 1023.0f) + 0.5f)) | bits) << 10;
				bits = ((unsigned int)floor(((((fmaxf(-1.0f, fminf(1.0f, in[1])) + 1.0f) * 0.5f) * 1023.0f) + 0.5f)) | bits) << 10;
				bits = ((unsigned int)floor(((((fmaxf(-1.0f, fminf(1.0f, in[0])) + 1.0f) * 0.5f) * 1023.0f) + 0.5f)) | bits);

				return { bits };
			}

			void Vec3UnpackUnitVec(const PackedUnitVec in, float* out) // t6 func
			{
				float decodeScale;

				decodeScale = (in.array[3] - -192.0f) / 32385.0f;
				out[0] = (in.array[0] - 127.0f) * decodeScale;
				out[1] = (in.array[1] - 127.0f) * decodeScale;
				out[2] = (in.array[2] - 127.0f) * decodeScale;
			}
		}
	}

	namespace
	{
		typedef unsigned short ushort;
		typedef unsigned int uint;

		uint as_uint(const float x) {
			return *(uint*)&x;
		}
		float as_float(const uint x) {
			return *(float*)&x;
		}

		float half_to_float(const ushort x) { // IEEE-754 16-bit floating-point format (without infinity): 1-5-10, exp-15, +-131008.0, +-6.1035156E-5, +-5.9604645E-8, 3.311 digits
			const uint e = (x & 0x7C00) >> 10; // exponent
			const uint m = (x & 0x03FF) << 13; // mantissa
			const uint v = as_uint((float)m) >> 23; // evil log2 bit hack to count leading zeros in denormalized format
			return as_float((x & 0x8000) << 16 | (e != 0) * ((e + 112) << 23 | m) | ((e == 0) & (m != 0)) * ((v - 37) << 23 | ((m << (150 - v)) & 0x007FE000))); // sign : normalized : denormalized
		}
		ushort float_to_half(const float x) { // IEEE-754 16-bit floating-point format (without infinity): 1-5-10, exp-15, +-131008.0, +-6.1035156E-5, +-5.9604645E-8, 3.311 digits
			const uint b = as_uint(x) + 0x00001000; // round-to-nearest-even: add last bit after truncated mantissa
			const uint e = (b & 0x7F800000) >> 23; // exponent
			const uint m = b & 0x007FFFFF; // mantissa; in line below: 0x007FF000 = 0x00800000-0x00001000 = decimal indicator flag - initial rounding
			return (ushort)((b & 0x80000000) >> 16 | (e > 112) * ((((e - 112) << 10) & 0x7C00) | m >> 13) | ((e < 113) & (e > 101)) * ((((0x007FF000 + m) >> (125 - e)) + 1) >> 1) | (e > 143) * 0x7FFF); // sign : normalized : denormalized : saturate
		}
	}

	namespace IW5
	{
		H1::GfxWorld* GenerateH1GfxWorld(GfxWorld* asset, ZoneMemory* mem)
		{
			// allocate H1 GfxWorld structure
			const auto h1_asset = mem->Alloc<H1::GfxWorld>();

			h1_asset->name = asset->name;
			h1_asset->baseName = asset->baseName;

			h1_asset->bspVersion = 111;

			h1_asset->planeCount = asset->planeCount;
			h1_asset->nodeCount = asset->nodeCount;
			h1_asset->surfaceCount = asset->surfaceCount;
			h1_asset->skyCount = asset->skyCount;

			h1_asset->skies = mem->Alloc<H1::GfxSky>(h1_asset->skyCount);
			for (int i = 0; i < h1_asset->skyCount; i++)
			{
				h1_asset->skies[i].skySurfCount = asset->skies[i].skySurfCount;
				REINTERPRET_CAST_SAFE(h1_asset->skies[i].skyStartSurfs, asset->skies[i].skyStartSurfs);
				if (asset->skies[i].skyImage)
				{
					h1_asset->skies[i].skyImage = mem->Alloc<H1::GfxImage>();
					h1_asset->skies[i].skyImage->name = asset->skies[i].skyImage->name;
				}
				else
				{
					h1_asset->skies[i].skyImage = nullptr;
				}
				h1_asset->skies[i].skySamplerState = asset->skies[i].skySamplerState;

				// add bounds
				//assert(asset->skies[i].skySurfCount == 1);
				for (auto j = 0; j < asset->skies[i].skySurfCount; j++)
				{
					auto index = asset->dpvs.sortedSurfIndex[asset->skies[i].skyStartSurfs[j]];
					auto* surface_bounds = &asset->dpvs.surfacesBounds[index];
					memcpy(&h1_asset->skies[i].bounds, &surface_bounds->bounds, sizeof(surface_bounds->bounds));

					//
					break;
				}
			}

			h1_asset->portalGroupCount = 0;
			h1_asset->lastSunPrimaryLightIndex = asset->lastSunPrimaryLightIndex;
			h1_asset->primaryLightCount = asset->primaryLightCount;
			h1_asset->primaryLightEnvCount = asset->primaryLightCount + 1;
			h1_asset->sortKeyLitDecal = 7; // h1_asset->sortKeyLitDecal = asset->sortKeyLitDecal;
			h1_asset->sortKeyEffectDecal = 43; // h1_asset->sortKeyEffectDecal = asset->sortKeyEffectDecal;
			h1_asset->sortKeyTopDecal = 17;
			h1_asset->sortKeyEffectAuto = 53; // h1_asset->sortKeyEffectAuto = asset->sortKeyEffectAuto;
			h1_asset->sortKeyDistortion = 48; // h1_asset->sortKeyDistortion = asset->sortKeyDistortion;
			h1_asset->sortKeyUnknown = 18;
			h1_asset->sortKeyUnknown2 = 33;

			h1_asset->dpvsPlanes.cellCount = asset->dpvsPlanes.cellCount;
			REINTERPRET_CAST_SAFE(h1_asset->dpvsPlanes.planes, asset->dpvsPlanes.planes);
			REINTERPRET_CAST_SAFE(h1_asset->dpvsPlanes.nodes, asset->dpvsPlanes.nodes);

			h1_asset->dpvsPlanes.sceneEntCellBits = mem->Alloc<unsigned int>(asset->dpvsPlanes.cellCount << 9);
			for (int i = 0; i < asset->dpvsPlanes.cellCount << 9; i++)
			{
				h1_asset->dpvsPlanes.sceneEntCellBits[i] = asset->dpvsPlanes.sceneEntCellBits[i];
			}

			h1_asset->aabbTreeCounts = mem->Alloc<H1::GfxCellTreeCount>(h1_asset->dpvsPlanes.cellCount); //reinterpret_cast<IW6::GfxCellTreeCount* __ptr64>(asset->aabbTreeCounts);
			h1_asset->aabbTrees = mem->Alloc<H1::GfxCellTree>(h1_asset->dpvsPlanes.cellCount);
			for (int i = 0; i < h1_asset->dpvsPlanes.cellCount; i++)
			{
				h1_asset->aabbTreeCounts[i].aabbTreeCount = asset->aabbTreeCounts[i].aabbTreeCount;
				h1_asset->aabbTrees[i].aabbTree = mem->Alloc<H1::GfxAabbTree>(h1_asset->aabbTreeCounts[i].aabbTreeCount);
				for (int j = 0; j < h1_asset->aabbTreeCounts[i].aabbTreeCount; j++)
				{
					memcpy(&h1_asset->aabbTrees[i].aabbTree[j].bounds, &asset->aabbTree[i].aabbtree[j].mins, sizeof(float[2][3]));

					h1_asset->aabbTrees[i].aabbTree[j].startSurfIndex = asset->aabbTree[i].aabbtree[j].startSurfIndex;
					h1_asset->aabbTrees[i].aabbTree[j].surfaceCount = asset->aabbTree[i].aabbtree[j].surfaceCount;

					h1_asset->aabbTrees[i].aabbTree[j].smodelIndexCount = asset->aabbTree[i].aabbtree[j].smodelIndexCount;
					REINTERPRET_CAST_SAFE(h1_asset->aabbTrees[i].aabbTree[j].smodelIndexes, asset->aabbTree[i].aabbtree[j].smodelIndexes);

					h1_asset->aabbTrees[i].aabbTree[j].childCount = asset->aabbTree[i].aabbtree[j].childCount;
					// re-calculate childrenOffset
					auto offset = asset->aabbTree[i].aabbtree[j].childrenOffset;
					int childrenIndex = offset / sizeof(IW5::GfxAabbTree);
					int childrenOffset = childrenIndex * sizeof(H1::GfxAabbTree);
					h1_asset->aabbTrees[i].aabbTree[j].childrenOffset = childrenOffset;
				}
			}

			h1_asset->cells = mem->Alloc<H1::GfxCell>(h1_asset->dpvsPlanes.cellCount);
			for (int i = 0; i < h1_asset->dpvsPlanes.cellCount; i++)
			{
				memcpy(&h1_asset->cells[i].bounds, &asset->cells[i].mins, sizeof(float[2][3]));
				h1_asset->cells[i].portalCount = asset->cells[i].portalCount;

				auto add_portal = [](H1::GfxPortal* h1_portal, IW5::GfxPortal* iw5_portal)
				{
					//h1_portal->writable.isQueued = iw5_portal->writable.isQueued;
					//h1_portal->writable.isAncestor = iw5_portal->writable.isAncestor;
					//h1_portal->writable.recursionDepth = iw5_portal->writable.recursionDepth;
					//h1_portal->writable.hullPointCount = iw5_portal->writable.hullPointCount;
					//h1_portal->writable.hullPoints = reinterpret_cast<float(*__ptr64)[2]>(iw5_portal->writable.hullPoints);
					//h1_portal->writable.queuedParent = add_portal(iw5_portal->writable.queuedParent); // mapped at runtime

					memcpy(&h1_portal->plane, &iw5_portal->plane, sizeof(float[4]));
					h1_portal->vertices = reinterpret_cast<float(*__ptr64)[3]>(iw5_portal->vertices);
					h1_portal->cellIndex = iw5_portal->cellIndex;
					h1_portal->closeDistance = 0;
					h1_portal->vertexCount = iw5_portal->vertexCount;
					memcpy(&h1_portal->hullAxis, &iw5_portal->hullAxis, sizeof(float[2][3]));
				};
				h1_asset->cells[i].portals = mem->Alloc<H1::GfxPortal>(h1_asset->cells[i].portalCount);
				for (int j = 0; j < h1_asset->cells[i].portalCount; j++)
				{
					add_portal(&h1_asset->cells[i].portals[j], &asset->cells[i].portals[j]);
				}

				h1_asset->cells[i].reflectionProbeCount = asset->cells[i].reflectionProbeCount;
				h1_asset->cells[i].reflectionProbes = reinterpret_cast<unsigned __int8* __ptr64>(asset->cells[i].reflectionProbes);
				h1_asset->cells[i].reflectionProbeReferenceCount = asset->cells[i].reflectionProbeReferenceCount;
				h1_asset->cells[i].reflectionProbeReferences = reinterpret_cast<unsigned __int8* __ptr64>(asset->cells[i].reflectionProbeReferences);
			}

			h1_asset->portalGroup = nullptr;

			h1_asset->unk_vec4_count_0 = 0;
			h1_asset->unk_vec4_0 = nullptr;

			h1_asset->draw.reflectionProbeCount = asset->worldDraw.reflectionProbeCount;
			h1_asset->draw.reflectionProbes = mem->Alloc<H1::GfxImage* __ptr64>(h1_asset->draw.reflectionProbeCount);
			h1_asset->draw.reflectionProbeOrigins = mem->Alloc<H1::GfxReflectionProbe>(h1_asset->draw.reflectionProbeCount);
			h1_asset->draw.reflectionProbeTextures = mem->Alloc<H1::GfxRawTexture>(h1_asset->draw.reflectionProbeCount);
			for (unsigned int i = 0; i < h1_asset->draw.reflectionProbeCount; i++)
			{
				h1_asset->draw.reflectionProbes[i] = mem->Alloc<H1::GfxImage>();
				h1_asset->draw.reflectionProbes[i]->name = asset->worldDraw.reflectionImages[i]->name;
				memcpy(&h1_asset->draw.reflectionProbeOrigins[i].origin, &asset->worldDraw.reflectionProbes[i].offset, sizeof(float[3]));
				h1_asset->draw.reflectionProbeOrigins[i].probeVolumeCount = 0;
				h1_asset->draw.reflectionProbeOrigins[i].probeVolumes = nullptr;
				//memcpy(&h1_asset->draw.reflectionProbeTextures[i], &asset->worldDraw.reflectionProbeTextures[i].loadDef, 20);
			}
			h1_asset->draw.reflectionProbeReferenceCount = asset->worldDraw.reflectionProbeReferenceCount;
			h1_asset->draw.reflectionProbeReferenceOrigins = reinterpret_cast<H1::GfxReflectionProbeReferenceOrigin * __ptr64>(
				asset->worldDraw.reflectionProbeReferenceOrigins);
			h1_asset->draw.reflectionProbeReferences = reinterpret_cast<H1::GfxReflectionProbeReference * __ptr64>(
				asset->worldDraw.reflectionProbeReferences);

			h1_asset->draw.lightmapCount = asset->worldDraw.lightmapCount;
			h1_asset->draw.lightmaps = mem->Alloc<H1::GfxLightmapArray>(h1_asset->draw.lightmapCount);
			h1_asset->draw.lightmapPrimaryTextures = mem->Alloc<H1::GfxRawTexture>(h1_asset->draw.lightmapCount);
			h1_asset->draw.lightmapSecondaryTextures = mem->Alloc<H1::GfxRawTexture>(h1_asset->draw.lightmapCount);
			for (int i = 0; i < h1_asset->draw.lightmapCount; i++)
			{
				h1_asset->draw.lightmaps[i].primary = mem->Alloc<H1::GfxImage>();
				h1_asset->draw.lightmaps[i].primary->name = asset->worldDraw.lightmaps[i].primary->name;
				h1_asset->draw.lightmaps[i].secondary = mem->Alloc<H1::GfxImage>();
				h1_asset->draw.lightmaps[i].secondary->name = asset->worldDraw.lightmaps[i].secondary->name;

				//memcpy(&h1_asset->draw.lightmapPrimaryTextures[i], &asset->worldDraw.lightmapPrimaryTextures[i].loadDef, 20);
				//memcpy(&h1_asset->draw.lightmapSecondaryTextures[i], &asset->worldDraw.lightmapSecondaryTextures[i].loadDef, 20);
			}
			if (asset->worldDraw.skyImage)
			{
				h1_asset->draw.lightmapOverridePrimary = mem->Alloc<H1::GfxImage>();
				h1_asset->draw.lightmapOverridePrimary->name = asset->worldDraw.skyImage->name;
			}
			else
			{
				h1_asset->draw.lightmapOverridePrimary = nullptr;
			}

			if (asset->worldDraw.outdoorImage)
			{
				h1_asset->draw.lightmapOverrideSecondary = mem->Alloc<H1::GfxImage>();
				h1_asset->draw.lightmapOverrideSecondary->name = asset->worldDraw.outdoorImage->name;
			}
			else
			{
				h1_asset->draw.lightmapOverrideSecondary = nullptr;
			}

			h1_asset->draw.u1[0] = 1024; h1_asset->draw.u1[1] = 1024; // u1
			h1_asset->draw.u2[0] = 512; h1_asset->draw.u2[1] = 512; // u2
			h1_asset->draw.u3 = 8; // u3

			h1_asset->draw.trisType = 0; // dunno

			h1_asset->draw.vertexCount = asset->worldDraw.vertexCount;
			h1_asset->draw.vd.vertices = mem->Alloc<H1::GfxWorldVertex>(h1_asset->draw.vertexCount);
			for (unsigned int i = 0; i < h1_asset->draw.vertexCount; i++)
			{
				memcpy(&h1_asset->draw.vd.vertices[i], &asset->worldDraw.vd.vertices[i], sizeof(IW5::GfxWorldVertex));

				// re-calculate these...
				float normal_unpacked[3]{ 0.0f, 0.0f, 0.0f };
				PackedShit::Vec3UnpackUnitVec(asset->worldDraw.vd.vertices[i].normal, normal_unpacked);

				float tangent_unpacked[3]{ 0.0f, 0.0f, 0.0f };
				PackedShit::Vec3UnpackUnitVec(asset->worldDraw.vd.vertices[i].tangent, tangent_unpacked);

				float normal[3] = { normal_unpacked[0], normal_unpacked[1], normal_unpacked[2] };
				float tangent[3] = { tangent_unpacked[0], tangent_unpacked[1], tangent_unpacked[2] };

				float sign = 0.0f;
				if (asset->worldDraw.vd.vertices[i].binormalSign == -1.0f)
				{
					sign = 1.0f;
				}

				h1_asset->draw.vd.vertices[i].normal.packed = PackedShit::Vec3PackUnitVecWithAlpha(normal, 1.0f).packed;
				h1_asset->draw.vd.vertices[i].tangent.packed = PackedShit::Vec3PackUnitVecWithAlpha(tangent, sign).packed;

				// correct color : bgra->rgba
				h1_asset->draw.vd.vertices[i].color.array[0] = asset->worldDraw.vd.vertices[i].color.array[2];
				h1_asset->draw.vd.vertices[i].color.array[1] = asset->worldDraw.vd.vertices[i].color.array[1];
				h1_asset->draw.vd.vertices[i].color.array[2] = asset->worldDraw.vd.vertices[i].color.array[0];
				h1_asset->draw.vd.vertices[i].color.array[3] = asset->worldDraw.vd.vertices[i].color.array[3];
			}

			h1_asset->draw.vertexLayerDataSize = asset->worldDraw.vertexLayerDataSize;
			REINTERPRET_CAST_SAFE(h1_asset->draw.vld.data, asset->worldDraw.vld.data);

			h1_asset->draw.indexCount = asset->worldDraw.indexCount;
			REINTERPRET_CAST_SAFE(h1_asset->draw.indices, asset->worldDraw.indices);

			h1_asset->draw.displacementParmsCount = 0;
			h1_asset->draw.displacementParms = nullptr;

			h1_asset->lightGrid.hasLightRegions = asset->lightGrid.hasLightRegions;
			h1_asset->lightGrid.useSkyForLowZ = 0;
			h1_asset->lightGrid.lastSunPrimaryLightIndex = asset->lightGrid.sunPrimaryLightIndex;
			memcpy(&h1_asset->lightGrid.mins, &asset->lightGrid.mins, sizeof(short[3]));
			memcpy(&h1_asset->lightGrid.maxs, &asset->lightGrid.maxs, sizeof(short[3]));
			h1_asset->lightGrid.rowAxis = asset->lightGrid.rowAxis;
			h1_asset->lightGrid.colAxis = asset->lightGrid.colAxis;
			REINTERPRET_CAST_SAFE(h1_asset->lightGrid.rowDataStart, asset->lightGrid.rowDataStart);
			h1_asset->lightGrid.rawRowDataSize = asset->lightGrid.rawRowDataSize;
			REINTERPRET_CAST_SAFE(h1_asset->lightGrid.rawRowData, asset->lightGrid.rawRowData);
			h1_asset->lightGrid.entryCount = asset->lightGrid.entryCount;
			h1_asset->lightGrid.entries = mem->Alloc<H1::GfxLightGridEntry>(h1_asset->lightGrid.entryCount);
			for (unsigned int i = 0; i < h1_asset->lightGrid.entryCount; i++)
			{
				h1_asset->lightGrid.entries[i].colorsIndex = asset->lightGrid.entries[i].colorsIndex;
				h1_asset->lightGrid.entries[i].primaryLightEnvIndex = asset->lightGrid.entries[i].primaryLightIndex;
				h1_asset->lightGrid.entries[i].unused = 0;
				h1_asset->lightGrid.entries[i].needsTrace = asset->lightGrid.entries[i].needsTrace;
			}
			h1_asset->lightGrid.colorCount = asset->lightGrid.colorCount;
			h1_asset->lightGrid.colors = mem->Alloc<H1::GfxLightGridColors>(h1_asset->lightGrid.colorCount);
			for (unsigned int i = 0; i < h1_asset->lightGrid.colorCount; i++)
			{
				// colorVec3 -> colorVec6
				
				//memcpy(&h1_asset->lightGrid.colors[i].colorVec6, &asset->lightGrid.colors[i].rgb, sizeof(asset->lightGrid.colors[i]));
			}

			//h1_asset->lightGrid.__pad0; // unknown data in pad
			//h1_asset->lightGrid.missingGridColorIndex = 0;			// no such thing in iw5 {
			//h1_asset->lightGrid.tableVersion = 0;
			//h1_asset->lightGrid.paletteVersion = 0;
			//h1_asset->lightGrid.rangeExponent8BitsEncoding = 0;
			//h1_asset->lightGrid.rangeExponent12BitsEncoding = 0;
			//h1_asset->lightGrid.rangeExponent16BitsEncoding = 0;
			//h1_asset->lightGrid.stageCount = 0;
			//h1_asset->lightGrid.stageLightingContrastGain = 0;
			//h1_asset->lightGrid.paletteEntryCount = 0;
			//h1_asset->lightGrid.paletteEntryAddress = 0;
			//h1_asset->lightGrid.paletteBitstreamSize = 0;
			//h1_asset->lightGrid.paletteBitstream = 0;
			//h1_asset->lightGrid.skyLightGridColors.colorVec6;
			//h1_asset->lightGrid.defaultLightGridColors;
			//h1_asset->lightGrid.tree;								// }

			
			// --experimental--

			h1_asset->lightGrid.tableVersion = 1;
			h1_asset->lightGrid.paletteVersion = 1;
			h1_asset->lightGrid.paletteEntryCount = asset->lightGrid.entryCount;
			h1_asset->lightGrid.paletteEntryAddress = mem->Alloc<int>(h1_asset->lightGrid.paletteEntryCount);
			for (unsigned int i = 0; i < h1_asset->lightGrid.paletteEntryCount; i++)
			{
				h1_asset->lightGrid.paletteEntryAddress[i] = 30; // 0, 30, 86, 116 //asset->lightGrid.entries[i].colorsIndex;
			}

			// mp_character_room palettebitstream
			std::uint8_t paletteBitStream[] =
			{
			8, 33, 195, 128, 128, 124, 128, 128, 128, 129, 128, 199, 128, 128, 124, 128, 128, 128, 129, 128, 216, 128, 128, 124, 128, 128, 128, 129, 128, 0, 8, 33, 187, 128, 128, 130, 128, 128, 128, 128, 128, 191, 128, 128, 130, 128, 128, 128, 128, 128, 209, 128, 128, 130, 128, 128, 128, 128, 128, 0, 0, 0, 82, 80, 18, 64, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 214, 106, 18, 64, 1, 0, 0, 0, 8, 33, 195, 128, 128, 124, 128, 128, 128, 129, 128, 199, 128, 128, 124, 128, 128, 128, 129, 128, 216, 128, 128, 124, 128, 128, 128, 129, 128, 0, 198, 24, 241, 248, 8, 128, 128, 128, 128, 90, 128, 241, 8, 128, 248, 128, 128, 128, 147, 184, 241, 128, 248, 8, 128, 128, 128, 147, 72, 0,
			};

			h1_asset->lightGrid.paletteBitstreamSize = sizeof(paletteBitStream);
			h1_asset->lightGrid.paletteBitstream = mem->Alloc<unsigned char>(h1_asset->lightGrid.paletteBitstreamSize);
			memcpy(h1_asset->lightGrid.paletteBitstream, paletteBitStream, sizeof(paletteBitStream));

			h1_asset->lightGrid.missingGridColorIndex = h1_asset->lightGrid.paletteEntryCount - 1;

			h1_asset->lightGrid.rangeExponent8BitsEncoding = 0;
			h1_asset->lightGrid.rangeExponent12BitsEncoding = 4;
			h1_asset->lightGrid.rangeExponent16BitsEncoding = 23;

			h1_asset->lightGrid.stageCount = 1;
			h1_asset->lightGrid.stageLightingContrastGain = mem->Alloc<float>(1);
			h1_asset->lightGrid.stageLightingContrastGain[0] = 0.3f;

			for (auto i = 0; i < 3; i++)
			{
				h1_asset->lightGrid.tree[i].index = i;
			}

			// ----
			

			h1_asset->modelCount = asset->modelCount;
			h1_asset->models = mem->Alloc<H1::GfxBrushModel>(h1_asset->modelCount);
			for (int i = 0; i < h1_asset->modelCount; i++)
			{
				int decals = asset->models[i].surfaceCount - asset->models[i].surfaceCountNoDecal;

				//memcpy(&h1_asset->models[i].writable.bounds, &asset->models[i].writable.bounds, sizeof(float[2][3])); // Irrevelant
				memcpy(&h1_asset->models[i].bounds, &asset->models[i].bounds, sizeof(float[2][3]));

				h1_asset->models[i].radius = asset->models[i].radius;
				h1_asset->models[i].startSurfIndex = asset->models[i].startSurfIndex;
				h1_asset->models[i].surfaceCount = asset->models[i].surfaceCountNoDecal + decals;
				h1_asset->models[i].mdaoVolumeIndex = -1;
			}

			memcpy(h1_asset->mins1, asset->bounds.midPoint, sizeof(float[3]));
			memcpy(h1_asset->maxs1, asset->bounds.halfSize, sizeof(float[3]));
			memcpy(h1_asset->mins2, asset->bounds.midPoint, sizeof(float[3]));
			memcpy(h1_asset->maxs2, asset->bounds.halfSize, sizeof(float[3]));

			// bounds1 = ?
			// bounds2 = shadowBounds;

			h1_asset->checksum = asset->checksum;

			h1_asset->materialMemoryCount = asset->materialMemoryCount;
			h1_asset->materialMemory = mem->Alloc<H1::MaterialMemory>(h1_asset->materialMemoryCount);
			for (int i = 0; i < h1_asset->materialMemoryCount; i++)
			{
				h1_asset->materialMemory[i].material = reinterpret_cast<H1::Material * __ptr64>(asset->materialMemory[i].material);
				h1_asset->materialMemory[i].memory = asset->materialMemory[i].memory;
			}

			h1_asset->sun.hasValidData = asset->sun.hasValidData;
			h1_asset->sun.spriteMaterial = reinterpret_cast<H1::Material * __ptr64>(asset->sun.spriteMaterial);
			h1_asset->sun.flareMaterial = reinterpret_cast<H1::Material * __ptr64>(asset->sun.flareMaterial);
			memcpy(&h1_asset->sun.spriteSize, &asset->sun.spriteSize, Difference(&asset->sun.sunFxPosition, &asset->sun.spriteSize) + sizeof(float[3]));

			memcpy(&h1_asset->outdoorLookupMatrix, &asset->outdoorLookupMatrix, sizeof(float[4][4]));

			h1_asset->outdoorImage = mem->Alloc<H1::GfxImage>();
			h1_asset->outdoorImage->name = asset->outdoorImage->name;

			h1_asset->cellCasterBits = mem->Alloc<unsigned int>(h1_asset->dpvsPlanes.cellCount * ((h1_asset->dpvsPlanes.cellCount + 31) >> 5));
			for (int i = 0; i < asset->dpvsPlanes.cellCount * ((asset->dpvsPlanes.cellCount + 31) >> 5); i++)
			{
				h1_asset->cellCasterBits[i] = asset->cellCasterBits[0][i];
			}
			h1_asset->cellHasSunLitSurfsBits = mem->Alloc<unsigned int>((h1_asset->dpvsPlanes.cellCount + 31) >> 5); // todo?

			h1_asset->sceneDynModel = mem->Alloc<H1::GfxSceneDynModel>(asset->dpvsDyn.dynEntClientCount[0]);
			for (unsigned int i = 0; i < asset->dpvsDyn.dynEntClientCount[0]; i++)
			{
				h1_asset->sceneDynModel[i].info.hasGfxEntIndex = asset->sceneDynModel[i].info.hasGfxEntIndex;
				h1_asset->sceneDynModel[i].info.lod = asset->sceneDynModel[i].info.lod;
				h1_asset->sceneDynModel[i].info.surfId = asset->sceneDynModel[i].info.surfId;
				h1_asset->sceneDynModel[i].dynEntId = asset->sceneDynModel[i].dynEntId;
			}
			REINTERPRET_CAST_SAFE(h1_asset->sceneDynBrush, asset->sceneDynBrush);

			//h1_asset->primaryLightEntityShadowVis = reinterpret_cast<unsigned int* __ptr64>(asset->primaryLightEntityShadowVis);
			int count = ((h1_asset->primaryLightCount - h1_asset->lastSunPrimaryLightIndex) << 13) - 0x2000;
			h1_asset->primaryLightEntityShadowVis = mem->Alloc<unsigned int>(count);
			for (unsigned int i = 0; i < count; i++)
			{
				h1_asset->primaryLightEntityShadowVis[i] = asset->primaryLightEntityShadowVis[i];
			}

			h1_asset->primaryLightDynEntShadowVis[0] = reinterpret_cast<unsigned int* __ptr64>(asset->primaryLightDynEntShadowVis[0]);
			h1_asset->primaryLightDynEntShadowVis[1] = reinterpret_cast<unsigned int* __ptr64>(asset->primaryLightDynEntShadowVis[1]);

			//h1_asset->nonSunPrimaryLightForModelDynEnt = reinterpret_cast<unsigned __int16* __ptr64>(asset->primaryLightForModelDynEnt);
			h1_asset->nonSunPrimaryLightForModelDynEnt = mem->Alloc<unsigned short>(asset->dpvsDyn.dynEntClientCount[0]);
			for (unsigned int i = 0; i < asset->dpvsDyn.dynEntClientCount[0]; i++)
			{
				h1_asset->nonSunPrimaryLightForModelDynEnt[i] = asset->primaryLightForModelDynEnt[i];
			}

			if (asset->shadowGeom)
			{
				h1_asset->shadowGeom = mem->Alloc<H1::GfxShadowGeometry>(h1_asset->primaryLightCount);
				for (unsigned int i = 0; i < h1_asset->primaryLightCount; i++)
				{
					h1_asset->shadowGeom[i].surfaceCount = asset->shadowGeom[i].surfaceCount;
					h1_asset->shadowGeom[i].smodelCount = asset->shadowGeom[i].smodelCount;

					h1_asset->shadowGeom[i].sortedSurfIndex = mem->Alloc<unsigned int>(h1_asset->shadowGeom[i].surfaceCount);
					for (unsigned int j = 0; j < h1_asset->shadowGeom[i].surfaceCount; j++)
					{
						h1_asset->shadowGeom[i].sortedSurfIndex[j] = asset->shadowGeom[i].sortedSurfIndex[j];
					}
					REINTERPRET_CAST_SAFE(h1_asset->shadowGeom[i].smodelIndex, asset->shadowGeom[i].smodelIndex);
				}
			}
			h1_asset->shadowGeomOptimized = nullptr;

			h1_asset->lightRegion = mem->Alloc<H1::GfxLightRegion>(h1_asset->primaryLightCount);
			for (unsigned int i = 0; i < h1_asset->primaryLightCount; i++)
			{
				h1_asset->lightRegion[i].hullCount = asset->lightRegion[i].hullCount;
				h1_asset->lightRegion[i].hulls = mem->Alloc<H1::GfxLightRegionHull>(h1_asset->lightRegion[i].hullCount);
				for (unsigned int j = 0; j < h1_asset->lightRegion[i].hullCount; j++)
				{
					memcpy(&h1_asset->lightRegion[i].hulls[j].kdopMidPoint, &asset->lightRegion[i].hulls[j].kdopMidPoint, sizeof(float[9]));
					memcpy(&h1_asset->lightRegion[i].hulls[j].kdopHalfSize, &asset->lightRegion[i].hulls[j].kdopHalfSize, sizeof(float[9]));

					h1_asset->lightRegion[i].hulls[j].axisCount = asset->lightRegion[i].hulls[j].axisCount;
					REINTERPRET_CAST_SAFE(h1_asset->lightRegion[i].hulls[j].axis, asset->lightRegion[i].hulls[j].axis);
				}
			}

			unsigned int lit_decal_count = asset->dpvs.staticSurfaceCount - asset->dpvs.staticSurfaceCountNoDecal;

			h1_asset->dpvs.smodelCount = asset->dpvs.smodelCount;
			h1_asset->dpvs.subdivVertexLightingInfoCount = 0;
			h1_asset->dpvs.staticSurfaceCount = asset->dpvs.staticSurfaceCountNoDecal + lit_decal_count;
			h1_asset->dpvs.litOpaqueSurfsBegin = asset->dpvs.litOpaqueSurfsBegin;
			h1_asset->dpvs.litOpaqueSurfsEnd = asset->dpvs.litOpaqueSurfsEnd;
			h1_asset->dpvs.unkSurfsBegin = 0;
			h1_asset->dpvs.unkSurfsEnd = 0;
			h1_asset->dpvs.litDecalSurfsBegin = asset->dpvs.litOpaqueSurfsEnd; // skip
			h1_asset->dpvs.litDecalSurfsEnd = asset->dpvs.litOpaqueSurfsEnd; // skip
			h1_asset->dpvs.litTransSurfsBegin = asset->dpvs.litTransSurfsBegin;
			h1_asset->dpvs.litTransSurfsEnd = asset->dpvs.litTransSurfsEnd;
			h1_asset->dpvs.shadowCasterSurfsBegin = asset->dpvs.shadowCasterSurfsBegin;
			h1_asset->dpvs.shadowCasterSurfsEnd = asset->dpvs.shadowCasterSurfsEnd;
			h1_asset->dpvs.emissiveSurfsBegin = asset->dpvs.emissiveSurfsBegin;
			h1_asset->dpvs.emissiveSurfsEnd = asset->dpvs.emissiveSurfsEnd;
			h1_asset->dpvs.smodelVisDataCount = asset->dpvs.smodelVisDataCount;
			h1_asset->dpvs.surfaceVisDataCount = asset->dpvs.surfaceVisDataCount;

			for (auto i = 0; i < 4; i++)
			{
				h1_asset->dpvs.smodelVisData[i] = mem->Alloc<unsigned int>(h1_asset->dpvs.smodelVisDataCount);
			}

			for (auto i = 0; i < 4; i++)
			{
				h1_asset->dpvs.surfaceVisData[i] = mem->Alloc<unsigned int>(h1_asset->dpvs.surfaceVisDataCount);
			}

			for (auto i = 0; i < 3; i++)
			{
				//memcpy(h1_asset->dpvs.smodelVisData[i], asset->dpvs.smodelVisData[i], sizeof(int) * h1_asset->dpvs.smodelVisDataCount);
				//memcpy(h1_asset->dpvs.surfaceVisData[i], asset->dpvs.surfaceVisData[i], sizeof(int) * h1_asset->dpvs.surfaceVisDataCount);
			}

			for (auto i = 0; i < 27; i++)
			{
				h1_asset->dpvs.smodelUnknownVisData[i] = mem->Alloc<unsigned int>(h1_asset->dpvs.smodelVisDataCount);
			}

			for (auto i = 0; i < 27; i++)
			{
				h1_asset->dpvs.surfaceUnknownVisData[i] = mem->Alloc<unsigned int>(h1_asset->dpvs.surfaceVisDataCount);
			}

			for (auto i = 0; i < 4; i++)
			{
				h1_asset->dpvs.smodelUmbraVisData[i] = mem->Alloc<unsigned int>(h1_asset->dpvs.smodelVisDataCount);
			}

			for (auto i = 0; i < 4; i++)
			{
				h1_asset->dpvs.surfaceUmbraVisData[i] = mem->Alloc<unsigned int>(h1_asset->dpvs.surfaceVisDataCount);
			}

			h1_asset->dpvs.unknownSModelVisData1 = mem->Alloc<unsigned int>(h1_asset->dpvs.smodelVisDataCount);
			h1_asset->dpvs.unknownSModelVisData2 = mem->Alloc<unsigned int>(h1_asset->dpvs.smodelVisDataCount * 2);

			h1_asset->dpvs.lodData = mem->Alloc<unsigned int>(h1_asset->dpvs.smodelCount + 1);
			h1_asset->dpvs.tessellationCutoffVisData = mem->Alloc<unsigned int>(h1_asset->dpvs.surfaceVisDataCount);

			h1_asset->dpvs.sortedSurfIndex = mem->Alloc<unsigned int>(h1_asset->dpvs.staticSurfaceCount);
			for (unsigned int i = 0; i < h1_asset->dpvs.staticSurfaceCount; i++)
			{
				h1_asset->dpvs.sortedSurfIndex[i] = asset->dpvs.sortedSurfIndex[i];
			}

			REINTERPRET_CAST_SAFE(h1_asset->dpvs.smodelInsts, asset->dpvs.smodelInsts);

			h1_asset->dpvs.surfaces = mem->Alloc<H1::GfxSurface>(h1_asset->surfaceCount);
			for (unsigned int i = 0; i < h1_asset->surfaceCount; i++)
			{
				h1_asset->dpvs.surfaces[i].tris.vertexLayerData = asset->dpvs.surfaces[i].tris.vertexLayerData;
				h1_asset->dpvs.surfaces[i].tris.firstVertex = asset->dpvs.surfaces[i].tris.firstVertex;
				h1_asset->dpvs.surfaces[i].tris.maxEdgeLength = 0;
				h1_asset->dpvs.surfaces[i].tris.unk = -1;
				h1_asset->dpvs.surfaces[i].tris.vertexCount = asset->dpvs.surfaces[i].tris.vertexCount;
				h1_asset->dpvs.surfaces[i].tris.triCount = asset->dpvs.surfaces[i].tris.triCount;
				h1_asset->dpvs.surfaces[i].tris.baseIndex = asset->dpvs.surfaces[i].tris.baseIndex;
				h1_asset->dpvs.surfaces[i].material = reinterpret_cast<H1::Material * __ptr64>(asset->dpvs.surfaces[i].material);
				h1_asset->dpvs.surfaces[i].laf.fields.lightmapIndex = asset->dpvs.surfaces[i].lightmapIndex;
				h1_asset->dpvs.surfaces[i].laf.fields.reflectionProbeIndex = asset->dpvs.surfaces[i].reflectionProbeIndex;
				h1_asset->dpvs.surfaces[i].laf.fields.primaryLightEnvIndex = asset->dpvs.surfaces[i].primaryLightIndex;
				h1_asset->dpvs.surfaces[i].laf.fields.flags = asset->dpvs.surfaces[i].flags;
			}

			h1_asset->dpvs.surfacesBounds = mem->Alloc<H1::GfxSurfaceBounds>(h1_asset->surfaceCount);
			for (unsigned int i = 0; i < h1_asset->surfaceCount; i++)
			{
				memcpy(&h1_asset->dpvs.surfacesBounds[i].bounds, &asset->dpvs.surfacesBounds[i].bounds, sizeof(IW5::Bounds));
				h1_asset->dpvs.surfacesBounds[i].__pad0; // idk
			}

			h1_asset->dpvs.smodelDrawInsts = mem->Alloc<H1::GfxStaticModelDrawInst>(h1_asset->dpvs.smodelCount);
			for (unsigned int i = 0; i < h1_asset->dpvs.smodelCount; i++)
			{
				memcpy(&h1_asset->dpvs.smodelDrawInsts[i].placement, &asset->dpvs.smodelDrawInsts[i].placement, sizeof(IW5::GfxPackedPlacement));
				h1_asset->dpvs.smodelDrawInsts[i].model = reinterpret_cast<H1::XModel * __ptr64>(asset->dpvs.smodelDrawInsts[i].model);
				h1_asset->dpvs.smodelDrawInsts[i].lightingHandle = asset->dpvs.smodelDrawInsts[i].lightingHandle;
				h1_asset->dpvs.smodelDrawInsts[i].staticModelId = 0;
				h1_asset->dpvs.smodelDrawInsts[i].primaryLightEnvIndex = asset->dpvs.smodelDrawInsts[i].primaryLightIndex;
				h1_asset->dpvs.smodelDrawInsts[i].reflectionProbeIndex = asset->dpvs.smodelDrawInsts[i].reflectionProbeIndex;
				h1_asset->dpvs.smodelDrawInsts[i].firstMtlSkinIndex = asset->dpvs.smodelDrawInsts[i].firstMtlSkinIndex;
				h1_asset->dpvs.smodelDrawInsts[i].sunShadowFlags = 1;

				h1_asset->dpvs.smodelDrawInsts[i].cullDist = asset->dpvs.smodelDrawInsts[i].cullDist;
				h1_asset->dpvs.smodelDrawInsts[i].unk0 = h1_asset->dpvs.smodelDrawInsts[i].cullDist;
				h1_asset->dpvs.smodelDrawInsts[i].unk1 = 0;

				// casts no shadows
				auto no_shadows = (asset->dpvs.smodelDrawInsts[i].flags & 0x10) != 0;
				if (no_shadows)
				{
					h1_asset->dpvs.smodelDrawInsts[i].flags |= H1::StaticModelFlag::STATIC_MODEL_FLAG_NO_CAST_SHADOW;
				}

				// ground lighting
				auto ground_lighting = (asset->dpvs.smodelDrawInsts[i].flags & 0x20) != 0 || asset->dpvs.smodelDrawInsts[i].groundLighting.packed != 0;
				if (ground_lighting)
				{
					h1_asset->dpvs.smodelDrawInsts[i].flags |= H1::StaticModelFlag::STATIC_MODEL_FLAG_GROUND_LIGHTING;
				}
				// regular lighting
				else
				{
					h1_asset->dpvs.smodelDrawInsts[i].flags |= H1::StaticModelFlag::STATIC_MODEL_FLAG_LIGHTGRID_LIGHTING;
				}
			}

			h1_asset->dpvs.smodelLighting = mem->Alloc<H1::GfxStaticModelLighting>(h1_asset->dpvs.smodelCount);
			for (unsigned int i = 0; i < h1_asset->dpvs.smodelCount; i++)
			{
				if ((h1_asset->dpvs.smodelDrawInsts[i].flags & H1::StaticModelFlag::STATIC_MODEL_FLAG_GROUND_LIGHTING) != 0)
				{
					h1_asset->dpvs.smodelLighting[i].modelGroundLightingInfo.groundLighting[0] = 14340; // r
					h1_asset->dpvs.smodelLighting[i].modelGroundLightingInfo.groundLighting[1] = 14340; // g
					h1_asset->dpvs.smodelLighting[i].modelGroundLightingInfo.groundLighting[2] = 14340; // b
					h1_asset->dpvs.smodelLighting[i].modelGroundLightingInfo.groundLighting[3] = 14340; // a
				}
				else if ((h1_asset->dpvs.smodelDrawInsts[i].flags & H1::StaticModelFlag::STATIC_MODEL_FLAG_LIGHTGRID_LIGHTING) != 0)
				{
					// fixme
					h1_asset->dpvs.smodelLighting[i].modelLightGridLightingInfo.lighting[0] = 14340; // r
					h1_asset->dpvs.smodelLighting[i].modelLightGridLightingInfo.lighting[1] = 14340; // g
					h1_asset->dpvs.smodelLighting[i].modelLightGridLightingInfo.lighting[2] = 14340; // b
					//h1_asset->dpvs.smodelLighting[i].modelLightGridLightingInfo.lighting[3] = 14340; // a
					//h1_asset->dpvs.smodelLighting[i].modelLightGridLightingInfo.a = 47280;
					//h1_asset->dpvs.smodelLighting[i].modelLightGridLightingInfo.b = 1.0f;

					// todo?
				}
				else if ((h1_asset->dpvs.smodelDrawInsts[i].flags & H1::StaticModelFlag::STATIC_MODEL_FLAG_LIGHTMAP_LIGHTING) != 0)
				{
					// todo?
				}
				else if ((h1_asset->dpvs.smodelDrawInsts[i].flags & H1::StaticModelFlag::STATIC_MODEL_FLAG_VERTEXLIT_LIGHTING) != 0)
				{
					// todo?
				}
			}

			h1_asset->dpvs.subdivVertexLighting = nullptr;

			h1_asset->dpvs.surfaceMaterials = mem->Alloc<H1::GfxDrawSurf>(h1_asset->surfaceCount);
			for (unsigned int i = 0; i < h1_asset->surfaceCount; i++) // these are probably wrong
			{
				h1_asset->dpvs.surfaceMaterials[i].fields.objectId = asset->dpvs.surfaceMaterials[i].fields.objectId;
				h1_asset->dpvs.surfaceMaterials[i].fields.reflectionProbeIndex = asset->dpvs.surfaceMaterials[i].fields.reflectionProbeIndex;
				h1_asset->dpvs.surfaceMaterials[i].fields.hasGfxEntIndex = asset->dpvs.surfaceMaterials[i].fields.hasGfxEntIndex;
				h1_asset->dpvs.surfaceMaterials[i].fields.customIndex = asset->dpvs.surfaceMaterials[i].fields.customIndex;
				h1_asset->dpvs.surfaceMaterials[i].fields.materialSortedIndex = asset->dpvs.surfaceMaterials[i].fields.materialSortedIndex;
				h1_asset->dpvs.surfaceMaterials[i].fields.tessellation = 0;
				h1_asset->dpvs.surfaceMaterials[i].fields.prepass = asset->dpvs.surfaceMaterials[i].fields.prepass;
				h1_asset->dpvs.surfaceMaterials[i].fields.useHeroLighting = asset->dpvs.surfaceMaterials[i].fields.useHeroLighting;
				h1_asset->dpvs.surfaceMaterials[i].fields.sceneLightEnvIndex = asset->dpvs.surfaceMaterials[i].fields.sceneLightIndex;
				h1_asset->dpvs.surfaceMaterials[i].fields.viewModelRender = asset->dpvs.surfaceMaterials[i].fields.viewModelRender;
				h1_asset->dpvs.surfaceMaterials[i].fields.surfType = asset->dpvs.surfaceMaterials[i].fields.surfType;
				h1_asset->dpvs.surfaceMaterials[i].fields.primarySortKey = asset->dpvs.surfaceMaterials[i].fields.primarySortKey;
				h1_asset->dpvs.surfaceMaterials[i].fields.unused = asset->dpvs.surfaceMaterials[i].fields.unused;
			}

			REINTERPRET_CAST_SAFE(h1_asset->dpvs.surfaceCastsSunShadow, asset->dpvs.surfaceCastsSunShadow);
			//h1_asset->dpvs.sunShadowOptCount = 1;
			//h1_asset->dpvs.sunSurfVisDataCount = h1_asset->dpvs.surfaceVisDataCount * 8;
			//h1_asset->dpvs.surfaceCastsSunShadowOpt = mem->Alloc<unsigned int>(h1_asset->dpvs.sunShadowOptCount * h1_asset->dpvs.sunSurfVisDataCount);
			//memcpy(h1_asset->dpvs.surfaceCastsSunShadowOpt, h1_asset->dpvs.surfaceCastsSunShadow, sizeof(int) * (h1_asset->dpvs.sunShadowOptCount * h1_asset->dpvs.sunSurfVisDataCount));
			h1_asset->dpvs.surfaceDeptAndSurf = mem->Alloc<H1::GfxDepthAndSurf>(h1_asset->dpvs.staticSurfaceCount); // todo?
			h1_asset->dpvs.constantBuffersLit = mem->Alloc<char* __ptr64>(h1_asset->dpvs.smodelCount); //nullptr;
			h1_asset->dpvs.constantBuffersAmbient = mem->Alloc<char* __ptr64>(h1_asset->dpvs.smodelCount); //nullptr;
			h1_asset->dpvs.usageCount = asset->dpvs.usageCount;

			h1_asset->dpvsDyn.dynEntClientWordCount[0] = asset->dpvsDyn.dynEntClientWordCount[0];
			h1_asset->dpvsDyn.dynEntClientWordCount[1] = asset->dpvsDyn.dynEntClientWordCount[1];
			h1_asset->dpvsDyn.dynEntClientCount[0] = asset->dpvsDyn.dynEntClientCount[0];
			h1_asset->dpvsDyn.dynEntClientCount[1] = asset->dpvsDyn.dynEntClientCount[1];
			h1_asset->dpvsDyn.dynEntCellBits[0] = reinterpret_cast<unsigned int* __ptr64>(asset->dpvsDyn.dynEntCellBits[0]);
			h1_asset->dpvsDyn.dynEntCellBits[1] = reinterpret_cast<unsigned int* __ptr64>(asset->dpvsDyn.dynEntCellBits[1]);
			h1_asset->dpvsDyn.dynEntVisData[0][0] = reinterpret_cast<unsigned char* __ptr64>(asset->dpvsDyn.dynEntVisData[0][0]);
			h1_asset->dpvsDyn.dynEntVisData[0][1] = reinterpret_cast<unsigned char* __ptr64>(asset->dpvsDyn.dynEntVisData[0][1]);
			h1_asset->dpvsDyn.dynEntVisData[0][2] = reinterpret_cast<unsigned char* __ptr64>(asset->dpvsDyn.dynEntVisData[0][2]);
			h1_asset->dpvsDyn.dynEntVisData[0][3] = mem->Alloc<unsigned char>(h1_asset->dpvsDyn.dynEntClientWordCount[0] * 32);
			h1_asset->dpvsDyn.dynEntVisData[1][0] = reinterpret_cast<unsigned char* __ptr64>(asset->dpvsDyn.dynEntVisData[1][0]);
			h1_asset->dpvsDyn.dynEntVisData[1][1] = reinterpret_cast<unsigned char* __ptr64>(asset->dpvsDyn.dynEntVisData[1][1]);
			h1_asset->dpvsDyn.dynEntVisData[1][2] = reinterpret_cast<unsigned char* __ptr64>(asset->dpvsDyn.dynEntVisData[1][2]);
			h1_asset->dpvsDyn.dynEntVisData[1][3] = mem->Alloc<unsigned char>(h1_asset->dpvsDyn.dynEntClientWordCount[1] * 32);

			h1_asset->mapVtxChecksum = asset->mapVtxChecksum;

			h1_asset->heroOnlyLightCount = asset->heroLightCount;
			REINTERPRET_CAST_SAFE(h1_asset->heroOnlyLights, asset->heroLights);

			h1_asset->fogTypesAllowed = asset->fogTypesAllowed;

			h1_asset->umbraTomeSize = 0;
			h1_asset->umbraTomeData = nullptr;
			h1_asset->umbraTomePtr = nullptr;

			h1_asset->mdaoVolumesCount = 0;
			h1_asset->mdaoVolumes = nullptr;

			// pad3 unknown data

			h1_asset->buildInfo.args0 = nullptr;
			h1_asset->buildInfo.args1 = nullptr;
			h1_asset->buildInfo.buildStartTime = nullptr;
			h1_asset->buildInfo.buildEndTime = nullptr;

			return h1_asset;
		}

		void IGfxWorld::dump(GfxWorld* asset, ZoneMemory* mem)
		{
			// generate h1 gfxworld
			auto h1_asset = GenerateH1GfxWorld(asset, mem);

			// dump h1 gfxworld
			H1::IGfxWorld::dump(h1_asset);
		}
	}
}