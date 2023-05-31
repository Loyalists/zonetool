#include "stdafx.hpp"
#include "H1/Assets/ClipMap.hpp"

#include "H1/Assets/PhysWorld.hpp"

namespace ZoneTool
{
	namespace IW5
	{
		namespace
		{
			H1::CSurfaceFlags surf_flags_conversion_table[31]
			{
				H1::SURF_FLAG_DEFAULT,
				H1::SURF_FLAG_BARK,
				H1::SURF_FLAG_BRICK,
				H1::SURF_FLAG_CARPET,
				H1::SURF_FLAG_CLOTH,
				H1::SURF_FLAG_CONCRETE,
				H1::SURF_FLAG_DIRT,
				H1::SURF_FLAG_FLESH,
				H1::SURF_FLAG_FOLIAGE_DEBRIS,
				H1::SURF_FLAG_GLASS,
				H1::SURF_FLAG_GRASS,
				H1::SURF_FLAG_GRAVEL,
				H1::SURF_FLAG_ICE,
				H1::SURF_FLAG_METAL_SOLID,
				H1::SURF_FLAG_MUD,
				H1::SURF_FLAG_PAPER,
				H1::SURF_FLAG_PLASTER,
				H1::SURF_FLAG_ROCK,
				H1::SURF_FLAG_SAND,
				H1::SURF_FLAG_SNOW,
				H1::SURF_FLAG_WATER_WAIST,
				H1::SURF_FLAG_WOOD_SOLID,
				H1::SURF_FLAG_ASPHALT,
				H1::SURF_FLAG_CERAMIC,
				H1::SURF_FLAG_PLASTIC_SOLID,
				H1::SURF_FLAG_RUBBER,
				H1::SURF_FLAG_CUSHION,
				H1::SURF_FLAG_FRUIT,
				H1::SURF_FLAG_PAINTEDMETAL,
				H1::SURF_FLAG_RIOTSHIELD,
				H1::SURF_FLAG_SLUSH,
			}; IW5::CSurfaceFlags;

			int convert_surf_flags(int flags)
			{
				int h1_flags = surf_flags_conversion_table[flags >> 20];
				auto convert = [&](IW5::CSurfaceFlags a, H1::CSurfaceFlags b)
				{
					h1_flags |= ((flags & a) == a) ? b : 0;
				};
				convert(IW5::CSurfaceFlags::SURF_FLAG_OPAQUEGLASS, H1::CSurfaceFlags::SURF_FLAG_DEFAULT);
				convert(IW5::CSurfaceFlags::SURF_FLAG_CLIPMISSILE, H1::CSurfaceFlags::SURF_FLAG_CLIPMISSILE);
				convert(IW5::CSurfaceFlags::SURF_FLAG_AI_NOSIGHT, H1::CSurfaceFlags::SURF_FLAG_AI_NOSIGHT);
				convert(IW5::CSurfaceFlags::SURF_FLAG_CLIPSHOT, H1::CSurfaceFlags::SURF_FLAG_CLIPSHOT);
				convert(IW5::CSurfaceFlags::SURF_FLAG_PLAYERCLIP, H1::CSurfaceFlags::SURF_FLAG_PLAYERCLIP);
				convert(IW5::CSurfaceFlags::SURF_FLAG_MONSTERCLIP, H1::CSurfaceFlags::SURF_FLAG_MONSTERCLIP);
				convert(IW5::CSurfaceFlags::SURF_FLAG_AICLIPALLOWDEATH, H1::CSurfaceFlags::SURF_FLAG_AICLIPALLOWDEATH);
				convert(IW5::CSurfaceFlags::SURF_FLAG_VEHICLECLIP, H1::CSurfaceFlags::SURF_FLAG_VEHICLECLIP);
				convert(IW5::CSurfaceFlags::SURF_FLAG_ITEMCLIP, H1::CSurfaceFlags::SURF_FLAG_ITEMCLIP);
				convert(IW5::CSurfaceFlags::SURF_FLAG_NODROP, H1::CSurfaceFlags::SURF_FLAG_NODROP);
				convert(IW5::CSurfaceFlags::SURF_FLAG_NONSOLID, H1::CSurfaceFlags::SURF_FLAG_NONSOLID);
				convert(IW5::CSurfaceFlags::SURF_FLAG_DETAIL, H1::CSurfaceFlags::SURF_FLAG_DETAIL);
				convert(IW5::CSurfaceFlags::SURF_FLAG_STRUCTURAL, H1::CSurfaceFlags::SURF_FLAG_STRUCTURAL);
				convert(IW5::CSurfaceFlags::SURF_FLAG_PORTAL, H1::CSurfaceFlags::SURF_FLAG_PORTAL);
				convert(IW5::CSurfaceFlags::SURF_FLAG_CANSHOOTCLIP, H1::CSurfaceFlags::SURF_FLAG_CANSHOOTCLIP);
				convert(IW5::CSurfaceFlags::SURF_FLAG_ORIGIN, H1::CSurfaceFlags::SURF_FLAG_ORIGIN);
				convert(IW5::CSurfaceFlags::SURF_FLAG_SKY, H1::CSurfaceFlags::SURF_FLAG_SKY);
				convert(IW5::CSurfaceFlags::SURF_FLAG_NOCASTSHADOW, H1::CSurfaceFlags::SURF_FLAG_NOCASTSHADOW);
				convert(IW5::CSurfaceFlags::SURF_FLAG_PHYSICSGEOM, H1::CSurfaceFlags::SURF_FLAG_PHYSICSGEOM);
				convert(IW5::CSurfaceFlags::SURF_FLAG_LIGHTPORTAL, H1::CSurfaceFlags::SURF_FLAG_LIGHTPORTAL);
				convert(IW5::CSurfaceFlags::SURF_FLAG_OUTDOORBOUNDS, H1::CSurfaceFlags::SURF_FLAG_OUTDOORBOUNDS);
				convert(IW5::CSurfaceFlags::SURF_FLAG_SLICK, H1::CSurfaceFlags::SURF_FLAG_SLICK);
				convert(IW5::CSurfaceFlags::SURF_FLAG_NOIMPACT, H1::CSurfaceFlags::SURF_FLAG_NOIMPACT);
				convert(IW5::CSurfaceFlags::SURF_FLAG_NOMARKS, H1::CSurfaceFlags::SURF_FLAG_NOMARKS);
				convert(IW5::CSurfaceFlags::SURF_FLAG_NOPENETRATE, H1::CSurfaceFlags::SURF_FLAG_NOPENETRATE);
				convert(IW5::CSurfaceFlags::SURF_FLAG_LADDER, H1::CSurfaceFlags::SURF_FLAG_LADDER);
				convert(IW5::CSurfaceFlags::SURF_FLAG_NODAMAGE, H1::CSurfaceFlags::SURF_FLAG_NODAMAGE);
				convert(IW5::CSurfaceFlags::SURF_FLAG_MANTLEON, H1::CSurfaceFlags::SURF_FLAG_MANTLEON);
				convert(IW5::CSurfaceFlags::SURF_FLAG_MANTLEOVER, H1::CSurfaceFlags::SURF_FLAG_MANTLEOVER);
				convert(IW5::CSurfaceFlags::SURF_FLAG_STAIRS, H1::CSurfaceFlags::SURF_FLAG_STAIRS);
				convert(IW5::CSurfaceFlags::SURF_FLAG_SOFT, H1::CSurfaceFlags::SURF_FLAG_SOFT);
				convert(IW5::CSurfaceFlags::SURF_FLAG_NOSTEPS, H1::CSurfaceFlags::SURF_FLAG_NOSTEPS);
				convert(IW5::CSurfaceFlags::SURF_FLAG_NODRAW, H1::CSurfaceFlags::SURF_FLAG_NODRAW);
				convert(IW5::CSurfaceFlags::SURF_FLAG_NOLIGHTMAP, H1::CSurfaceFlags::SURF_FLAG_NOLIGHTMAP);
				convert(IW5::CSurfaceFlags::SURF_FLAG_NODLIGHT, H1::CSurfaceFlags::SURF_FLAG_NODLIGHT);
				return h1_flags;
			}
		}

		void GenerateH1ClipInfo(H1::ClipInfo* info, clipMap_t* asset, ZoneMemory* mem)
		{
			info->planeCount = asset->info.numCPlanes;
			REINTERPRET_CAST_SAFE(info->planes, asset->info.cPlanes);

			info->numMaterials = asset->info.numMaterials;
			info->materials = mem->Alloc<H1::ClipMaterial>(info->numMaterials);
			for (unsigned int i = 0; i < info->numMaterials; i++)
			{
				info->materials[i].name = asset->info.materials[i].material;
				info->materials[i].surfaceFlags = convert_surf_flags(asset->info.materials[i].surfaceFlags);
				info->materials[i].contents = asset->info.materials[i].contentFlags;
			}

			info->bCollisionTree.leafbrushNodesCount = asset->info.numCLeafBrushNodes;
			info->bCollisionTree.leafbrushNodes = mem->Alloc<H1::cLeafBrushNode_s>(info->bCollisionTree.leafbrushNodesCount);
			for (unsigned int i = 0; i < info->bCollisionTree.leafbrushNodesCount; i++)
			{
				info->bCollisionTree.leafbrushNodes[i].axis = asset->info.cLeafBrushNodes[i].axis;
				info->bCollisionTree.leafbrushNodes[i].leafBrushCount = asset->info.cLeafBrushNodes[i].leafBrushCount;
				info->bCollisionTree.leafbrushNodes[i].contents = asset->info.cLeafBrushNodes[i].contents;
				if (info->bCollisionTree.leafbrushNodes[i].leafBrushCount > 0)
				{
					REINTERPRET_CAST_SAFE(info->bCollisionTree.leafbrushNodes[i].data.leaf.brushes, asset->info.cLeafBrushNodes[i].data.leaf.brushes);
				}
				else
				{
					info->bCollisionTree.leafbrushNodes[i].data.children.dist = asset->info.cLeafBrushNodes[i].data.children.dist;
					info->bCollisionTree.leafbrushNodes[i].data.children.range = asset->info.cLeafBrushNodes[i].data.children.range;
					
					info->bCollisionTree.leafbrushNodes[i].data.children.childOffset[0] = asset->info.cLeafBrushNodes[i].data.children.childOffset[0];
					info->bCollisionTree.leafbrushNodes[i].data.children.childOffset[1] = asset->info.cLeafBrushNodes[i].data.children.childOffset[1];
				}
			}

			info->bCollisionTree.numLeafBrushes = asset->info.numLeafBrushes;
			REINTERPRET_CAST_SAFE(info->bCollisionTree.leafbrushes, asset->info.leafBrushes);

			info->pCollisionTree.aabbTreeCount = asset->numCollisionAABBTrees;
			info->pCollisionTree.aabbTrees = mem->Alloc<H1::CollisionAabbTree>(info->pCollisionTree.aabbTreeCount);
			for (int i = 0; i < info->pCollisionTree.aabbTreeCount; i++)
			{
				std::memcpy(info->pCollisionTree.aabbTrees[i].midPoint, asset->collisionAABBTrees[i].midPoint, sizeof(float[3]));
				std::memcpy(info->pCollisionTree.aabbTrees[i].halfSize, asset->collisionAABBTrees[i].halfSize, sizeof(float[3]));
				info->pCollisionTree.aabbTrees[i].materialIndex = asset->collisionAABBTrees[i].materialIndex;
				info->pCollisionTree.aabbTrees[i].childCount = asset->collisionAABBTrees[i].childCount;

				info->pCollisionTree.aabbTrees[i].u.firstChildIndex = asset->collisionAABBTrees[i].u.firstChildIndex;
				//info->pCollisionTree.aabbTrees[i].u.partitionIndex = asset->collisionAABBTrees[i].u.partitionIndex;
			}

			info->sCollisionTree.numStaticModels = asset->numStaticModels;
			info->sCollisionTree.smodelNodeCount = asset->smodelNodeCount;
			REINTERPRET_CAST_SAFE(info->sCollisionTree.smodelNodes, asset->smodelNodes);

			std::unordered_map<cbrushside_t*, H1::cbrushside_t*> mapped_brush_sides;

			info->bCollisionData.numBrushSides = asset->info.numCBrushSides;
			info->bCollisionData.brushSides = mem->Alloc<H1::cbrushside_t>(info->bCollisionData.numBrushSides);
			for (unsigned int i = 0; i < info->bCollisionData.numBrushSides; i++)
			{
				mapped_brush_sides[&asset->info.cBrushSides[i]] = &info->bCollisionData.brushSides[i];

				// check
				info->bCollisionData.brushSides[i].planeIndex =
					(reinterpret_cast<std::uintptr_t>(asset->info.cBrushSides[i].plane) - reinterpret_cast<std::uintptr_t>(asset->info.cPlanes)) / sizeof(cplane_s);
				assert(info->bCollisionData.brushSides[i].planeIndex <= info->planeCount);

				info->bCollisionData.brushSides[i].materialNum = asset->info.cBrushSides[i].materialNum;
				info->bCollisionData.brushSides[i].firstAdjacentSideOffset = asset->info.cBrushSides[i].firstAdjacentSideOffset;
				info->bCollisionData.brushSides[i].edgeCount = asset->info.cBrushSides[i].edgeCount;
			}

			info->bCollisionData.numBrushEdges = asset->info.numCBrushEdges;
			REINTERPRET_CAST_SAFE(info->bCollisionData.brushEdges, asset->info.cBrushEdges);

			info->bCollisionData.numBrushes = asset->info.numBrushes;
			info->bCollisionData.brushes = mem->Alloc<H1::cbrush_t>(asset->info.numBrushes);
			for (unsigned int i = 0; i < info->bCollisionData.numBrushes; i++)
			{
				info->bCollisionData.brushes[i].numsides = asset->info.brushes[i].numsides;
				info->bCollisionData.brushes[i].glassPieceIndex = asset->info.brushes[i].glassPieceIndex;

				if (asset->info.brushes[i].sides)
					info->bCollisionData.brushes[i].sides = mapped_brush_sides.find(asset->info.brushes[i].sides)->second;

				REINTERPRET_CAST_SAFE(info->bCollisionData.brushes[i].baseAdjacentSide, asset->info.brushes[i].edge);

				memcpy(&info->bCollisionData.brushes[i].axialMaterialNum, &asset->info.brushes[i].axialMaterialNum, sizeof(short[2][3]));
				memcpy(&info->bCollisionData.brushes[i].firstAdjacentSideOffsets, &asset->info.brushes[i].firstAdjacentSideOffsets, sizeof(char[2][3]));
				memcpy(&info->bCollisionData.brushes[i].edgeCount, &asset->info.brushes[i].edgeCount, sizeof(char[2][3]));
			}

			REINTERPRET_CAST_SAFE(info->bCollisionData.brushBounds, asset->info.brushBounds);
			REINTERPRET_CAST_SAFE(info->bCollisionData.brushContents, asset->info.brushContents);

			info->pCollisionData.vertCount = asset->numVerts;
			REINTERPRET_CAST_SAFE(info->pCollisionData.verts, asset->verts);
			info->pCollisionData.triCount = asset->numTriIndices;
			REINTERPRET_CAST_SAFE(info->pCollisionData.triIndices, asset->triIndices);
			REINTERPRET_CAST_SAFE(info->pCollisionData.triEdgeIsWalkable, asset->triEdgeIsWalkable);
			info->pCollisionData.borderCount = asset->numCollisionBorders;
			REINTERPRET_CAST_SAFE(info->pCollisionData.borders, asset->collisionBorders);
			info->pCollisionData.partitionCount = asset->numCollisionPartitions;
			info->pCollisionData.partitions = mem->Alloc<H1::CollisionPartition>(info->pCollisionData.partitionCount);
			for (int i = 0; i < info->pCollisionData.partitionCount; i++)
			{
				info->pCollisionData.partitions[i].triCount = asset->collisionPartitions[i].triCount;
				info->pCollisionData.partitions[i].borderCount = asset->collisionPartitions[i].borderCount;
				info->pCollisionData.partitions[i].firstVertSegment = asset->collisionPartitions[i].firstVertSegment;
				info->pCollisionData.partitions[i].firstTri = asset->collisionPartitions[i].firstTri;
				REINTERPRET_CAST_SAFE(info->pCollisionData.partitions[i].borders, asset->collisionPartitions[i].borders);
			}

			info->sCollisionData.numStaticModels = asset->numStaticModels;
			info->sCollisionData.staticModelList = mem->Alloc<H1::cStaticModel_s>(info->sCollisionData.numStaticModels);
			for (unsigned int i = 0; i < info->sCollisionData.numStaticModels; i++)
			{
				info->sCollisionData.staticModelList[i].xmodel = reinterpret_cast<H1::XModel * __ptr64>(asset->staticModelList[i].xmodel);

				memcpy(&info->sCollisionData.staticModelList[i].origin, &asset->staticModelList[i].origin, sizeof(float[3]));
				memcpy(&info->sCollisionData.staticModelList[i].invScaledAxis, &asset->staticModelList[i].invScaledAxis, sizeof(float[3][3]));
				memcpy(&info->sCollisionData.staticModelList[i].absBounds, &asset->staticModelList[i].absmin, sizeof(float[2][3]));
				info->sCollisionData.staticModelList[i].lightingHandle = 0;
			}
		}

		H1::clipMap_t* GenerateH1ClipMap(clipMap_t* asset, ZoneMemory* mem)
		{
			// allocate H1 clipMap_t structure
			const auto h1_asset = mem->Alloc<H1::clipMap_t>();

			h1_asset->name = asset->name;
			h1_asset->isInUse = asset->isInUse;

			GenerateH1ClipInfo(&h1_asset->info, asset, mem);
			h1_asset->pInfo = &h1_asset->info;

			h1_asset->numNodes = asset->numCNodes;
			h1_asset->nodes = mem->Alloc<H1::cNode_t>(h1_asset->numNodes);
			for (unsigned int i = 0; i < h1_asset->numNodes; i++)
			{
				REINTERPRET_CAST_SAFE(h1_asset->nodes[i].plane, asset->cNodes[i].plane);
				h1_asset->nodes[i].children[0] = asset->cNodes[i].children[0];
				h1_asset->nodes[i].children[1] = asset->cNodes[i].children[1];
			}

			h1_asset->numLeafs = asset->numCLeaf;
			h1_asset->leafs = mem->Alloc<H1::cLeaf_t>(h1_asset->numLeafs);
			for (unsigned int i = 0; i < h1_asset->numLeafs; i++)
			{
				h1_asset->leafs[i].firstCollAabbIndex = asset->cLeaf[i].firstCollAabbIndex;
				h1_asset->leafs[i].collAabbCount = asset->cLeaf[i].collAabbCount;
				h1_asset->leafs[i].brushContents = asset->cLeaf[i].brushContents;
				h1_asset->leafs[i].terrainContents = asset->cLeaf[i].terrainContents;
				memcpy(&h1_asset->leafs[i].bounds, &asset->cLeaf[i].bounds, sizeof(IW5::Bounds));
				h1_asset->leafs[i].leafBrushNode = asset->cLeaf[i].leafBrushNode;
			}

			h1_asset->numSubModels = asset->numCModels;
			h1_asset->cmodels = mem->Alloc<H1::cmodel_t>(h1_asset->numSubModels);
			for (unsigned int i = 0; i < h1_asset->numSubModels; i++)
			{
				memcpy(&h1_asset->cmodels[i].bounds, &asset->cModels[i].bounds, sizeof(IW5::Bounds));
				h1_asset->cmodels[i].radius = asset->cModels[i].radius;

				h1_asset->cmodels[i].info = nullptr; // mapped in h1

				h1_asset->cmodels[i].leaf.firstCollAabbIndex = asset->cModels[i].leaf.firstCollAabbIndex;
				h1_asset->cmodels[i].leaf.collAabbCount = asset->cModels[i].leaf.collAabbCount;
				h1_asset->cmodels[i].leaf.brushContents = asset->cModels[i].leaf.brushContents;
				h1_asset->cmodels[i].leaf.terrainContents = asset->cModels[i].leaf.terrainContents;
				memcpy(&h1_asset->cmodels[i].leaf.bounds, &asset->cModels[i].leaf.bounds, sizeof(IW5::Bounds));
				h1_asset->cmodels[i].leaf.leafBrushNode = asset->cModels[i].leaf.leafBrushNode;
			}

			h1_asset->mapEnts = mem->Alloc<H1::MapEnts>();
			h1_asset->mapEnts->name = asset->mapEnts->name;

			h1_asset->stageCount = asset->stageCount;
			h1_asset->stages = mem->Alloc<H1::Stage>(h1_asset->stageCount);
			for (unsigned int i = 0; i < h1_asset->stageCount; i++)
			{
				h1_asset->stages[i].name = reinterpret_cast<const char* __ptr64>(asset->stages[i].name);
				memcpy(&h1_asset->stages[i].origin, &asset->stages[i].origin, sizeof(float[3]));
				h1_asset->stages[i].triggerIndex = asset->stages[i].triggerIndex;
				h1_asset->stages[i].sunPrimaryLightIndex = asset->stages[i].sunPrimaryLightIndex;
				h1_asset->stages[i].unk = 0x3A83126F;
			}
			h1_asset->stageTrigger.count = 0;
			h1_asset->stageTrigger.models = nullptr;
			h1_asset->stageTrigger.hullCount = 0;
			h1_asset->stageTrigger.hulls = nullptr;
			h1_asset->stageTrigger.slabCount = 0;
			h1_asset->stageTrigger.slabs = nullptr;

			for (unsigned char i = 0; i < 2; i++)
			{
				h1_asset->dynEntCount[i] = asset->dynEntCount[i];
				h1_asset->dynEntDefList[i] = mem->Alloc<H1::DynEntityDef>(h1_asset->dynEntCount[i]);
				h1_asset->dynEntPoseList[i] = reinterpret_cast<H1::DynEntityPose * __ptr64>(asset->dynEntPoseList[i]); // check
				h1_asset->dynEntClientList[i] = mem->Alloc<H1::DynEntityClient>(h1_asset->dynEntCount[i]);
				h1_asset->dynEntCollList[i] = reinterpret_cast<H1::DynEntityColl * __ptr64>(asset->dynEntCollList[i]);
				for (unsigned short j = 0; j < h1_asset->dynEntCount[i]; j++)
				{
					h1_asset->dynEntDefList[i][j].type = static_cast<H1::DynEntityType>(asset->dynEntDefList[i][j].type);
					memcpy(&h1_asset->dynEntDefList[i][j].pose, &asset->dynEntDefList[i][j].pose, sizeof(IW5::GfxPlacement));
					h1_asset->dynEntDefList[i][j].baseModel = reinterpret_cast<H1::XModel * __ptr64>(asset->dynEntDefList[i][j].xModel);
					h1_asset->dynEntDefList[i][j].brushModel = asset->dynEntDefList[i][j].brushModel;
					h1_asset->dynEntDefList[i][j].physicsBrushModel = asset->dynEntDefList[i][j].physicsBrushModel;
					h1_asset->dynEntDefList[i][j].health = asset->dynEntDefList[i][j].health;
					h1_asset->dynEntDefList[i][j].destroyFx = reinterpret_cast<H1::FxEffectDef * __ptr64>(asset->dynEntDefList[i][j].destroyFx);
					h1_asset->dynEntDefList[i][j].sound = nullptr;
					h1_asset->dynEntDefList[i][j].physPreset = reinterpret_cast<H1::PhysPreset * __ptr64>(asset->dynEntDefList[i][j].physPreset);
					h1_asset->dynEntDefList[i][j].hinge = reinterpret_cast<H1::DynEntityHingeDef * __ptr64>(asset->dynEntDefList[i][j].hinge);
					h1_asset->dynEntDefList[i][j].linkTo = nullptr;
					memcpy(&h1_asset->dynEntDefList[i][j].mass, &asset->dynEntDefList[i][j].mass, sizeof(IW5::PhysMass));
					h1_asset->dynEntDefList[i][j].contents = asset->dynEntDefList[i][j].contents;
					if (1) // check
					{
						h1_asset->dynEntDefList[i][j].unk[0] = 2500.00000f;
						h1_asset->dynEntDefList[i][j].unk[1] = 0.0199999996f;
					}

					h1_asset->dynEntClientList[i][j].physObjId = asset->dynEntClientList[i]->physObjId;
					h1_asset->dynEntClientList[i][j].flags = asset->dynEntClientList[i]->flags;
					h1_asset->dynEntClientList[i][j].lightingHandle = asset->dynEntClientList[i]->lightingHandle;
					h1_asset->dynEntClientList[i][j].health = asset->dynEntClientList[i]->health;
					h1_asset->dynEntClientList[i][j].hinge = nullptr;
					h1_asset->dynEntClientList[i][j].activeModel = nullptr;
					h1_asset->dynEntClientList[i][j].contents = asset->dynEntClientList[i]->contents;
				}
			}

			h1_asset->dynEntAnchorCount = 0;
			h1_asset->dynEntAnchorNames = nullptr;

			h1_asset->scriptableMapEnts;

			h1_asset->grappleData;

			h1_asset->checksum = asset->isPlutoniumMap;

			return h1_asset;
		}

		H1::PhysWorld* generate_physics_world(H1::clipMap_t* col_map, allocator& allocator)
		{
			// TODO: 
			// - remove duplicate vertexes and (triangles?)
			// - fix brush triangle vertex indexes
			// - optimize node generation?
			// - add partition code
			//

			const auto mem = &allocator;

			auto* phys_col_map = mem->allocate<H1::PhysWorld>();

			phys_col_map->name = mem->duplicate_string(col_map->name);

			phys_col_map->brushModelCount = col_map->numSubModels;
			phys_col_map->brushModels = mem->allocate<H1::PhysBrushModel>(phys_col_map->brushModelCount);
			memset(phys_col_map->brushModels, 0, sizeof(H1::PhysBrushModel) * phys_col_map->brushModelCount);

			for (auto i = 0u; i < phys_col_map->brushModelCount; i++)
			{
				auto* model = &phys_col_map->brushModels[i];
				model->fields.polytopeIndex = -1;
				model->fields.unk = -1;
				model->fields.worldIndex = 0;
				model->fields.meshIndex = 0;
			}

			phys_col_map->meshDataCount = 1;
			phys_col_map->meshDatas = mem->allocate<H1::dmMeshData>(1);
			memset(phys_col_map->meshDatas, 0, sizeof(H1::dmMeshData) * 1);

			auto* mesh = &phys_col_map->meshDatas[0];

			std::vector<H1::dmFloat4> phys_verticies;
			std::vector<H1::dmMeshTriangle> phys_triangles;

			int vert_index = 0;
			int tri_index = 0;

			int base_index = 0;

			for (auto brush_index = 0u; brush_index < col_map->info.bCollisionData.numBrushes; brush_index++)
			{
				auto* brush = &col_map->info.bCollisionData.brushes[brush_index];
				auto brush_bounds = col_map->info.bCollisionData.brushBounds[brush_index];
				auto brush_contents = col_map->info.bCollisionData.brushContents[brush_index];

				if ((brush_contents & 1) == 0)
				{
					continue;
				}

				float* center = brush_bounds.midPoint;
				float* halfSize = brush_bounds.halfSize;

				// Create the eight vertices of the box
				vec3_t v1{}, v2{}, v3{}, v4{}, v5{}, v6{}, v7{}, v8{};

				v1[0] = center[0] - halfSize[0];
				v1[1] = center[1] - halfSize[1];
				v1[2] = center[2] - halfSize[2];

				v2[0] = center[0] + halfSize[0];
				v2[1] = center[1] - halfSize[1];
				v2[2] = center[2] - halfSize[2];

				v3[0] = center[0] - halfSize[0];
				v3[1] = center[1] + halfSize[1];
				v3[2] = center[2] - halfSize[2];

				v4[0] = center[0] + halfSize[0];
				v4[1] = center[1] + halfSize[1];
				v4[2] = center[2] - halfSize[2];

				v5[0] = center[0] - halfSize[0];
				v5[1] = center[1] - halfSize[1];
				v5[2] = center[2] + halfSize[2];

				v6[0] = center[0] + halfSize[0];
				v6[1] = center[1] - halfSize[1];
				v6[2] = center[2] + halfSize[2];

				v7[0] = center[0] - halfSize[0];
				v7[1] = center[1] + halfSize[1];
				v7[2] = center[2] + halfSize[2];

				v8[0] = center[0] + halfSize[0];
				v8[1] = center[1] + halfSize[1];
				v8[2] = center[2] + halfSize[2];

				// Create the 12 triangles of the box by specifying the indices of their vertices
				std::vector<std::vector<int>> triangles =
				{
					// bottom
					{0, 1, 2}, // 0
					{1, 3, 5}, // 1
					{3, 2, 1}, // 2
					{2, 0, 4}, // 3
					// top
					{4, 5, 6}, // 4
					{5, 7, 3}, // 5
					{7, 6, 5}, // 6
					{6, 4, 2}, // 7
					// verticals
					{0, 4, 1}, // 8
					{1, 5, 4}, // 9
					{2, 6, 3}, // 10
					{3, 7, 6}, // 11
				};

				// Create a vector to hold all the vertices
				std::vector<H1::vec_t*> vertices = { v1, v2, v3, v4, v5, v6, v7, v8 };

				base_index = static_cast<int>(phys_verticies.size());
				for (size_t i = 0; i < vertices.size(); i++)
				{
					H1::dmFloat4 vert = { vertices[i][0], vertices[i][1], vertices[i][2], 0.0f };
					phys_verticies.push_back(vert);
					++vert_index;
				}

				for (size_t i = 0; i < triangles.size(); i++)
				{
					H1::dmMeshTriangle tri{};
					tri.i1 = base_index + triangles[i][0];
					tri.i2 = base_index + triangles[i][1];
					tri.i3 = base_index + triangles[i][2];
					tri.w1 = -1;
					tri.w2 = -1;
					tri.w3 = -1;
					tri.materialIndex = 0;
					tri.collisionFlags = 1;
					phys_triangles.push_back(tri);
					++tri_index;
				}
			}

			mesh->m_vertexCount = static_cast<int>(phys_verticies.size());
			mesh->m_triangleCount = static_cast<int>(phys_triangles.size());

			mesh->m_aVertices = mem->allocate<H1::dmFloat4>(mesh->m_vertexCount);
			memset(mesh->m_aVertices, 0, sizeof(H1::dmFloat4) * mesh->m_vertexCount);
			mesh->m_aTriangles = mem->allocate<H1::dmMeshTriangle>(mesh->m_triangleCount);
			memset(mesh->m_aTriangles, 0, sizeof(H1::dmMeshTriangle) * mesh->m_triangleCount);

			memcpy(mesh->m_aVertices, phys_verticies.data(), sizeof(H1::dmFloat4) * mesh->m_vertexCount);
			memcpy(mesh->m_aTriangles, phys_triangles.data(), sizeof(H1::dmMeshTriangle) * mesh->m_triangleCount);

			float unquan[3]{ 1.0f, 1.0f, 1.0f };
			{
				float max_f = std::numeric_limits<std::int16_t>().max();
				float min_f = std::numeric_limits<std::int16_t>().min();

				float maxs[3] = { min_f, min_f, min_f };
				float mins[3] = { max_f, max_f, max_f };
				for (auto v = 0; v < mesh->m_vertexCount; v++)
				{
					auto* vertex = &mesh->m_aVertices[v];
					maxs[0] = std::max(maxs[0], static_cast<float>(vertex->x));
					maxs[1] = std::max(maxs[1], static_cast<float>(vertex->y));
					maxs[2] = std::max(maxs[2], static_cast<float>(vertex->z));
					mins[0] = std::min(mins[0], static_cast<float>(vertex->x));
					mins[1] = std::min(mins[1], static_cast<float>(vertex->y));
					mins[2] = std::min(mins[2], static_cast<float>(vertex->z));
				}

				for (auto i = 0; i < 3; i++)
				{
					unquan[i] = std::max(
						maxs[i] / std::numeric_limits<std::int16_t>().max(),
						mins[i] / std::numeric_limits<std::int16_t>().min());
				}

				mesh->m_unquantize.x = unquan[0];
				mesh->m_unquantize.y = unquan[1];
				mesh->m_unquantize.z = unquan[2];

				mesh->m_center.x = 0;
				mesh->m_center.y = 0;
				mesh->m_center.z = 0;

				mesh->m_extents.x = floor(maxs[0]);
				mesh->m_extents.y = floor(maxs[1]);
				mesh->m_extents.z = floor(maxs[2]);
			}

			mesh->m_nodeCount = (mesh->m_triangleCount * 2) - 1;
			mesh->m_pRoot = mem->allocate<H1::dmMeshNode>(mesh->m_nodeCount);
			memset(mesh->m_pRoot, 0, sizeof(H1::dmMeshNode) * mesh->m_nodeCount);

			auto node_index = 0;
			for (auto idx = 0; idx < mesh->m_triangleCount; idx++)
			{
				auto* triangle = &mesh->m_aTriangles[idx];
				auto v1 = &mesh->m_aVertices[triangle->i1];
				auto v2 = &mesh->m_aVertices[triangle->i2];
				auto v3 = &mesh->m_aVertices[triangle->i3];

				float max_f = std::numeric_limits<std::uint16_t>().max();
				float min_f = std::numeric_limits<std::uint16_t>().min();

				float maxs[3] = { min_f, min_f, min_f };
				float mins[3] = { max_f, max_f, max_f };
				maxs[0] = std::max(maxs[0], static_cast<float>(v1->x));
				maxs[1] = std::max(maxs[1], static_cast<float>(v1->y));
				maxs[2] = std::max(maxs[2], static_cast<float>(v1->z));
				mins[0] = std::min(mins[0], static_cast<float>(v1->x));
				mins[1] = std::min(mins[1], static_cast<float>(v1->y));
				mins[2] = std::min(mins[2], static_cast<float>(v1->z));

				maxs[0] = std::max(maxs[0], static_cast<float>(v2->x));
				maxs[1] = std::max(maxs[1], static_cast<float>(v2->y));
				maxs[2] = std::max(maxs[2], static_cast<float>(v2->z));
				mins[0] = std::min(mins[0], static_cast<float>(v2->x));
				mins[1] = std::min(mins[1], static_cast<float>(v2->y));
				mins[2] = std::min(mins[2], static_cast<float>(v2->z));

				maxs[0] = std::max(maxs[0], static_cast<float>(v3->x));
				maxs[1] = std::max(maxs[1], static_cast<float>(v3->y));
				maxs[2] = std::max(maxs[2], static_cast<float>(v3->z));
				mins[0] = std::min(mins[0], static_cast<float>(v3->x));
				mins[1] = std::min(mins[1], static_cast<float>(v3->y));
				mins[2] = std::min(mins[2], static_cast<float>(v3->z));

				if (idx == mesh->m_triangleCount - 1)
				{
					mesh->m_pRoot[node_index].lowerX = std::numeric_limits<std::int16_t>().min();
					mesh->m_pRoot[node_index].lowerY = std::numeric_limits<std::int16_t>().min();
					mesh->m_pRoot[node_index].lowerZ = std::numeric_limits<std::int16_t>().min();
					mesh->m_pRoot[node_index].upperX = std::numeric_limits<std::int16_t>().max();
					mesh->m_pRoot[node_index].upperY = std::numeric_limits<std::int16_t>().max();
					mesh->m_pRoot[node_index].upperZ = std::numeric_limits<std::int16_t>().max();
					mesh->m_pRoot[node_index].anon.fields.axis = 0;
					mesh->m_pRoot[node_index].anon.fields.triangleCount = 1;
					mesh->m_pRoot[node_index].anon.fields.index = idx;
					node_index += 1;
				}
				else
				{
					mesh->m_pRoot[node_index].lowerX = std::numeric_limits<std::int16_t>().min();
					mesh->m_pRoot[node_index].lowerY = std::numeric_limits<std::int16_t>().min();
					mesh->m_pRoot[node_index].lowerZ = std::numeric_limits<std::int16_t>().min();
					mesh->m_pRoot[node_index].upperX = std::numeric_limits<std::int16_t>().max();
					mesh->m_pRoot[node_index].upperY = std::numeric_limits<std::int16_t>().max();
					mesh->m_pRoot[node_index].upperZ = std::numeric_limits<std::int16_t>().max();
					mesh->m_pRoot[node_index].anon.fields.axis = 0;
					mesh->m_pRoot[node_index].anon.fields.triangleCount = 0;
					mesh->m_pRoot[node_index].anon.fields.index = 2;

					mesh->m_pRoot[node_index + 1].lowerX = static_cast<std::int16_t>(floor(mins[0] / mesh->m_unquantize.x));
					mesh->m_pRoot[node_index + 1].lowerY = static_cast<std::int16_t>(floor(mins[1] / mesh->m_unquantize.y));
					mesh->m_pRoot[node_index + 1].lowerZ = static_cast<std::int16_t>(floor(mins[2] / mesh->m_unquantize.z));
					mesh->m_pRoot[node_index + 1].upperX = static_cast<std::int16_t>(floor(maxs[0] / mesh->m_unquantize.x));
					mesh->m_pRoot[node_index + 1].upperY = static_cast<std::int16_t>(floor(maxs[1] / mesh->m_unquantize.y));
					mesh->m_pRoot[node_index + 1].upperZ = static_cast<std::int16_t>(floor(maxs[2] / mesh->m_unquantize.z));
					mesh->m_pRoot[node_index + 1].anon.fields.axis = 0;
					mesh->m_pRoot[node_index + 1].anon.fields.triangleCount = 1;
					mesh->m_pRoot[node_index + 1].anon.fields.index = idx;
					node_index += 2;
				}
			}

			mesh->m_height = 127;
			mesh->contents = 1; // every collisionFlags

			if (!mesh->m_triangleCount)
			{
				mesh->m_aTriangles = nullptr;
			}
			if (!mesh->m_vertexCount)
			{
				mesh->m_aVertices = nullptr;
			}
			if (!mesh->m_nodeCount)
			{
				mesh->m_pRoot = nullptr;
			}

			phys_col_map->waterVolumeDefCount = 0;
			phys_col_map->waterVolumeDefs = nullptr;

			phys_col_map->polytopeCount = 0;
			phys_col_map->polytopeDatas = nullptr;

			return phys_col_map;
		}

		void IClipMap::dump(clipMap_t* asset, ZoneMemory* mem)
		{
			// generate h1 clipmap
			auto h1_asset = GenerateH1ClipMap(asset, mem);

			// dump h1 clipmap
			H1::IClipMap::dump(h1_asset, SL_ConvertToString);

			// dump physmap here too i guess, since it's needed.
			allocator allocator;
			auto* physmap = generate_physics_world(h1_asset, allocator);

			H1::IPhysWorld::dump(physmap, SL_ConvertToString);
		}
	}
}