#include "stdafx.hpp"
#include "H1/Assets/ClipMap.hpp"
#include "IW5/Structs.hpp"

#include "IW5/Assets/ClipMap.hpp"
#include "H1/Assets/PhysWorld.hpp"

namespace ZoneTool
{
	namespace IW4
	{
		void IClipMap::dump(clipMap_t* asset, ZoneMemory* mem)
		{
			auto* iw5_clipmap = mem->Alloc<IW5::clipMap_t>();
			memset(iw5_clipmap, 0, sizeof IW5::clipMap_t);

			// convert clipmap to IW5 format
			iw5_clipmap->name = asset->name;
			iw5_clipmap->isInUse = asset->isInUse;

			iw5_clipmap->info.planeCount = asset->numCPlanes;
			iw5_clipmap->info.planes = (IW5::cplane_s*)asset->cPlanes;

			iw5_clipmap->numStaticModels = asset->numStaticModels;
			iw5_clipmap->staticModelList = (IW5::cStaticModel_s*)asset->staticModelList;

			iw5_clipmap->info.numMaterials = asset->numMaterials;
			iw5_clipmap->info.materials = (IW5::ClipMaterial*)asset->materials;

			iw5_clipmap->info.numBrushSides = asset->numCBrushSides;
			iw5_clipmap->info.brushsides = (IW5::cbrushside_t*)asset->cBrushSides;

			iw5_clipmap->info.numBrushEdges = asset->numCBrushEdges;
			iw5_clipmap->info.brushEdges = (unsigned char*)asset->cBrushEdges;

			iw5_clipmap->numNodes = asset->numCNodes;
			iw5_clipmap->nodes = (IW5::cNode_t*)asset->cNodes;

			iw5_clipmap->numLeafs = asset->numCLeaf;
			iw5_clipmap->leafs = (IW5::cLeaf_t*)asset->cLeaf;

			iw5_clipmap->info.leafbrushNodesCount = asset->numCLeafBrushNodes;
			iw5_clipmap->info.leafbrushNodes = (IW5::cLeafBrushNode_s*)asset->cLeafBrushNodes;

			iw5_clipmap->info.numLeafBrushes = asset->numLeafBrushes;
			iw5_clipmap->info.leafbrushes = (unsigned short*)asset->leafBrushes;

			// leafSurfaces todo!

			iw5_clipmap->vertCount = asset->numVerts;
			iw5_clipmap->verts = (IW5::vec3_t*)asset->verts;

			iw5_clipmap->triCount = asset->numTriIndices;
			iw5_clipmap->triIndices = (unsigned short*)asset->triIndices;
			iw5_clipmap->triEdgeIsWalkable = (unsigned char*)asset->triEdgeIsWalkable;

			iw5_clipmap->borderCount = asset->numCollisionBorders;
			iw5_clipmap->borders = (IW5::CollisionBorder*)asset->collisionBorders;

			iw5_clipmap->partitionCount = asset->numCollisionPartitions;
			iw5_clipmap->partitions = (IW5::CollisionPartition*)asset->collisionPartitions;

			iw5_clipmap->aabbTreeCount = asset->numCollisionAABBTrees;
			iw5_clipmap->aabbTrees = (IW5::CollisionAabbTree*)asset->collisionAABBTrees;

			// cmodels!
			iw5_clipmap->numSubModels = asset->numCModels;
			iw5_clipmap->cmodels = mem->Alloc<IW5::cmodel_t>(iw5_clipmap->numSubModels);
			memset(iw5_clipmap->cmodels, 0, sizeof(IW5::cmodel_t) * iw5_clipmap->numSubModels);

			for (int i = 0; i < iw5_clipmap->numSubModels; i++)
			{
				memcpy(&iw5_clipmap->cmodels[i].bounds, &asset->cModels[i].bounds, sizeof(Bounds));
				iw5_clipmap->cmodels[i].radius = asset->cModels[i].radius;
				memcpy(&iw5_clipmap->cmodels[i].leaf, &asset->cModels[i].leaf, sizeof(cLeaf_t));
			}

			iw5_clipmap->info.numBrushes = asset->numBrushes;
			iw5_clipmap->info.brushes = (IW5::cbrush_t*)asset->brushes;
			iw5_clipmap->info.brushBounds = (IW5::Bounds*)asset->brushBounds;
			iw5_clipmap->info.brushContents = asset->brushContents;

			iw5_clipmap->mapEnts = (IW5::MapEnts*)asset->mapEnts;
			iw5_clipmap->stageCount = asset->mapEnts->stageCount;
			iw5_clipmap->stages = (IW5::Stage*)asset->mapEnts->stageNames;

			iw5_clipmap->smodelNodeCount = asset->smodelNodeCount;
			iw5_clipmap->smodelNodes = (IW5::SModelAabbNode*)asset->smodelNodes;

			// dynEnts
			for (int i = 0; i < 2; i++)
			{
				iw5_clipmap->dynEntCount[i] = asset->dynEntCount[i];

				if (iw5_clipmap->dynEntCount[i] <= 0)
				{
					continue;
				}
				
				iw5_clipmap->dynEntDefList[i] = mem->Alloc<IW5::DynEntityDef>(iw5_clipmap->dynEntCount[i]);
				iw5_clipmap->dynEntPoseList[i] = mem->Alloc<IW5::DynEntityPose>(iw5_clipmap->dynEntCount[i]);
				iw5_clipmap->dynEntClientList[i] = mem->Alloc<IW5::DynEntityClient>(iw5_clipmap->dynEntCount[i]);
				iw5_clipmap->dynEntCollList[i] = mem->Alloc<IW5::DynEntityColl>(iw5_clipmap->dynEntCount[i]);
				
				for (int j = 0; j < iw5_clipmap->dynEntCount[i]; j++)
				{
					iw5_clipmap->dynEntDefList[i][j].type = (IW5::DynEntityType)asset->dynEntDefList[i][j].type;
					memcpy(&iw5_clipmap->dynEntDefList[i][j].pose, &asset->dynEntDefList[i][j].pose, sizeof(IW5::DynEntityPose));
					iw5_clipmap->dynEntDefList[i][j].xModel = (IW5::XModel*)asset->dynEntDefList[i][j].xModel;
					iw5_clipmap->dynEntDefList[i][j].brushModel = asset->dynEntDefList[i][j].brushModel;
					iw5_clipmap->dynEntDefList[i][j].physicsBrushModel = asset->dynEntDefList[i][j].physicsBrushModel;
					iw5_clipmap->dynEntDefList[i][j].destroyFx = (IW5::FxEffectDef*)asset->dynEntDefList[i][j].destroyFx;
					iw5_clipmap->dynEntDefList[i][j].physPreset = (IW5::PhysPreset*)asset->dynEntDefList[i][j].physPreset;
					iw5_clipmap->dynEntDefList[i][j].health = asset->dynEntDefList[i][j].health;
					iw5_clipmap->dynEntDefList[i][j].hinge = nullptr;
					memcpy(&iw5_clipmap->dynEntDefList[i][j].mass, &asset->dynEntDefList[i][j].mass, sizeof(IW5::PhysMass));
					iw5_clipmap->dynEntDefList[i][j].contents = asset->dynEntDefList[i][j].contents;
					
					memcpy(&iw5_clipmap->dynEntPoseList[i][j], &asset->dynEntPoseList[i][j], sizeof(IW5::DynEntityPose));

					memcpy(&iw5_clipmap->dynEntClientList[i][j], &asset->dynEntClientList[i][j], sizeof(IW5::DynEntityClient) - sizeof(int));
					iw5_clipmap->dynEntClientList[i][j].hinge = 0;
					
					memcpy(&iw5_clipmap->dynEntCollList[i][j], &asset->dynEntCollList[i][j], sizeof(IW5::DynEntityColl));
				}
			}

			// dump clipmap
			IW5::IClipMap::dump(iw5_clipmap, mem);
		}
	}
}