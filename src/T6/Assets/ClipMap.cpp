// ======================= ZoneTool =======================
// zonetool, a fastfile linker for various
// Call of Duty titles. 
//
// Project: https://github.com/ZoneTool/zonetool
// Author: RektInator (https://github.com/RektInator)
// License: GNU GPL v3.0
// ========================================================
#include "stdafx.hpp"

namespace ZoneTool
{
	namespace T6
	{
#define INFO info->

		//void parse_info(ClipInfo* info, AssetReader& read, ZoneMemory* mem)
		//{
		//	INFO numCPlanes = read.read_int();
		//	INFO cPlanes = read.read_array<cplane_s>();

		//	INFO numMaterials = read.read_int();
		//	INFO materials = read.read_array<dmaterial_t>();
		//	for (auto i = 0; i < INFO numMaterials; i++)
		//	{
		//		if (INFO materials[i].material)
		//		{
		//			INFO materials[i].material = read.read_string();
		//		}
		//	}

		//	INFO numCBrushSides = read.read_int();
		//	INFO cBrushSides = read.read_array<cbrushside_t>();
		//	for (auto i = 0; i < INFO numCBrushSides; i++)
		//	{
		//		if (INFO cBrushSides[i].plane)
		//		{
		//			INFO cBrushSides[i].plane = read.read_array<cplane_s>();
		//		}
		//	}

		//	INFO numCBrushEdges = read.read_int();
		//	INFO cBrushEdges = read.read_array<cbrushedge_t>();

		//	INFO numLeafBrushes = read.read_int();
		//	INFO leafBrushes = read.read_array<short>();

		//	INFO numCLeafBrushNodes = read.read_int();
		//	INFO cLeafBrushNodes = read.read_array<cLeafBrushNode_s>();
		//	for (auto i = 0; i < INFO numCLeafBrushNodes; i++)
		//	{
		//		if (INFO cLeafBrushNodes[i].leafBrushCount > 0)
		//		{
		//			INFO cLeafBrushNodes[i].data.leaf.brushes = read.read_array<unsigned short>();
		//		}
		//	}

		//	INFO numBrushes = read.read_int();
		//	INFO brushes = read.read_array<cbrush_t>();
		//	for (auto i = 0; i < INFO numBrushes; i++)
		//	{
		//		if (INFO brushes[i].sides)
		//		{
		//			INFO brushes[i].sides = read.read_array<cbrushside_t>();

		//			if (INFO brushes[i].sides->plane)
		//			{
		//				INFO brushes[i].sides->plane = read.read_array<cplane_s>();
		//			}
		//		}
		//		if (INFO brushes[i].edge)
		//		{
		//			INFO brushes[i].edge = read.read_array<cbrushedge_t>();
		//		}
		//	}

		//	INFO brushBounds = read.read_array<Bounds>();
		//	INFO brushContents = read.read_array<int>();
		//}

#undef INFO
#define INFO info.

//		clipMap_t* IClipMap::parse(const std::string& name, ZoneMemory* mem)
//		{
//			auto path = name + ".colmap";
//
//			if (!FileSystem::FileExists(path))
//			{
//				return nullptr;
//			}
//
//			AssetReader read(mem);
//
//			if (!read.open(path))
//			{
//				return nullptr;
//			}
//
//			ZONETOOL_INFO("Parsing colmap \"%s\"...", name.c_str());
//
//			auto* colmap = mem->Alloc<clipMap_t>();
//
//			colmap->name = read.read_string();
//			colmap->isInUse = read.read_int();
//
//			parse_info(&colmap->info, read, mem);
//
//			colmap->numStaticModels = read.read_int();
//			colmap->staticModelList = read.read_array<cStaticModel_s>();
//			for (auto i = 0; i < colmap->numStaticModels; i++)
//			{
//				if (colmap->staticModelList[i].xmodel)
//				{
//					colmap->staticModelList[i].xmodel = read.read_asset<XModel>();
//				}
//			}
//
//			colmap->numCNodes = read.read_int();
//			colmap->cNodes = read.read_array<cNode_t>();
//			for (auto i = 0; i < colmap->numCNodes; i++)
//			{
//				if (colmap->cNodes[i].plane)
//				{
//					colmap->cNodes[i].plane = read.read_array<cplane_s>();
//				}
//			}
//
//			colmap->numCLeaf = read.read_int();
//			colmap->cLeaf = read.read_array<cLeaf_t>();
//
//			colmap->numVerts = read.read_int();
//			colmap->verts = read.read_array<VecInternal<3>>();
//
//			colmap->numTriIndices = read.read_int();
//			colmap->triIndices = read.read_array<short>();
//			colmap->triEdgeIsWalkable = read.read_array<char>();
//
//			colmap->numCollisionBorders = read.read_int();
//			colmap->collisionBorders = read.read_array<CollisionBorder>();
//
//			colmap->numCollisionPartitions = read.read_int();
//			colmap->collisionPartitions = read.read_array<CollisionPartition>();
//			for (auto i = 0; i < colmap->numCollisionPartitions; i++)
//			{
//				if (colmap->collisionPartitions[i].borders)
//				{
//					colmap->collisionPartitions[i].borders = read.read_array<CollisionBorder>();
//				}
//			}
//
//			colmap->numCollisionAABBTrees = read.read_int();
//			colmap->collisionAABBTrees = read.read_array<CollisionAabbTree>();
//
//			colmap->numCModels = read.read_int();
//			colmap->cModels = read.read_array<cmodel_t>();
//
//			for (auto i = 0; i < colmap->numCModels; i++)
//			{
//				if (colmap->cModels[i].info)
//				{
//					colmap->cModels[i].info = mem->Alloc<ClipInfo>();
//					parse_info(colmap->cModels[i].info, read, mem);
//				}
//			}
//
//			colmap->mapEnts = read.read_asset<MapEnts>();
//			colmap->mapEnts->name = colmap->name;
//			colmap->smodelNodeCount = read.read_int();
//			colmap->smodelNodes = read.read_array<SModelAabbNode>();
//			colmap->dynEntDefList[0] = 0;
//			colmap->dynEntDefList[1] = 0;
//			colmap->dynEntPoseList[0] = 0;
//			colmap->dynEntPoseList[1] = 0;
//			colmap->dynEntClientList[0] = 0;
//			colmap->dynEntClientList[1] = 0;
//			colmap->dynEntCollList[0] = 0;
//			colmap->dynEntCollList[1] = 0;
//			colmap->dynEntCount[0] = 0;
//			colmap->dynEntCount[1] = 0;
//			// parse stages
//			AssetReader stageReader(mem);
//			if (stageReader.open(name + ".ents.stages"))
//			{
//				ZONETOOL_INFO("Parsing entity stages...");
//
//				colmap->stageCount = stageReader.read_int();
//				if (colmap->stageCount)
//				{
//					colmap->stages = stageReader.read_array<Stage>();
//
//					for (int i = 0; i < colmap->stageCount; i++)
//					{
//						colmap->stages[i].name = stageReader.read_string();
//					}
//				}
//			}
//			stageReader.close();
//
//			// copy info into pInfo
//			colmap->pInfo = &colmap->info;
//
//			/*colmap->pInfo = mem->Alloc<ClipInfo>();
//			memcpy(colmap->pInfo, &colmap->info, sizeof ClipInfo);*/
//
//#ifdef USE_VMPROTECT
//			VMProtectEnd();
//#endif
//
//			return colmap;
//		}
//
//		void IClipMap::init(const std::string& name, ZoneMemory* mem)
//		{
//			this->name_ = "maps/"s + (currentzone.substr(0, 3) == "mp_" ? "mp/" : "") + currentzone + ".d3dbsp"; // name;
//			this->asset_ = this->parse(name, mem);
//
//			if (!this->asset_)
//			{
//				this->asset_ = DB_FindXAssetHeader(this->type(), name.data(), 1).clipmap;
//			}
//		}
//
//		void IClipMap::prepare(ZoneBuffer* buf, ZoneMemory* mem)
//		{
//		}
//
//		void IClipMap::load_depending(IZone* zone)
//		{
//#ifdef USE_VMPROTECT
//			VMProtectBeginUltra("IW5::IClipMap::load_depending");
//#endif
//
//			auto data = this->asset_;
//
//			if (data->staticModelList)
//			{
//				for (int i = 0; i < data->numStaticModels; i++)
//				{
//					if (data->staticModelList[i].xmodel)
//					{
//						zone->add_asset_of_type(xmodel, data->staticModelList[i].xmodel->name);
//					}
//				}
//			}
//
//			//if (data->dynEntDefList[0])
//			//{
//			//	for (int i = 0; i < data->dynEntCount[0]; i++)
//			//	{
//			//		if (data->dynEntDefList[0][i].xModel)
//			//		{
//			//			zone->add_asset_of_type(xmodel, data->dynEntDefList[0][i].xModel->name);
//			//		}
//			//		if (data->dynEntDefList[0][i].destroyFx)
//			//		{
//			//			zone->add_asset_of_type(fx, data->dynEntDefList[0][i].destroyFx->name);
//			//		}
//			//		if (data->dynEntDefList[0][i].physPreset)
//			//		{
//			//			zone->add_asset_of_type(physpreset, data->dynEntDefList[0][i].physPreset->name);
//			//		}
//			//	}
//			//}
//
//			//if (data->dynEntDefList[1])
//			//{
//			//	for (int i = 0; i < data->dynEntCount[1]; i++)
//			//	{
//			//		if (data->dynEntDefList[1][i].xModel)
//			//		{
//			//			zone->add_asset_of_type(xmodel, data->dynEntDefList[1][i].xModel->name);
//			//		}
//			//		if (data->dynEntDefList[1][i].destroyFx)
//			//		{
//			//			zone->add_asset_of_type(fx, data->dynEntDefList[1][i].destroyFx->name);
//			//		}
//			//		if (data->dynEntDefList[1][i].physPreset)
//			//		{
//			//			zone->add_asset_of_type(physpreset, data->dynEntDefList[1][i].physPreset->name);
//			//		}
//			//	}
//			//}
//
//			if (data->mapEnts)
//			{
//				zone->add_asset_of_type(map_ents, this->asset_->mapEnts->name);
//			}
//
//#ifdef USE_VMPROTECT
//			VMProtectEnd();
//#endif
//		}
//
//		std::string IClipMap::name()
//		{
//			return this->name_;
//		}
//
//		std::int32_t IClipMap::type()
//		{
//			return col_map_mp;
//		}
//
//		void IClipMap::write_info(IZone* zone, ZoneBuffer* buf, ClipInfo* data, ClipInfo* dest)
//		{
//#ifdef USE_VMPROTECT
//			VMProtectBeginUltra("IW5::IClipMap::write_info");
//#endif
//
//			if (data->cPlanes)
//			{
//				dest->cPlanes = buf->write_s(3, data->cPlanes, data->numCPlanes);
//				ZONETOOL_INFO("cPlanes pointer is 0x%08X", dest->cPlanes);
//			}
//
//			if (data->materials)
//			{
//				dmaterial_t* dmaterial;
//				dest->materials = buf->write_s(3, data->materials, data->numMaterials, sizeof dmaterial_t, &dmaterial);
//
//				if (dest->materials == reinterpret_cast<dmaterial_t*>(-1))
//				{
//					for (std::int32_t i = 0; i < data->numMaterials; i++)
//					{
//						if (data->materials[i].material)
//						{
//							dmaterial[i].material = buf->write_str(data->materials[i].material);
//						}
//					}
//				}
//				ZONETOOL_INFO("materials pointer is 0x%08X", dest->materials);
//			}
//
//			if (data->cBrushSides)
//			{
//				cbrushside_t* brush_side;
//				dest->cBrushSides = buf->write_s(3, data->cBrushSides, data->numCBrushSides, sizeof cbrushside_t,
//				                                 &brush_side);
//
//				if (dest->cBrushSides == reinterpret_cast<cbrushside_t*>(-1))
//				{
//					for (std::int32_t i = 0; i < data->numCBrushSides; i++)
//					{
//						if (data->cBrushSides[i].plane)
//						{
//							brush_side[i].plane = buf->write_s(3, data->cBrushSides[i].plane);
//						}
//					}
//				}
//				ZONETOOL_INFO("cBrushSides pointer is 0x%08X", dest->cBrushSides);
//			}
//
//			if (data->cBrushEdges)
//			{
//				/*buf->write_p(data->cBrushEdges, data->numCBrushEdges);
//				ZoneBuffer::clear_pointer(&);*/
//				dest->cBrushEdges = buf->write_s(0, data->cBrushEdges, data->numCBrushEdges);
//				ZONETOOL_INFO("cBrushEdges pointer is 0x%08X", dest->cBrushEdges);
//			}
//
//			if (data->cLeafBrushNodes)
//			{
//				cLeafBrushNode_s* leaf_brush_node = nullptr;
//				dest->cLeafBrushNodes = buf->write_s(3, data->cLeafBrushNodes, data->numCLeafBrushNodes,
//				                                     sizeof cLeafBrushNode_s, &leaf_brush_node);
//
//				if (dest->cLeafBrushNodes == reinterpret_cast<cLeafBrushNode_s*>(-1))
//				{
//					for (std::int32_t i = 0; i < data->numCLeafBrushNodes; i++)
//					{
//						if (data->cLeafBrushNodes[i].leafBrushCount > 0 && data->cLeafBrushNodes[i].data.leaf.brushes)
//						{
//							leaf_brush_node[i].data.leaf.brushes = buf->write_s(
//								1, data->cLeafBrushNodes[i].data.leaf.brushes, data->cLeafBrushNodes[i].leafBrushCount);
//						}
//					}
//				}
//				ZONETOOL_INFO("cLeafBrushNodes pointer is 0x%08X", dest->cLeafBrushNodes);
//			}
//
//			if (data->leafBrushes)
//			{
//				/*buf->align(1);
//				buf->write(data->leafBrushes, data->numLeafBrushes);
//				ZoneBuffer::clear_pointer(&dest->leafBrushes);*/
//				dest->leafBrushes = buf->write_s(1, data->leafBrushes, data->numLeafBrushes);
//				ZONETOOL_INFO("leafBrushes pointer is 0x%08X", dest->leafBrushes);
//			}
//
//			// brushes
//			if (data->brushes)
//			{
//				cbrush_t* brush = nullptr;
//				dest->brushes = buf->write_s(127, data->brushes, data->numBrushes, sizeof cbrush_t, &brush);
//
//				if (dest->brushes == reinterpret_cast<cbrush_t*>(-1))
//				{
//					for (int i = 0; i < data->numBrushes; i++)
//					{
//						if (data->brushes[i].sides)
//						{
//							cbrushside_t* side = nullptr;
//							brush[i].sides = buf->write_s(3, data->brushes[i].sides, 1, sizeof cbrushside_t, &side);
//
//							if (brush[i].sides == (cbrushside_t*)-1 && side)
//							{
//								if (side->plane)
//								{
//									side->plane = buf->write_s(3, side->plane);
//								}
//							}
//						}
//
//						if (data->brushes[i].edge)
//						{
//							brush[i].edge = buf->write_s(0, data->brushes[i].edge);
//						}
//					}
//				}
//				ZONETOOL_INFO("brushes pointer is 0x%08X", dest->brushes);
//			}
//
//			// brushBounds
//			if (data->brushBounds)
//			{
//				/*buf->align(127);
//				buf->write(data->brushBounds, data->numBrushes);
//				ZoneBuffer::clear_pointer(&dest->brushBounds);*/
//				dest->brushBounds = buf->write_s(127, data->brushBounds, data->numBrushes);
//				ZONETOOL_INFO("brushBounds pointer is 0x%08X", dest->brushBounds);
//			}
//
//			// brushContents
//			if (data->brushContents)
//			{
//				/*buf->align(3);
//				buf->write(data->brushContents, data->numBrushes);
//				ZoneBuffer::clear_pointer(&dest->brushContents);*/
//				dest->brushContents = buf->write_s(3, data->brushContents, data->numBrushes);
//				ZONETOOL_INFO("brushContents pointer is 0x%08X", dest->brushContents);
//			}
//
//#ifdef USE_VMPROTECT
//			VMProtectEnd();
//#endif
//		}
//
//		void IClipMap::write(IZone* zone, ZoneBuffer* buf)
//		{
//#ifdef USE_VMPROTECT
//			VMProtectBeginUltra("IW5::IClipMap::write");
//#endif
//
//			auto data = this->asset_;
//			auto offset = buf->get_zone_offset();
//			auto dest = buf->write<clipMap_t>(data);
//
//			sizeof clipMap_t;
//
//			dest->isPlutoniumMap = 0x13370420;
//
//			buf->push_stream(3);
//			START_LOG_STREAM;
//
//			dest->name = buf->write_str(this->name());
//
//			this->write_info(zone, buf, &data->info, &dest->info);
//
//			if (data->pInfo)
//			{
//				buf->align(3);
//				auto destInfo = buf->write(data->pInfo);
//				this->write_info(zone, buf, data->pInfo, destInfo);
//				ZoneBuffer::clear_pointer(&dest->pInfo);
//			}
//
//			if (data->staticModelList)
//			{
//				buf->align(3);
//				auto static_model = buf->write(data->staticModelList, data->numStaticModels);
//
//				for (std::int32_t i = 0; i < data->numStaticModels; i++)
//				{
//					if (data->staticModelList[i].xmodel)
//					{
//						static_model[i].xmodel = reinterpret_cast<XModel*>(zone->get_asset_pointer(
//							xmodel, data->staticModelList[i].xmodel->name));
//					}
//				}
//
//				ZoneBuffer::clear_pointer(&data->staticModelList);
//			}
//
//			if (data->cNodes)
//			{
//				buf->align(3);
//				auto node = buf->write(data->cNodes, data->numCNodes);
//
//				for (std::int32_t i = 0; i < data->numCNodes; i++)
//				{
//					if (data->cNodes[i].plane)
//					{
//						node[i].plane = buf->write_s(3, data->cNodes[i].plane);
//					}
//				}
//
//				ZoneBuffer::clear_pointer(&dest->cNodes);
//			}
//
//			if (data->cLeaf)
//			{
//				buf->align(3);
//				buf->write(data->cLeaf, data->numCLeaf);
//				ZoneBuffer::clear_pointer(&dest->cLeaf);
//			}
//
//			if (data->verts)
//			{
//				buf->align(3);
//				buf->write(data->verts, data->numVerts);
//				ZoneBuffer::clear_pointer(&dest->verts);
//			}
//
//			if (data->triIndices)
//			{
//				buf->align(1);
//				buf->write(data->triIndices, data->numTriIndices * 3);
//				ZoneBuffer::clear_pointer(&dest->triIndices);
//			}
//
//			if (data->triEdgeIsWalkable)
//			{
//				buf->align(0);
//				buf->write(data->triEdgeIsWalkable, 4 * ((3 * data->numTriIndices + 31) >> 5));
//				ZoneBuffer::clear_pointer(&dest->triEdgeIsWalkable);
//			}
//
//			if (data->collisionBorders)
//			{
//				buf->align(3);
//				buf->write_p(data->collisionBorders, data->numCollisionBorders);
//				ZoneBuffer::clear_pointer(&dest->collisionBorders);
//			}
//
//			if (data->collisionPartitions)
//			{
//				buf->align(3);
//				auto collision_partition = buf->write(data->collisionPartitions, data->numCollisionPartitions);
//
//				for (std::int32_t i = 0; i < data->numCollisionPartitions; i++)
//				{
//					if (data->collisionPartitions[i].borders)
//					{
//						collision_partition[i].borders = buf->write_s(3, data->collisionPartitions[i].borders);
//					}
//				}
//
//				ZoneBuffer::clear_pointer(&dest->collisionPartitions);
//			}
//
//			if (data->collisionAABBTrees)
//			{
//				buf->align(15);
//				buf->write(data->collisionAABBTrees, data->numCollisionAABBTrees);
//				ZoneBuffer::clear_pointer(&dest->collisionAABBTrees);
//			}
//
//			if (data->cModels)
//			{
//				buf->align(3);
//				auto destCModels = buf->write(data->cModels, data->numCModels);
//
//				for (std::int32_t i = 0; i < data->numCModels; i++)
//				{
//					buf->push_stream(0);
//					
//					if (data->cModels[i].info)
//					{
//						ClipInfo* destInfo = nullptr;
//						destCModels[i].info = buf->write_s(3, data->cModels[i].info, 1, sizeof ClipInfo, &destInfo);
//
//						if (destCModels[i].info == reinterpret_cast<ClipInfo*>(-1))
//						{
//							this->write_info(zone, buf, data->cModels[i].info, destInfo);
//						}
//					}
//
//					buf->pop_stream();
//				}
//
//				ZoneBuffer::clear_pointer(&dest->cModels);
//			}
//
//			if (data->smodelNodes)
//			{
//				buf->align(3);
//				buf->write(data->smodelNodes, data->smodelNodeCount);
//				ZoneBuffer::clear_pointer(&dest->smodelNodes);
//			}
//
//			if (data->mapEnts)
//			{
//				dest->mapEnts = reinterpret_cast<MapEnts*>(zone->get_asset_pointer(map_ents, this->name()));
//			}
//
//			if (data->stages)
//			{
//				buf->align(3);
//				auto destStages = buf->write(data->stages, data->stageCount);
//
//				for (std::uint8_t i = 0; i < data->stageCount; i++)
//				{
//					if (data->stages[i].name)
//					{
//						buf->write_str(data->stages[i].name);
//						ZoneBuffer::clear_pointer(&destStages[i].name);
//					}
//				}
//
//				ZoneBuffer::clear_pointer(&dest->stages);
//			}
//
//			// copy trigger data from mapents
//			memcpy(&dest->trigger, &data->mapEnts->trigger, sizeof MapTriggers);
//
//			// write triggers
//			IMapEnts::write_triggers(zone, buf, &dest->trigger);
//
//			if (data->dynEntDefList[0])
//			{
//				buf->align(3);
//				auto dyn_entity_def = buf->write(data->dynEntDefList[0], data->dynEntCount[0]);
//
//				for (std::uint16_t i = 0; i < data->dynEntCount[0]; i++)
//				{
//					if (data->dynEntDefList[0][i].xModel)
//					{
//						dyn_entity_def[i].xModel = reinterpret_cast<XModel*>(zone->get_asset_pointer(
//							xmodel, data->dynEntDefList[0][i].xModel->name));
//					}
//					if (data->dynEntDefList[0][i].destroyFx)
//					{
//						dyn_entity_def[i].destroyFx = reinterpret_cast<FxEffectDef*>(zone->get_asset_pointer(
//							fx, data->dynEntDefList[0][i].destroyFx->name));
//					}
//					if (data->dynEntDefList[0][i].physPreset)
//					{
//						dyn_entity_def[i].physPreset = reinterpret_cast<PhysPreset*>(zone->get_asset_pointer(
//							physpreset, data->dynEntDefList[0][i].physPreset->name));
//					}
//
//					if (data->dynEntDefList[0][i].hinge)
//					{
//						dyn_entity_def[i].hinge = buf->write_s(3, dyn_entity_def[i].hinge, 1);
//					}
//				}
//
//				ZoneBuffer::clear_pointer(&dest->dynEntDefList[0]);
//			}
//
//			if (data->dynEntDefList[1])
//			{
//				buf->align(3);
//				auto dyn_entity_def = buf->write(data->dynEntDefList[1], data->dynEntCount[1]);
//
//				for (std::uint16_t i = 0; i < data->dynEntCount[1]; i++)
//				{
//					if (data->dynEntDefList[1][i].xModel)
//					{
//						dyn_entity_def[i].xModel = reinterpret_cast<XModel*>(zone->get_asset_pointer(
//							xmodel, data->dynEntDefList[1][i].xModel->name));
//					}
//					if (data->dynEntDefList[1][i].destroyFx)
//					{
//						dyn_entity_def[i].destroyFx = reinterpret_cast<FxEffectDef*>(zone->get_asset_pointer(
//							fx, data->dynEntDefList[1][i].destroyFx->name));
//					}
//					if (data->dynEntDefList[1][i].physPreset)
//					{
//						dyn_entity_def[i].physPreset = reinterpret_cast<PhysPreset*>(zone->get_asset_pointer(
//							physpreset, data->dynEntDefList[1][i].physPreset->name));
//					}
//
//					if (data->dynEntDefList[1][i].hinge)
//					{
//						dyn_entity_def[i].hinge = buf->write_s(3, dyn_entity_def[i].hinge, 1);
//					}
//				}
//
//				ZoneBuffer::clear_pointer(&dest->dynEntDefList[1]);
//			}
//
//			buf->push_stream(2);
//
//			if (data->dynEntPoseList[0])
//			{
//				buf->align(3);
//				buf->write(data->dynEntPoseList[0], data->dynEntCount[0]);
//				ZoneBuffer::clear_pointer(&dest->dynEntPoseList[0]);
//			}
//
//			if (data->dynEntPoseList[1])
//			{
//				buf->align(3);
//				buf->write(data->dynEntPoseList[1], data->dynEntCount[1]);
//				ZoneBuffer::clear_pointer(&dest->dynEntPoseList[1]);
//			}
//
//			if (data->dynEntClientList[0])
//			{
//				buf->align(3);
//				buf->write(data->dynEntClientList[0], data->dynEntCount[0]);
//				ZoneBuffer::clear_pointer(&dest->dynEntClientList[0]);
//			}
//
//			if (data->dynEntClientList[1])
//			{
//				buf->align(3);
//				buf->write(data->dynEntClientList[1], data->dynEntCount[1]);
//				ZoneBuffer::clear_pointer(&dest->dynEntClientList[1]);
//			}
//
//			if (data->dynEntCollList[0])
//			{
//				buf->align(3);
//				buf->write(data->dynEntCollList[0], data->dynEntCount[0]);
//				ZoneBuffer::clear_pointer(&dest->dynEntCollList[0]);
//			}
//
//			if (data->dynEntCollList[1])
//			{
//				buf->align(3);
//				buf->write(data->dynEntCollList[1], data->dynEntCount[1]);
//				ZoneBuffer::clear_pointer(&dest->dynEntCollList[1]);
//			}
//
//			buf->pop_stream();
//
//			END_LOG_STREAM;
//			buf->pop_stream();
//
//			encrypt_data(dest, sizeof clipMap_t);
//
//#ifdef USE_VMPROTECT
//			VMProtectEnd();
//#endif
//		}

#undef INFO
#define INFO info->

		void dump_info(ClipInfo* info, AssetDumper& write)
		{
			write.dump_int(INFO planeCount);
			write.dump_array(INFO planes, INFO planeCount);

			write.dump_int(INFO numMaterials);
			write.dump_array(INFO materials, INFO numMaterials);

			for (auto i = 0; i < INFO numMaterials; i++)
			{
				if (INFO materials[i].name)
				{
					write.dump_string(INFO materials[i].name);
				}
			}

			write.dump_int(INFO numBrushSides);
			write.dump_array(INFO brushsides, INFO numBrushSides);

			for (auto i = 0; i < INFO numBrushSides; i++)
			{
				if (INFO brushsides[i].plane)
				{
					write.dump_array(INFO brushsides[i].plane, 1);
				}
			}

			//write.dump_int(INFO numCBrushEdges);
			//write.dump_array(INFO cBrushEdges, INFO numCBrushEdges);

			write.dump_int(INFO numLeafBrushes);
			write.dump_array(INFO leafbrushes, INFO numLeafBrushes);

			write.dump_int(INFO leafbrushNodesCount);
			write.dump_array(INFO leafbrushNodes, INFO leafbrushNodesCount);

			for (auto i = 0; i < INFO leafbrushNodesCount; i++)
			{
				if (INFO leafbrushNodes[i].leafBrushCount > 0)
				{
					write.dump_array(INFO leafbrushNodes[i].data.leaf.brushes, INFO leafbrushNodes[i].leafBrushCount);
				}
			}

			write.dump_int(INFO numBrushes);
			write.dump_array(INFO brushes, INFO numBrushes);

			for (auto i = 0; i < INFO numBrushes; i++)
			{
				if (INFO brushes[i].sides)
				{
					write.dump_array(INFO brushes[i].sides, 1);

					if (INFO brushes[i].sides->plane)
					{
						write.dump_array(INFO brushes[i].sides->plane, 1);
					}
				}
				//if (INFO brushes[i].edge)
				//{
				//	write.dump_array(INFO brushes[i].edge, 1);
				//}
			}

			write.dump_array(INFO brushBounds, INFO numBrushes);
			write.dump_array(INFO brushContents, INFO numBrushes);
		}

		void IClipMap::dump(clipMap_t* asset)
		{
			AssetDumper write;
			if (!write.open(asset->name + ".colmap"s))
			{
				return;
			}

			write.dump_string(asset->name);
			write.dump_int(asset->isInUse);

			dump_info(&asset->info, write);

			write.dump_int(asset->numStaticModels);
			write.dump_array(asset->staticModelList, asset->numStaticModels);

			for (auto i = 0; i < asset->numStaticModels; i++)
			{
				if (asset->staticModelList[i].xmodel)
				{
					write.dump_asset(asset->staticModelList[i].xmodel);
				}
			}

			write.dump_int(asset->numNodes);
			write.dump_array(asset->nodes, asset->numNodes);

			for (auto i = 0; i < asset->numNodes; i++)
			{
				if (asset->nodes[i].plane)
				{
					write.dump_array(asset->nodes[i].plane, 1);
				}
			}

			write.dump_int(asset->numLeafs);
			write.dump_array(asset->leafs, asset->numLeafs);

			//write.dump_int(asset->numVerts);
			//write.dump_array(asset->verts, asset->numVerts);

			write.dump_int(asset->triCount);
			write.dump_array(asset->triIndices, asset->triCount * 3);
			write.dump_array(asset->triEdgeIsWalkable, 4 * ((3 * asset->triCount + 31) >> 5));

			//write.dump_int(asset->numCollisionBorders);
			//write.dump_array(asset->collisionBorders, asset->numCollisionBorders);

			write.dump_int(asset->partitionCount);
			write.dump_array(asset->partitions, asset->partitionCount);

			//for (auto i = 0; i < asset->partitionCount; i++)
			//{
			//	if (asset->partitions[i].borders)
			//	{
			//		write.dump_array(asset->partitions[i].borders, asset->partitions[i].borderCount);
			//	}
			//}

			write.dump_int(asset->aabbTreeCount);
			write.dump_array(asset->aabbTrees, asset->aabbTreeCount);

			write.dump_int(asset->numSubModels);
			write.dump_array(asset->cmodels, asset->numSubModels);

			for (int i = 0; i < asset->numSubModels; i++)
			{
				if (asset->cmodels[i].info)
				{
					dump_info(asset->cmodels[i].info, write);
				}
			}

			write.dump_asset(asset->mapEnts);

			//write.dump_int(asset->smodelNodeCount);
			//write.dump_array(asset->smodelNodes, asset->smodelNodeCount);

			// save file to disk
			write.close();

			// dump stages
			//if (asset->stages)
			//{
			//	AssetDumper stageDumper;

			//	if (stageDumper.open(asset->name + ".ents.stages"s))
			//	{
			//		stageDumper.dump_int(asset->stageCount);
			//		if (asset->stageCount)
			//		{
			//			stageDumper.dump_array(asset->stages, asset->stageCount);

			//			for (int i = 0; i < asset->stageCount; i++)
			//			{
			//				stageDumper.dump_string(asset->stages[i].name);
			//			}
			//		}
			//	}

			//	stageDumper.close();
			//}
		}
	}
}
