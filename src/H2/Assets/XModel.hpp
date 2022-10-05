#include "H2/Utils/assetmanager.hpp"

namespace ZoneTool 
{
    namespace H2
    {
        class IXModel
        {
        public:
            static XModel* convert_from_iw4(IW4::XModel* asset)
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
					const char* name = asset->materials[i]->name;
					auto casted_name = reinterpret_cast<std::uint64_t>(name);
					//MaterialInfo info = {
					//	.name = casted_name,
					//};
					materialHandles[i] = new Material{
						.name = casted_name
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
				xmodel->numCollSurfs = asset->numColSurfs;
				xmodel->contents = asset->contents;
				xmodel->radius = asset->radius;

				auto collSurfs = new XModelCollSurf_s[asset->numColSurfs]();
				for (int i = 0; i < asset->numColSurfs; i++) {
					memcpy(collSurfs[i].bounds.halfSize, asset->colSurf[i].bounds.halfSize, sizeof(Bounds::halfSize));
					memcpy(collSurfs[i].bounds.midPoint, asset->colSurf[i].bounds.midPoint, sizeof(Bounds::midPoint));
					collSurfs[i].boneIdx = asset->colSurf[i].boneIdx;
					collSurfs[i].contents = asset->colSurf[i].contents;
					collSurfs[i].surfFlags = asset->colSurf[i].surfFlags;
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
