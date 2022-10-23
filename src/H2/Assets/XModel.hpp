#include "H2/Utils/assetmanager.hpp"

namespace ZoneTool 
{
    namespace H2
    {
        class IXModel
        {
        public:
			static int convert_surf_flags(int flags)
			{
				H2::CSurfaceFlags surf_flags_conversion_table[31]
				{
					H2::SURF_FLAG_DEFAULT,
					H2::SURF_FLAG_BARK,
					H2::SURF_FLAG_BRICK,
					H2::SURF_FLAG_CARPET,
					H2::SURF_FLAG_CLOTH,
					H2::SURF_FLAG_CONCRETE,
					H2::SURF_FLAG_DIRT,
					H2::SURF_FLAG_FLESH,
					H2::SURF_FLAG_FOLIAGE_DEBRIS,
					H2::SURF_FLAG_GLASS,
					H2::SURF_FLAG_GRASS,
					H2::SURF_FLAG_GRAVEL,
					H2::SURF_FLAG_ICE,
					H2::SURF_FLAG_METAL_SOLID,
					H2::SURF_FLAG_MUD,
					H2::SURF_FLAG_PAPER,
					H2::SURF_FLAG_PLASTER,
					H2::SURF_FLAG_ROCK,
					H2::SURF_FLAG_SAND,
					H2::SURF_FLAG_SNOW,
					H2::SURF_FLAG_WATER_WAIST,
					H2::SURF_FLAG_WOOD_SOLID,
					H2::SURF_FLAG_ASPHALT,
					H2::SURF_FLAG_CERAMIC,
					H2::SURF_FLAG_PLASTIC_SOLID,
					H2::SURF_FLAG_RUBBER,
					H2::SURF_FLAG_CUSHION,
					H2::SURF_FLAG_FRUIT,
					H2::SURF_FLAG_PAINTEDMETAL,
					H2::SURF_FLAG_RIOTSHIELD,
					H2::SURF_FLAG_SLUSH,
				};

				int h1_flags = surf_flags_conversion_table[flags >> 20];
				auto convert = [&](IW4::CSurfaceFlags a, H2::CSurfaceFlags b)
				{
					h1_flags |= ((flags & a) != 0) ? b : 0;
				};
				convert(IW4::CSurfaceFlags::SURF_FLAG_OPAQUEGLASS, H2::CSurfaceFlags::SURF_FLAG_DEFAULT);
				convert(IW4::CSurfaceFlags::SURF_FLAG_CLIPMISSILE, H2::CSurfaceFlags::SURF_FLAG_CLIPMISSILE);
				convert(IW4::CSurfaceFlags::SURF_FLAG_AI_NOSIGHT, H2::CSurfaceFlags::SURF_FLAG_AI_NOSIGHT);
				convert(IW4::CSurfaceFlags::SURF_FLAG_CLIPSHOT, H2::CSurfaceFlags::SURF_FLAG_CLIPSHOT);
				convert(IW4::CSurfaceFlags::SURF_FLAG_PLAYERCLIP, H2::CSurfaceFlags::SURF_FLAG_PLAYERCLIP);
				convert(IW4::CSurfaceFlags::SURF_FLAG_MONSTERCLIP, H2::CSurfaceFlags::SURF_FLAG_MONSTERCLIP);
				convert(IW4::CSurfaceFlags::SURF_FLAG_AICLIPALLOWDEATH, H2::CSurfaceFlags::SURF_FLAG_AICLIPALLOWDEATH);
				convert(IW4::CSurfaceFlags::SURF_FLAG_VEHICLECLIP, H2::CSurfaceFlags::SURF_FLAG_VEHICLECLIP);
				convert(IW4::CSurfaceFlags::SURF_FLAG_ITEMCLIP, H2::CSurfaceFlags::SURF_FLAG_ITEMCLIP);
				convert(IW4::CSurfaceFlags::SURF_FLAG_NODROP, H2::CSurfaceFlags::SURF_FLAG_NODROP);
				convert(IW4::CSurfaceFlags::SURF_FLAG_NONSOLID, H2::CSurfaceFlags::SURF_FLAG_NONSOLID);
				convert(IW4::CSurfaceFlags::SURF_FLAG_DETAIL, H2::CSurfaceFlags::SURF_FLAG_DETAIL);
				convert(IW4::CSurfaceFlags::SURF_FLAG_STRUCTURAL, H2::CSurfaceFlags::SURF_FLAG_STRUCTURAL);
				convert(IW4::CSurfaceFlags::SURF_FLAG_PORTAL, H2::CSurfaceFlags::SURF_FLAG_PORTAL);
				convert(IW4::CSurfaceFlags::SURF_FLAG_CANSHOOTCLIP, H2::CSurfaceFlags::SURF_FLAG_CANSHOOTCLIP);
				convert(IW4::CSurfaceFlags::SURF_FLAG_ORIGIN, H2::CSurfaceFlags::SURF_FLAG_ORIGIN);
				convert(IW4::CSurfaceFlags::SURF_FLAG_SKY, H2::CSurfaceFlags::SURF_FLAG_SKY);
				convert(IW4::CSurfaceFlags::SURF_FLAG_NOCASTSHADOW, H2::CSurfaceFlags::SURF_FLAG_NOCASTSHADOW);
				convert(IW4::CSurfaceFlags::SURF_FLAG_PHYSICSGEOM, H2::CSurfaceFlags::SURF_FLAG_PHYSICSGEOM);
				convert(IW4::CSurfaceFlags::SURF_FLAG_LIGHTPORTAL, H2::CSurfaceFlags::SURF_FLAG_LIGHTPORTAL);
				convert(IW4::CSurfaceFlags::SURF_FLAG_OUTDOORBOUNDS, H2::CSurfaceFlags::SURF_FLAG_OUTDOORBOUNDS);
				convert(IW4::CSurfaceFlags::SURF_FLAG_SLICK, H2::CSurfaceFlags::SURF_FLAG_SLICK);
				convert(IW4::CSurfaceFlags::SURF_FLAG_NOIMPACT, H2::CSurfaceFlags::SURF_FLAG_NOIMPACT);
				convert(IW4::CSurfaceFlags::SURF_FLAG_NOMARKS, H2::CSurfaceFlags::SURF_FLAG_NOMARKS);
				convert(IW4::CSurfaceFlags::SURF_FLAG_NOPENETRATE, H2::CSurfaceFlags::SURF_FLAG_NOPENETRATE);
				convert(IW4::CSurfaceFlags::SURF_FLAG_LADDER, H2::CSurfaceFlags::SURF_FLAG_LADDER);
				convert(IW4::CSurfaceFlags::SURF_FLAG_NODAMAGE, H2::CSurfaceFlags::SURF_FLAG_NODAMAGE);
				convert(IW4::CSurfaceFlags::SURF_FLAG_MANTLEON, H2::CSurfaceFlags::SURF_FLAG_MANTLEON);
				convert(IW4::CSurfaceFlags::SURF_FLAG_MANTLEOVER, H2::CSurfaceFlags::SURF_FLAG_MANTLEOVER);
				convert(IW4::CSurfaceFlags::SURF_FLAG_STAIRS, H2::CSurfaceFlags::SURF_FLAG_STAIRS);
				convert(IW4::CSurfaceFlags::SURF_FLAG_SOFT, H2::CSurfaceFlags::SURF_FLAG_SOFT);
				convert(IW4::CSurfaceFlags::SURF_FLAG_NOSTEPS, H2::CSurfaceFlags::SURF_FLAG_NOSTEPS);
				convert(IW4::CSurfaceFlags::SURF_FLAG_NODRAW, H2::CSurfaceFlags::SURF_FLAG_NODRAW);
				convert(IW4::CSurfaceFlags::SURF_FLAG_NOLIGHTMAP, H2::CSurfaceFlags::SURF_FLAG_NOLIGHTMAP);
				convert(IW4::CSurfaceFlags::SURF_FLAG_NODLIGHT, H2::CSurfaceFlags::SURF_FLAG_NODLIGHT);
				return h1_flags;
			}

            static XModel* convert_from_iw4(IW4::XModel* asset, const std::function<const char* (uint16_t)>& convertToString)
            {
				const auto name = reinterpret_cast<std::uint64_t>(asset->name);
				auto xmodel = new XModel{
					.name = name,
				};

				xmodel->numBones = asset->numBones;
				xmodel->numRootBones = asset->numRootBones;
				xmodel->numsurfs = asset->numSurfaces;
				xmodel->lodRampType = asset->lodRampType;
				xmodel->numBonePhysics = 0;
				xmodel->numCompositeModels = 0;
				xmodel->scale = 1.0;
				xmodel->noScalePartBits[0] = 1065353216;
				//memcpy(xmodel->noScalePartBits, asset->noScalePartBits, sizeof(asset->noScalePartBits));

				scr_string_t* boneNames = new scr_string_t[asset->numBones]();
				for (int b = 0; b < asset->numBones; b++) {
					boneNames[b] = static_cast<scr_string_t>(asset->boneNames[b]);
				}
				xmodel->boneNames = reinterpret_cast<std::uint64_t>(boneNames);

				int numChildBones = asset->numBones - asset->numRootBones;
				unsigned char* parentList = new unsigned char[numChildBones]();
				memcpy(parentList, asset->parentList, numChildBones * sizeof(char));
				xmodel->parentList = reinterpret_cast<std::uint64_t>(parentList);

				auto tagAngles = new XModelAngle[numChildBones]();
				auto tagPositions = new XModelTagPos[numChildBones]();
				for (int i = 0; i < numChildBones; i++) {
					tagAngles[i].x = asset->tagAngles[i].x;
					tagAngles[i].y = asset->tagAngles[i].y;
					tagAngles[i].z = asset->tagAngles[i].z;
					tagAngles[i].base = asset->tagAngles[i].base;

					tagPositions[i].x = asset->tagPositions[i].x;
					tagPositions[i].y = asset->tagPositions[i].y;
					tagPositions[i].z = asset->tagPositions[i].z;
				}
				xmodel->tagAngles = reinterpret_cast<std::uint64_t>(tagAngles);
				xmodel->tagPositions = reinterpret_cast<std::uint64_t>(tagPositions);

				unsigned char* partClassification = new unsigned char[asset->numBones]();
				auto baseMat = new DObjAnimMat[asset->numBones]();
				for (int i = 0; i < asset->numBones; i++) {
					uint16_t boneNameIndex = asset->boneNames[i];
					std::string boneNameString = convertToString(boneNameIndex);
					if (boneNameString == "tag_shield_back" || boneNameString == "tag_weapon_left")
						partClassification[i] = 0x13;
					else
						partClassification[i] = asset->partClassification[i];

					memcpy(baseMat[i].quat, asset->animMatrix[i].quat, sizeof(DObjAnimMat::quat));
					memcpy(baseMat[i].trans, asset->animMatrix[i].trans, sizeof(DObjAnimMat::trans));
					baseMat[i].transWeight = asset->animMatrix[i].transWeight;
				}
				xmodel->partClassification = reinterpret_cast<std::uint64_t>(partClassification);
				xmodel->baseMat = reinterpret_cast<std::uint64_t>(baseMat);

				//auto reactiveMotionTweaks = new ReactiveMotionModelTweaks();
				//xmodel->reactiveMotionTweaks = reinterpret_cast<std::uint64_t>(reactiveMotionTweaks);

				auto materialHandles = new Material * [asset->numSurfaces]();
				for (int i = 0; i < asset->numSurfaces; i++) {
					std::string name_str = asset->materials[i]->name;
					std::string prefix = "mc/";
					int index = name_str.find(prefix);
					if (index != std::string::npos) {
						name_str.replace(index, prefix.length(), "m/");
					}
					const char* name2 = strdup(name_str.c_str());

					materialHandles[i] = new Material{
						.name = reinterpret_cast<std::uint64_t>(name2)
					};
				}
				xmodel->materialHandles = reinterpret_cast<std::uint64_t>(materialHandles);

				auto& lodInfo = xmodel->lodInfo;
				for (int i = 0; i < 6; i++) {
					if (i >= 4) {
						lodInfo[i].modelSurfs = reinterpret_cast<std::uint64_t>(nullptr);
						continue;
					}

					lodInfo[i].dist = asset->lods[i].dist;
					lodInfo[i].numsurfs = asset->lods[i].numSurfacesInLod;
					lodInfo[i].surfIndex = asset->lods[i].surfIndex;
					lodInfo[i].surfs = 0;
					memcpy(lodInfo[i].partBits, asset->lods[i].partBits, sizeof(IW4::XModelLodInfo::partBits));

					if (asset->lods[i].surfaces) {
						auto *modelSurfs = new XModelSurfs{
							.name = reinterpret_cast<std::uint64_t>(asset->lods[i].surfaces->name),
						};

						lodInfo[i].modelSurfs = reinterpret_cast<std::uint64_t>(modelSurfs);
					}
					else {
						lodInfo[i].modelSurfs = reinterpret_cast<std::uint64_t>(nullptr);
					}
				}

				xmodel->numLods = asset->numLods;
				xmodel->collLod = asset->collLod;
				xmodel->flags = asset->flags;
				xmodel->numCollSurfs = asset->numColSurfs;
				xmodel->contents = asset->contents;
				xmodel->radius = asset->radius;

				auto collSurfs = new XModelCollSurf_s[asset->numColSurfs]();
				for (int i = 0; i < asset->numColSurfs; i++) {
					memcpy(collSurfs[i].bounds.halfSize, asset->colSurf[i].bounds.halfSize, sizeof(Bounds::halfSize));
					memcpy(collSurfs[i].bounds.midPoint, asset->colSurf[i].bounds.midPoint, sizeof(Bounds::midPoint));
					collSurfs[i].boneIdx = asset->colSurf[i].boneIdx;
					collSurfs[i].contents = asset->colSurf[i].contents;
					collSurfs[i].surfFlags = convert_surf_flags(asset->colSurf[i].surfFlags);
				}
				xmodel->collSurfs = reinterpret_cast<std::uint64_t>(collSurfs);

				auto boneInfo = new XBoneInfo[asset->numBones]();
				for (int i = 0; i < asset->numBones; i++) {
					float radiusSquared = asset->boneInfo[i].radiusSquared;
					unsigned int radiusSquaredAsInt = round(radiusSquared);
					memcpy(boneInfo[i].bounds.halfSize, asset->boneInfo[i].packedBounds.halfSize, sizeof(Bounds::halfSize));
					memcpy(boneInfo[i].bounds.midPoint, asset->boneInfo[i].packedBounds.midPoint, sizeof(Bounds::midPoint));
					boneInfo[i].radiusSquared = radiusSquared;
				}
				xmodel->boneInfo = reinterpret_cast<std::uint64_t>(boneInfo);

				memcpy(xmodel->bounds.halfSize, asset->bounds.halfSize, sizeof(Bounds::halfSize));
				memcpy(xmodel->bounds.midPoint, asset->bounds.midPoint, sizeof(Bounds::midPoint));

				auto invHighMipRadius = new unsigned short[xmodel->numsurfs]();
				for (int i = 0; i < xmodel->numsurfs; i++) {
					invHighMipRadius[i] = 65535;
				}
				xmodel->invHighMipRadius = reinterpret_cast<std::uint64_t>(invHighMipRadius);

				//std::string name_str = asset->name;
				//if (name_str.find("body") != std::string::npos && name_str.find("viewbody") == std::string::npos) {
				//	auto skeletonScript = new SkeletonScript{
				//		.name = reinterpret_cast<std::uint64_t>("character_sp_footik")
				//	};
				//	xmodel->skeletonScript = reinterpret_cast<std::uint64_t>(skeletonScript);
				//}

				return xmodel;
            }

            static void dump(XModel* asset, const std::function<const char* (std::uint16_t)>& convertToString)
            {
				const char* name = reinterpret_cast<const char*>(asset->name);
				const auto path = "xmodel\\"s + name + ".xmodel_export";

				zonetool::assetmanager::dumper dump;
				if (!dump.open(path))
				{
					return;
				}

				// asset
				dump.dump_single(asset);
				dump.dump_string(name);

				// tags
				auto boneNames = reinterpret_cast<scr_string_t*>(asset->boneNames);
				dump.dump_array(boneNames, asset->numBones);
				for (unsigned char i = 0; i < asset->numBones; i++)
				{
					dump.dump_string(convertToString(boneNames[i]));
				}

				// basic info
				auto parentList = reinterpret_cast<unsigned char*>(asset->parentList);
				auto tagAngles = reinterpret_cast<XModelAngle*>(asset->tagAngles);
				auto tagPositions = reinterpret_cast<XModelTagPos*>(asset->tagPositions);
				auto partClassification = reinterpret_cast<unsigned char*>(asset->partClassification);
				auto baseMat = reinterpret_cast<DObjAnimMat*>(asset->baseMat);
				auto reactiveMotionTweaks = reinterpret_cast<ReactiveMotionModelTweaks*>(asset->reactiveMotionTweaks);
				auto collSurfs = reinterpret_cast<XModelCollSurf_s*>(asset->collSurfs);
				auto boneInfo = reinterpret_cast<XBoneInfo*>(asset->boneInfo);
				auto invHighMipRadius = reinterpret_cast<unsigned short*>(asset->invHighMipRadius);
				dump.dump_array(parentList, asset->numBones - asset->numRootBones);
				dump.dump_array(tagAngles, asset->numBones - asset->numRootBones);
				dump.dump_array(tagPositions, asset->numBones - asset->numRootBones);
				dump.dump_array(partClassification, asset->numBones);
				dump.dump_array(baseMat, asset->numBones);
				dump.dump_single(reactiveMotionTweaks);
				dump.dump_array(collSurfs, asset->numCollSurfs);
				dump.dump_array(boneInfo, asset->numBones);
				dump.dump_array(invHighMipRadius, asset->numsurfs);

				// surfaces
				auto materialHandles = reinterpret_cast<Material**>(asset->materialHandles);
				std::uint64_t* materialHandles_casted = new std::uint64_t[asset->numsurfs]();
				for (unsigned char i = 0; i < asset->numsurfs; i++)
				{
					materialHandles_casted[i] = reinterpret_cast<std::uint64_t>(materialHandles[i]);
				}

				dump.dump_array(materialHandles_casted, asset->numsurfs);
				for (unsigned char i = 0; i < asset->numsurfs; i++)
				{
					auto material = reinterpret_cast<Material*>(materialHandles_casted[i]);
					dump.dump_asset(material);
				}

				delete[] materialHandles_casted;

				// lods
				auto lodInfo = reinterpret_cast<XModelLodInfo*>(asset->lodInfo);
				for (auto i = 0; i < 6; i++)
				{
					auto modelSurfs = reinterpret_cast<XModelSurfs*>(lodInfo[i].modelSurfs);
					dump.dump_asset(modelSurfs);
					dump.dump_array64<XUnknown1>(asset->lodInfo[i].reactiveMotionParts, asset->lodInfo[i].numReactiveMotionParts);
				}

				// physics subassets
				auto physPreset = reinterpret_cast<PhysPreset*>(asset->physPreset);
				auto physCollmap = reinterpret_cast<PhysCollmap*>(asset->physCollmap);
				dump.dump_asset(physPreset);
				dump.dump_asset(physCollmap);

				// weights
				auto weightNames = reinterpret_cast<scr_string_t*>(asset->weightNames);
				dump.dump_array(weightNames, asset->numberOfWeights);
				for (unsigned short i = 0; i < asset->numberOfWeights; i++)
				{
					dump.dump_string(convertToString(weightNames[i]));
				}

				// blendshapeweights
				auto blendShapeWeightMap = reinterpret_cast<BlendShapeWeightMap*>(asset->blendShapeWeightMap);
				dump.dump_array(blendShapeWeightMap, asset->numberOfWeightMaps);

				// mdao
				auto mdaoVolumes = reinterpret_cast<MdaoVolume*>(asset->mdaoVolumes);
				dump.dump_array(mdaoVolumes, asset->mdaoVolumeCount);
				for (auto i = 0; i < asset->mdaoVolumeCount; i++)
				{
					auto volumeData = reinterpret_cast<GfxImage*>(mdaoVolumes->volumeData);
					dump.dump_asset(volumeData);
				}

				// extra models
				auto compositeModels = reinterpret_cast<XModel**>(asset->compositeModels);
				std::uint64_t* compositeModels_casted = nullptr;
				if (asset->numCompositeModels > 0) {
					compositeModels_casted = new std::uint64_t[asset->numCompositeModels]();
					for (unsigned char i = 0; i < asset->numCompositeModels; i++)
					{
						compositeModels_casted[i] = reinterpret_cast<std::uint64_t>(compositeModels[i]);
					}
				}

				dump.dump_array(compositeModels_casted, asset->numCompositeModels);
				for (char i = 0; i < asset->numCompositeModels; i++)
				{
					auto model = reinterpret_cast<XModel*>(compositeModels_casted[i]);
					dump.dump_asset(model);
				}

				if (asset->numCompositeModels > 0) {
					delete[] compositeModels_casted;
				}

				// skeletonscript subasset
				auto skeletonScript = reinterpret_cast<SkeletonScript*>(asset->skeletonScript);
				dump.dump_asset(skeletonScript);

				// bone physics
				auto bonePhysics = reinterpret_cast<XPhysBoneInfo*>(asset->bonePhysics);
				dump.dump_array(bonePhysics, asset->numBonePhysics);
				for (char i = 0; i < asset->numBonePhysics; i++)
				{
					auto physPreset = reinterpret_cast<PhysPreset*>(bonePhysics[i].physPreset);
					auto physContraint = reinterpret_cast<PhysConstraint*>(bonePhysics[i].physContraint);
					auto physCollmap = reinterpret_cast<PhysCollmap*>(bonePhysics[i].physCollmap);
					dump.dump_asset(physPreset);
					dump.dump_asset(physContraint);
					dump.dump_asset(physCollmap);
				}

				//DEBUG
				//ZONETOOL_INFO("parentList: %p", parentList);
				//ZONETOOL_INFO("tagAngles: %p", tagAngles);
				//ZONETOOL_INFO("tagPositions: %p", tagPositions);
				//ZONETOOL_INFO("partClassification: %p", partClassification);
				//ZONETOOL_INFO("baseMat: %p", baseMat);
				//ZONETOOL_INFO("collSurfs: %p", collSurfs);
				//ZONETOOL_INFO("boneInfo: %p", boneInfo);
				//ZONETOOL_INFO("baseMat: %p", baseMat);
				//ZONETOOL_INFO("invHighMipRadius: %p", invHighMipRadius);
				//ZONETOOL_INFO("materialHandles: %p", materialHandles);
				//ZONETOOL_INFO("lodInfo: %p", lodInfo);
				ZONETOOL_INFO("name: %s", name);
				dump.close();
            }
        };
    }
}
