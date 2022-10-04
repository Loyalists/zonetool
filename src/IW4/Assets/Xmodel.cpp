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
#include <H2/Utils/assetmanager.hpp>
#include <H2/Assets/XSurface.hpp>
#include <H2/Assets/XModel.hpp>

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

		void IXModel::dump(XModel* asset, const std::function<const char*(uint16_t)>& convertToString)
		{
			auto* result = H2::IXModel::convert_from_iw4(asset);
			H2::IXModel::dump(result, convertToString);
		}
	}
}
