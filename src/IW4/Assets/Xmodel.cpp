// ======================= ZoneTool =======================
// zonetool, a fastfile linker for various
// Call of Duty titles. 
//
// Project: https://github.com/ZoneTool/zonetool
// Author: RektInator (https://github.com/RektInator)
// License: GNU GPL v3.0
// ========================================================
#include "stdafx.hpp"
#include "IW5/Assets/XModel.hpp"

namespace ZoneTool
{
	namespace IW4
	{
		XModel* IXModel::parse(std::string name, ZoneMemory* mem)
		{
			return reinterpret_cast<XModel*>(IW5::IXModel::parse(name, mem, SL_AllocString));
		}

		void IXModel::init(const std::string& name, ZoneMemory* mem)
		{
			this->name_ = name;
			this->asset_ = this->parse(name, mem);

			if (!this->asset_)
			{
				this->asset_ = DB_FindXAssetHeader(this->type(), this->name_.data()).xmodel;
			}
		}

		void IXModel::prepare(ZoneBuffer* buf, ZoneMemory* mem)
		{
			// fixup scriptstrings
			auto xmodel = mem->Alloc<XModel>();
			memcpy(xmodel, this->asset_, sizeof XModel);

			// allocate bonenames
			if (this->asset_->boneNames)
			{
				xmodel->boneNames = mem->Alloc<short>(xmodel->numBones);
				memcpy(xmodel->boneNames, this->asset_->boneNames, sizeof(short) * xmodel->numBones);

				for (int i = 0; i < xmodel->numBones; i++)
				{
					if (xmodel->boneNames[i])
					{
						std::string bone = SL_ConvertToString(this->asset_->boneNames[i]);
						xmodel->boneNames[i] = buf->write_scriptstring(bone);
					}
				}
			}

			this->asset_ = xmodel;
		}

		void IXModel::load_depending(IZone* zone)
		{
			auto data = this->asset_;

			// Materials
			for (std::int32_t i = 0; i < data->numSurfaces; i++)
			{
				if (data->materials[i])
				{
					zone->add_asset_of_type(material, data->materials[i]->name);
				}
			}

			// XSurfaces
			for (std::int32_t i = 0; i < 4; i++)
			{
				if (data->lods[i].surfaces)
				{
					zone->add_asset_of_type(xmodelsurfs, data->lods[i].surfaces->name);
				}
			}

			// PhysCollmap
			if (data->physCollmap)
			{
				zone->add_asset_of_type(phys_collmap, data->physCollmap->name);
			}

			// PhysPreset
			if (data->physPreset)
			{
				zone->add_asset_of_type(physpreset, data->physPreset->name);
			}
		}

		std::string IXModel::name()
		{
			return this->name_;
		}

		std::int32_t IXModel::type()
		{
			return xmodel;
		}

		void IXModel::write(IZone* zone, ZoneBuffer* buf)
		{
			auto data = this->asset_;
			auto dest = buf->write<XModel>(data);

			//assert(sizeof XModel, 304);

			buf->push_stream(3);
			START_LOG_STREAM;

			dest->name = buf->write_str(this->name());

			if (data->boneNames)
			{
				buf->align(1);
				buf->write(data->boneNames, data->numBones);
				ZoneBuffer::clear_pointer(&dest->boneNames);
			}

			if (data->parentList)
			{
				buf->align(0);
				buf->write(data->parentList, data->numBones - data->numRootBones);
				ZoneBuffer::clear_pointer(&dest->parentList);
			}

			if (data->tagAngles)
			{
				buf->align(1);
				buf->write(data->tagAngles, data->numBones - data->numRootBones);
				ZoneBuffer::clear_pointer(&dest->tagAngles);
			}

			if (data->tagPositions)
			{
				buf->align(3);
				buf->write(data->tagPositions, data->numBones - data->numRootBones);
				ZoneBuffer::clear_pointer(&dest->tagPositions);
			}

			if (data->partClassification)
			{
				buf->align(0);
				buf->write(data->partClassification, data->numBones);
				ZoneBuffer::clear_pointer(&dest->partClassification);
			}

			if (data->animMatrix)
			{
				buf->align(3);
				buf->write(data->animMatrix, data->numBones);
				ZoneBuffer::clear_pointer(&dest->animMatrix);
			}

			if (data->materials)
			{
				buf->align(3);

				auto destMaterials = buf->write(data->materials, data->numSurfaces);
				for (int i = 0; i < data->numSurfaces; i++)
				{
					destMaterials[i] = reinterpret_cast<Material*>(zone->get_asset_pointer(
						material, data->materials[i]->name));
				}

				ZoneBuffer::clear_pointer(&dest->materials);
			}

			for (int i = 0; i < 4; i++)
			{
				if (!data->lods[i].surfaces) continue;
				dest->lods[i].surfaces = reinterpret_cast<XModelSurfs*>(zone->get_asset_pointer(
					xmodelsurfs, data->lods[i].surfaces->name));

				//if (data->lods[i].surfaces && dependingSurfaces[i])
				//{
				//	buf->push_stream(0);
				//	buf->align(3);
				//	dependingSurfaces[i]->write(zone, buf);
				//	buf->pop_stream();

				//	//ZoneBuffer::clear_pointer(&dest->lods[i].surfaces);
				//	//delete[] dependingSurfaces[i];

				//	dest->lods[i].numSurfacesInLod = data->lods[i].surfaces->xSurficiesCount;
				//	dest->lods[i].surfaces = (ModelSurface*)-1;
				//}
				//else
				//{
				//	dest->lods[i].surfaces = nullptr;
				//}
			}

			if (data->colSurf)
			{
				buf->align(3);
				auto destSurf = buf->write(data->colSurf, data->numColSurfs);

				for (int i = 0; i < data->numColSurfs; i++)
				{
					destSurf[i].tris = buf->write_s(3, data->colSurf[i].tris, data->colSurf[i].numCollTris);
				}

				ZoneBuffer::clear_pointer(&dest->colSurf);
			}

			if (data->boneInfo)
			{
				buf->align(3);
				buf->write(data->boneInfo, data->numBones);
				ZoneBuffer::clear_pointer(&dest->boneInfo);
			}

			if (data->physCollmap)
			{
				dest->physCollmap = reinterpret_cast<PhysCollmap*>(zone->get_asset_pointer(
					phys_collmap, data->physCollmap->name));
			}

			if (data->physPreset)
			{
				dest->physPreset = reinterpret_cast<PhysPreset*>(zone->get_asset_pointer(
					physpreset, data->physPreset->name));
			}

			END_LOG_STREAM;
			buf->pop_stream();
		}
		
		zonetool::XModel* IXModel::ConvertXModel(XModel* asset)
		{
			const auto name = reinterpret_cast<std::uint64_t>(asset->name);
			auto xmodel = new zonetool::XModel{
				.name = name,
			};

			xmodel->numBones = asset->numBones;
			xmodel->numRootBones = asset->numRootBones;
			xmodel->numsurfs = asset->numSurfaces;
			xmodel->lodRampType = asset->lodRampType;
			xmodel->numBonePhysics = 0;
			xmodel->numCompositeModels = 0;
			xmodel->scale = 1.0;

			zonetool::scr_string_t* boneNames = new zonetool::scr_string_t[asset->numBones]();
			for (int b = 0; b < asset->numBones; b++) {
				boneNames[b] = static_cast<zonetool::scr_string_t>(asset->boneNames[b]);
			}
			xmodel->boneNames = reinterpret_cast<std::uint64_t>(asset->boneNames);

			unsigned char* parentList = new unsigned char[asset->numBones - asset->numRootBones]();
			memcpy(parentList, asset->parentList, (asset->numBones - asset->numRootBones) * sizeof(char));
			xmodel->parentList = reinterpret_cast<std::uint64_t>(parentList);

			int numChildBones = asset->numBones - asset->numRootBones;
			auto tagAngles = new zonetool::XModelAngle[numChildBones]();
			auto tagPositions = new zonetool::XModelTagPos[numChildBones]();
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
			auto baseMat = new zonetool::DObjAnimMat[asset->numBones]();
			for (int i = 0; i < asset->numBones; i++) {
				partClassification[i] = asset->partClassification[i];
				memcpy(baseMat[i].quat, asset->animMatrix[i].quat, sizeof(DObjAnimMat::quat));
				memcpy(baseMat[i].trans, asset->animMatrix[i].trans, sizeof(DObjAnimMat::trans));
				baseMat[i].transWeight = asset->animMatrix[i].transWeight;
			}
			xmodel->partClassification = reinterpret_cast<std::uint64_t>(partClassification);
			xmodel->baseMat = reinterpret_cast<std::uint64_t>(baseMat);

			auto materialHandles = new zonetool::Material * [asset->numSurfaces]();
			for (int i = 0; i < asset->numSurfaces; i++) {
				auto name = reinterpret_cast<std::uint64_t>(asset->materials[i]->name);
				materialHandles[i] = new zonetool::Material{
					.name = name
				};
			}
			xmodel->materialHandles = reinterpret_cast<std::uint64_t>(materialHandles);

			auto& lodInfo = xmodel->lodInfo;
			for (int i = 0; i < 4; i++) {
				lodInfo[i].dist = asset->lods[i].dist;
				lodInfo[i].numsurfs = asset->lods[i].numSurfacesInLod;
				lodInfo[i].surfIndex = asset->lods[i].surfIndex;
				lodInfo[i].surfs = 0;
				auto surfs = new zonetool::XSurface[lodInfo[i].numsurfs]();

				if (asset->lods[i].surfaces) {
					for (int j = 0; j < asset->lods[i].surfaces->numsurfs; j++) {
						IXSurface::ConvertXSurface(&surfs[j], &asset->lods[i].surfaces->surfs[j]);
					}

					auto modelSurfs = new zonetool::XModelSurfs{
						.name = reinterpret_cast<std::uint64_t>(asset->lods[i].surfaces->name),
						.surfs = reinterpret_cast<std::uint64_t>(surfs),
						.numsurfs = asset->lods[i].surfaces->numsurfs,
						.partBits = {0},
					};

					lodInfo[i].modelSurfs = reinterpret_cast<std::uint64_t>(modelSurfs);
				}
			}

			return xmodel;
		}

		void IXModel::dump(XModel* asset, const std::function<const char*(uint16_t)>& convertToString)
		{
			zonetool::XModel* converted_asset = ConvertXModel(asset);
			dump_converted(converted_asset, convertToString);
		}

		void IXModel::dump_converted(zonetool::XModel* asset, const std::function<const char* (std::uint16_t)>& convertToString)
		{
			const char* name = reinterpret_cast<const char*>(asset->name);
			const auto path = "xmodel\\"s + name + ".xmodel_export";

			AssetDumper dump;
			if (!dump.open(path))
			{
				return;
			}

			// asset
			dump.dump_single(asset);
			dump.dump_string(name);

			// tags
			auto boneNames = reinterpret_cast<zonetool::scr_string_t*>(asset->boneNames);
			dump.dump_array(boneNames, asset->numBones);
			for (unsigned char i = 0; i < asset->numBones; i++)
			{
				dump.dump_string(convertToString(boneNames[i]));
			}

			// basic info
			auto parentList = reinterpret_cast<unsigned char*>(asset->parentList);
			auto tagAngles = reinterpret_cast<zonetool::XModelAngle*>(asset->tagAngles);
			auto tagPositions = reinterpret_cast<zonetool::XModelTagPos*>(asset->tagPositions);
			auto partClassification = reinterpret_cast<unsigned char*>(asset->partClassification);
			auto baseMat = reinterpret_cast<zonetool::DObjAnimMat*>(asset->baseMat);
			auto reactiveMotionTweaks = reinterpret_cast<zonetool::ReactiveMotionModelTweaks*>(asset->reactiveMotionTweaks);
			auto collSurfs = reinterpret_cast<zonetool::XModelCollSurf_s*>(asset->collSurfs);
			auto boneInfo = reinterpret_cast<zonetool::XBoneInfo*>(asset->boneInfo);
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
			auto materialHandles = reinterpret_cast<zonetool::Material**>(asset->materialHandles);
			dump.dump_array(materialHandles, asset->numsurfs);
			for (unsigned char i = 0; i < asset->numsurfs; i++)
			{
				dump.dump_asset(materialHandles[i]);
			}

			// lods
			auto lodInfo = reinterpret_cast<zonetool::XModelLodInfo*>(asset->lodInfo);
			for (auto i = 0; i < 6; i++)
			{
				auto modelSurfs = reinterpret_cast<zonetool::XModelSurfs*>(lodInfo[i].modelSurfs);
				dump.dump_asset(modelSurfs);
			}

			// physics subassets
			auto physPreset = reinterpret_cast<zonetool::PhysPreset*>(asset->physPreset);
			auto physCollmap = reinterpret_cast<zonetool::PhysCollmap*>(asset->physCollmap);
			dump.dump_asset(physPreset);
			dump.dump_asset(physCollmap);

			// weights
			auto weightNames = reinterpret_cast<zonetool::scr_string_t*>(asset->weightNames);
			dump.dump_array(weightNames, asset->numberOfWeights);
			for (unsigned short i = 0; i < asset->numberOfWeights; i++)
			{
				dump.dump_string(convertToString(weightNames[i]));
			}

			// blendshapeweights
			auto blendShapeWeightMap = reinterpret_cast<zonetool::BlendShapeWeightMap*>(asset->blendShapeWeightMap);
			dump.dump_array(blendShapeWeightMap, asset->numberOfWeightMaps);

			// mdao
			auto mdaoVolumes = reinterpret_cast<zonetool::MdaoVolume*>(asset->mdaoVolumes);
			dump.dump_array(mdaoVolumes, asset->mdaoVolumeCount);
			for (auto i = 0; i < asset->mdaoVolumeCount; i++)
			{
				auto volumeData = reinterpret_cast<zonetool::GfxImage*>(mdaoVolumes->volumeData);
				dump.dump_asset(volumeData);
			}

			// extra models
			auto compositeModels = reinterpret_cast<zonetool::XModel**>(asset->compositeModels);
			dump.dump_array(compositeModels, asset->numCompositeModels);
			for (char i = 0; i < asset->numCompositeModels; i++)
			{
				dump.dump_asset(compositeModels[i]);
			}

			// skeletonscript subasset
			auto skeletonScript = reinterpret_cast<zonetool::SkeletonScript*>(asset->skeletonScript);
			dump.dump_asset(skeletonScript);

			// bone physics
			auto bonePhysics = reinterpret_cast<zonetool::XPhysBoneInfo*>(asset->bonePhysics);
			dump.dump_array(bonePhysics, asset->numBonePhysics);
			for (char i = 0; i < asset->numBonePhysics; i++)
			{
				auto physPreset = reinterpret_cast<zonetool::PhysPreset*>(bonePhysics[i].physPreset);
				auto physContraint = reinterpret_cast<zonetool::PhysConstraint*>(bonePhysics[i].physContraint);
				auto physCollmap = reinterpret_cast<zonetool::PhysCollmap*>(bonePhysics[i].physCollmap);
				dump.dump_asset(physPreset);
				dump.dump_asset(physContraint);
				dump.dump_asset(physCollmap);
			}

			dump.close();
		}
	}
}
