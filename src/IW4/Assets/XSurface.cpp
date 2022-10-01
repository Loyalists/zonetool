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
	namespace IW4
	{
		XModelSurfs* IXSurface::parse(const std::string& name, ZoneMemory* mem)
		{
			AssetReader read(mem);
			
			if (!read.open("XSurface\\" + name + ".xsurface_export"))
			{
				return nullptr;
			}

			ZONETOOL_INFO("Parsing xmodel surface \"%s\"...", name.c_str());

			auto asset = read.read_array<XModelSurfs>();
			asset->name = read.read_string();

			asset->surfs = mem->Alloc<XSurface>(asset->numsurfs);

			for (int i = 0; i < asset->numsurfs; i++)
			{
				asset->surfs[i].tileMode = read.read_int();
				asset->surfs[i].deformed = read.read_int();
				asset->surfs[i].baseTriIndex = read.read_int();
				asset->surfs[i].baseVertIndex = read.read_int();

				for (int j = 0; j < 6; j++)
				{
					asset->surfs[i].partBits[j] = read.read_int();
				}

				// vertex
				auto vertexInfo = read.read_array<XSurfaceVertexInfo>();
				memcpy(&asset->surfs[i].vertexInfo, vertexInfo, sizeof XSurfaceVertexInfo);
				asset->surfs[i].vertexInfo.vertsBlend = read.read_array<unsigned short>();

				// verticies
				asset->surfs[i].vertCount = read.read_int();
				asset->surfs[i].verticies = read.read_array<GfxPackedVertex>();

				// triangles
				asset->surfs[i].triCount = read.read_int();
				asset->surfs[i].triIndices = read.read_array<Face>();

				// rigidVertLists
				asset->surfs[i].vertListCount = read.read_int();
				asset->surfs[i].rigidVertLists = read.read_array<XRigidVertList>();
				for (int vert = 0; vert < asset->surfs[i].vertListCount; vert++)
				{
					if (asset->surfs[i].rigidVertLists[vert].collisionTree)
					{
						asset->surfs[i].rigidVertLists[vert].collisionTree = read.read_array<XSurfaceCollisionTree>();

						if (asset->surfs[i].rigidVertLists[vert].collisionTree->leafs)
						{
							asset->surfs[i].rigidVertLists[vert].collisionTree->leafs = read.read_array<
								XSurfaceCollisionLeaf>();
						}

						if (asset->surfs[i].rigidVertLists[vert].collisionTree->nodes)
						{
							asset->surfs[i].rigidVertLists[vert].collisionTree->nodes = read.read_array<
								XSurfaceCollisionNode>();
						}
					}
					else
					{
						asset->surfs[i].rigidVertLists[vert].collisionTree = nullptr;
					}
				}
			}

			read.close();

			return asset;
		}

		void IXSurface::init(const std::string& name, ZoneMemory* mem)
		{
			this->name_ = name;
			this->asset_ = this->parse(name, mem);

			if (!this->asset_)
			{
				this->asset_ = DB_FindXAssetHeader(this->type(), this->name_.data()).xsurface;
			}
		}

		void IXSurface::init(void* asset, ZoneMemory* mem)
		{
			this->asset_ = reinterpret_cast<XModelSurfs*>(asset);
			this->name_ = this->asset_->name;
		}

		void IXSurface::prepare(ZoneBuffer* buf, ZoneMemory* mem)
		{
		}

		void IXSurface::load_depending(IZone* zone)
		{
		}

		std::string IXSurface::name()
		{
			return this->name_;
		}

		std::int32_t IXSurface::type()
		{
			return xmodelsurfs;
		}

		void IXSurface::write_xsurfaces(IZone* zone, ZoneBuffer* buf, XSurface* data, std::uint16_t count)
		{
			assert(sizeof XSurface, 64);
			assert(sizeof Face, 6);
			assert(sizeof XRigidVertList, 12);
			assert(sizeof XSurfaceCollisionTree, 40);
			assert(sizeof XSurfaceCollisionLeaf, 2);
			assert(sizeof XSurfaceCollisionAabb, 12);
			assert(sizeof XSurfaceCollisionNode, 16);
			assert(sizeof GfxPackedVertex, 32);
			assert(sizeof XSurfaceVertexInfo, 12);

			auto* dest = buf->write(data, count);
			
			for (auto surf = 0u; surf < count; surf++)
			{
				if (data[surf].vertexInfo.vertsBlend)
				{
					dest[surf].vertexInfo.vertsBlend = buf->write_s(1, data[surf].vertexInfo.vertsBlend,
						data[surf].vertexInfo.vertCount[0] +
						(data[surf].vertexInfo.vertCount[1] * 3) + (data[
							surf].vertexInfo.vertCount[2] * 5) + (data[
								surf].vertexInfo.vertCount[3] * 7));
				}

				buf->push_stream(6);
				if (data[surf].verticies)
				{
					dest[surf].verticies = buf->write_s(15, data[surf].verticies, data[surf].vertCount);
				}
				buf->pop_stream();

				if (data[surf].rigidVertLists)
				{
					XRigidVertList* ct = nullptr;
					dest[surf].rigidVertLists = buf->write_s(3, data[surf].rigidVertLists, data[surf].vertListCount,
					                                         sizeof XRigidVertList, &ct);

					if (dest[surf].rigidVertLists == reinterpret_cast<XRigidVertList*>(-1))
					{
						for (auto k = 0; k < data[surf].vertListCount; k++)
						{
							if (ct[k].collisionTree)
							{
								XSurfaceCollisionTree* entry = nullptr;
								ct[k].collisionTree = buf->write_s(3, ct[k].collisionTree, 1,
								                                   sizeof XSurfaceCollisionTree, &entry);

								if (ct[k].collisionTree == reinterpret_cast<XSurfaceCollisionTree*>(-1))
								{
									if (entry->nodes)
									{
										entry->nodes = buf->write_s(15, entry->nodes, entry->nodeCount);
									}

									if (entry->leafs)
									{
										entry->leafs = buf->write_s(1, entry->leafs, entry->leafCount);
									}
								}
							}
						}
					}
				}

				buf->push_stream(7);
				if (data[surf].triIndices)
				{
					dest[surf].triIndices = buf->write_s(15, data[surf].triIndices, data[surf].triCount);
				}
				buf->pop_stream();
			}
		}

		void IXSurface::write(IZone* zone, ZoneBuffer* buf)
		{
			auto* data = this->asset_;
			auto* dest = buf->write<XModelSurfs>(data);

			assert(sizeof XModelSurfs, 36);

			buf->push_stream(3);
			START_LOG_STREAM;

			dest->name = buf->write_str(this->name());

			if (data->surfs)
			{
				buf->align(3);
				write_xsurfaces(zone, buf, data->surfs, data->numsurfs);
				ZoneBuffer::clear_pointer(&dest->surfs);
			}

			END_LOG_STREAM;
			buf->pop_stream();
		}

		zonetool::XModelSurfs* IXSurface::ConvertXModelSurfs(XModelSurfs* asset) {
			const auto name = reinterpret_cast<std::uint64_t>(asset->name);
			auto surfs = new zonetool::XSurface[asset->numsurfs]();

			for (int i = 0; i < asset->numsurfs; i++) {
				surfs[i].flags = 0;
				surfs[i].vertCount = asset->surfs[i].vertCount;
				surfs[i].triCount = asset->surfs[i].triCount;
				memset(surfs[i].blendVertCounts, 0, sizeof(zonetool::XSurface::blendVertCounts));
				memcpy(surfs[i].blendVertCounts, asset->surfs[i].vertexInfo.vertCount, sizeof(XSurfaceVertexInfo::vertCount));

				int blendVertsDataLength = asset->surfs[i].vertexInfo.vertCount[0]
					+ 3 * asset->surfs[i].vertexInfo.vertCount[1]
					+ 5 * asset->surfs[i].vertexInfo.vertCount[2]
					+ 7 * asset->surfs[i].vertexInfo.vertCount[3];

				int blendVertsTotal = asset->surfs[i].vertexInfo.vertCount[0]
					+ asset->surfs[i].vertexInfo.vertCount[1]
					+ asset->surfs[i].vertexInfo.vertCount[2]
					+ asset->surfs[i].vertexInfo.vertCount[3];

				auto packedMotionVerts0 = new zonetool::GfxPackedMotionVertex[asset->surfs[i].vertCount]();
				auto unknown0 = new zonetool::UnknownXSurface0[asset->surfs[i].vertCount]();

				for (int v = 0; v < asset->surfs[i].vertCount; v++) {
					auto& vert = packedMotionVerts0[v];
					memcpy(vert.xyz, asset->surfs[i].verticies[v].xyz, sizeof(GfxPackedVertex::xyz));
					vert.binormalSignAndHeight = asset->surfs[i].verticies[v].binormalSign;
					unsigned char arr[4];
					memcpy(arr, asset->surfs[i].verticies[v].color.array, sizeof(arr));
					//wtf is this
					vert.pieceIndex = {
						{arr[0], arr[1], arr[2], arr[3]},
					};
					vert.texCoord = {
						.packed = asset->surfs[i].verticies[v].texCoord.packed
					};
					vert.normal = {
						.packed = asset->surfs[i].verticies[v].normal.packed
					};
					vert.tangent = {
						.packed = asset->surfs[i].verticies[v].tangent.packed
					};

					memcpy(unknown0[v].xyz, vert.xyz, sizeof(zonetool::GfxPackedVertex::xyz));
					unknown0[v].normal = vert.normal;
				}

				surfs[i].verts0.packedMotionVerts0 = reinterpret_cast<std::uint64_t>(packedMotionVerts0);
				surfs[i].verts0.packedVerts0 = 0;
				surfs[i].verts0.verts0 = 0;
				surfs[i].unknown0 = reinterpret_cast<std::uint64_t>(unknown0);

				auto triIndices = new zonetool::Face[asset->surfs[i].triCount]();
				auto triIndices2 = new zonetool::Face[asset->surfs[i].triCount]();
				for (int f = 0; f < asset->surfs[i].triCount; f++) {
					auto& face = triIndices[f];
					face.v1 = asset->surfs[i].triIndices[f].v1;
					face.v2 = asset->surfs[i].triIndices[f].v2;
					face.v3 = asset->surfs[i].triIndices[f].v3;
				}
				memcpy(triIndices2, triIndices, asset->surfs[i].triCount * sizeof(zonetool::Face));
				surfs[i].triIndices = reinterpret_cast<std::uint64_t>(triIndices);
				surfs[i].triIndices2 = reinterpret_cast<std::uint64_t>(triIndices2);

				surfs[i].rigidVertListCount = asset->surfs[i].vertListCount;
				auto rigidVertLists = new zonetool::XRigidVertList[asset->surfs[i].vertListCount]();
				for (int j = 0; j < asset->surfs[i].vertListCount; j++) {
					rigidVertLists[j].boneOffset = asset->surfs[i].rigidVertLists->boneOffset;
					rigidVertLists[j].vertCount = asset->surfs[i].rigidVertLists->vertCount;
					rigidVertLists[j].triOffset = asset->surfs[i].rigidVertLists->triOffset;
					rigidVertLists[j].triCount = asset->surfs[i].rigidVertLists->triCount;
					rigidVertLists[j].collisionTree = 0;

					if (asset->surfs[i].rigidVertLists->collisionTree) {
						auto collisionTree = new zonetool::XSurfaceCollisionTree();
						memcpy(collisionTree->trans, asset->surfs[i].rigidVertLists->collisionTree->trans, sizeof(XSurfaceCollisionTree::trans));
						memcpy(collisionTree->scale, asset->surfs[i].rigidVertLists->collisionTree->scale, sizeof(XSurfaceCollisionTree::scale));
						collisionTree->nodeCount = asset->surfs[i].rigidVertLists->collisionTree->nodeCount;
						auto nodes = new zonetool::XSurfaceCollisionNode[collisionTree->nodeCount]();
						for (int n = 0; n < collisionTree->nodeCount; n++) {
							memcpy(nodes[n].aabb.mins, asset->surfs[i].rigidVertLists->collisionTree->nodes[n].aabb.mins, sizeof(XSurfaceCollisionAabb::mins));
							memcpy(nodes[n].aabb.maxs, asset->surfs[i].rigidVertLists->collisionTree->nodes[n].aabb.maxs, sizeof(XSurfaceCollisionAabb::maxs));
							nodes[n].childBeginIndex = asset->surfs[i].rigidVertLists->collisionTree->nodes[n].childBeginIndex;
							nodes[n].childCount = asset->surfs[i].rigidVertLists->collisionTree->nodes[n].childCount;
						}
						collisionTree->nodes = reinterpret_cast<std::uint64_t>(nodes);

						collisionTree->leafCount = asset->surfs[i].rigidVertLists->collisionTree->leafCount;
						auto leafs = new zonetool::XSurfaceCollisionLeaf[collisionTree->leafCount]();
						for (int n = 0; n < collisionTree->leafCount; n++) {
							leafs[n].triangleBeginIndex = asset->surfs[i].rigidVertLists->collisionTree->leafs[n].triangleBeginIndex;
						}
						collisionTree->leafs = reinterpret_cast<std::uint64_t>(leafs);

						rigidVertLists[j].collisionTree = reinterpret_cast<std::uint64_t>(collisionTree);
					}
				}
				surfs[i].rigidVertLists = reinterpret_cast<std::uint64_t>(rigidVertLists);

				auto lmapUnwrap = new zonetool::alignVertBufFloat16Vec2_t[asset->surfs[i].vertCount]();
				for (int j = 0; j < asset->surfs[i].vertCount; j++) {
					lmapUnwrap[0][j] = 0;
					lmapUnwrap[1][j] = 0;
				}
				surfs[i].lmapUnwrap = reinterpret_cast<std::uint64_t>(lmapUnwrap);

				if (blendVertsTotal > 0) {
					auto blendVerts = new zonetool::XBlendInfo[blendVertsDataLength]();
					for (int j = 0; j < blendVertsDataLength; j++) {
						blendVerts[j] = asset->surfs[i].vertexInfo.vertsBlend[j];
					}
					surfs[i].blendVerts = reinterpret_cast<std::uint64_t>(blendVerts);

					auto tensionData = new zonetool::alignCompBufFloat_t[blendVertsTotal]();
					for (int j = 0; j < blendVertsTotal; j++) {
						tensionData[j] = 0;
					}

					surfs[i].tensionData = reinterpret_cast<std::uint64_t>(tensionData);

					auto tensionAccumTable = new zonetool::alignCompBufUShort_t[asset->surfs[i].vertCount][16]();
					for (int j = 0; j < asset->surfs[i].vertCount; j++) {
						for (int k = 0; k < 16; k++)
							tensionAccumTable[j][k] = 0;
					}
					surfs[i].tensionAccumTable = reinterpret_cast<std::uint64_t>(tensionAccumTable);
				}
			}

			auto casted_surfs = reinterpret_cast<std::uint64_t>(surfs);
			auto converted_asset = new zonetool::XModelSurfs {
				.name = name,
				.surfs = casted_surfs,
				.numsurfs = asset->numsurfs,
				.partBits = {0},
			};

			return converted_asset;
		}

		void IXSurface::dump(XModelSurfs* asset)
		{
			zonetool::XModelSurfs* converted_asset = ConvertXModelSurfs(asset);
			dump_converted(converted_asset);
		}

		void IXSurface::dump_converted(zonetool::XModelSurfs* asset)
		{
			const char* name = reinterpret_cast<const char*>(asset->name);
			auto surfs = reinterpret_cast<zonetool::XSurface*>(asset->surfs);

			const auto path = "xsurface\\"s + name + ".xsurface_export";

			AssetDumper dump;
			if (!dump.open(path))
			{
				return;
			}

			dump.dump_single(asset);
			dump.dump_string(name);

			dump.dump_array(surfs, asset->numsurfs);

			for (unsigned short i = 0; i < asset->numsurfs; i++)
			{
				if ((surfs[i].flags & 8) != 0)
				{
					auto packedMotionVerts0 = reinterpret_cast<zonetool::GfxPackedMotionVertex*>(surfs[i].verts0.packedMotionVerts0);
					dump.dump_array(packedMotionVerts0, surfs[i].vertCount);
				}
				else
				{
					auto packedVerts0 = reinterpret_cast<zonetool::GfxPackedVertex*>(surfs[i].verts0.packedVerts0);
					dump.dump_array(packedVerts0, surfs[i].vertCount);
				}

				auto triIndices = reinterpret_cast<zonetool::Face*>(surfs[i].triIndices);
				auto triIndices2 = reinterpret_cast<zonetool::Face*>(surfs[i].triIndices2);
				dump.dump_array(triIndices, surfs[i].triCount);
				dump.dump_array(triIndices2, surfs[i].triCount);

				auto rigidVertLists = reinterpret_cast<zonetool::XRigidVertList*>(surfs[i].rigidVertLists);
				dump.dump_array(rigidVertLists, surfs[i].rigidVertListCount);
				for (unsigned char vert = 0; vert < surfs[i].rigidVertListCount; vert++)
				{
					if (rigidVertLists)
					{
						auto collisionTree = reinterpret_cast<zonetool::XSurfaceCollisionTree*>(rigidVertLists[vert].collisionTree);
						if (collisionTree)
						{
							dump.dump_single(collisionTree);

							auto leafs = reinterpret_cast<zonetool::XSurfaceCollisionLeaf*>(collisionTree->leafs);
							auto nodes = reinterpret_cast<zonetool::XSurfaceCollisionNode*>(collisionTree->nodes);

							if (leafs)
							{
								dump.dump_array(leafs,
									collisionTree->leafCount);
							}
							if (nodes)
							{
								dump.dump_array(nodes,
									collisionTree->nodeCount);
							}
						}
					}
				}

				auto unknown0 = reinterpret_cast<zonetool::UnknownXSurface0*>(surfs[i].unknown0);
				auto blendVerts = reinterpret_cast<zonetool::XBlendInfo*>(surfs[i].blendVerts);
				auto blendVertsTable = reinterpret_cast<zonetool::BlendVertsUnknown*>(surfs[i].blendVertsTable);
				auto lmapUnwrap = reinterpret_cast<zonetool::alignVertBufFloat16Vec2_t**>(surfs[i].lmapUnwrap);
				auto tensionData = reinterpret_cast<zonetool::alignCompBufFloat_t*>(surfs[i].tensionData);
				auto tensionAccumTable = reinterpret_cast<zonetool::alignCompBufUShort_t*>(surfs[i].tensionAccumTable);

				dump.dump_raw(unknown0, 16 * surfs[i].vertCount);

				dump.dump_raw(blendVerts, 2 * (surfs[i].blendVertCounts[0]
					+ 3 * surfs[i].blendVertCounts[1]
					+ 5 * surfs[i].blendVertCounts[2]
					+ 7 * surfs[i].blendVertCounts[3]
					+ 9 * surfs[i].blendVertCounts[4]
					+ 11 * surfs[i].blendVertCounts[5]
					+ 13 * surfs[i].blendVertCounts[6]
					+ 15 * surfs[i].blendVertCounts[7]));
				dump.dump_raw(blendVertsTable, 32 * surfs[i].vertCount);

				dump.dump_raw(lmapUnwrap, 4 * surfs[i].vertCount);

				dump.dump_raw(tensionData, 4 * (surfs[i].blendVertCounts[0]
					+ surfs[i].blendVertCounts[1]
					+ surfs[i].blendVertCounts[2]
					+ surfs[i].blendVertCounts[3]
					+ surfs[i].blendVertCounts[4]
					+ surfs[i].blendVertCounts[5]
					+ surfs[i].blendVertCounts[6]
					+ surfs[i].blendVertCounts[7]));
				dump.dump_raw(tensionAccumTable, 32 * surfs[i].vertCount);

				//DEBUG
				//int blendVertsDataLength = surfs[i].blendVertCounts[0]
				//	+ 3 * surfs[i].blendVertCounts[1]
				//	+ 5 * surfs[i].blendVertCounts[2]
				//	+ 7 * surfs[i].blendVertCounts[3];

				//int blendVertsTotal = surfs[i].blendVertCounts[0]
				//	+ surfs[i].blendVertCounts[1]
				//	+ surfs[i].blendVertCounts[2]
				//	+ surfs[i].blendVertCounts[3];

				//ZONETOOL_INFO("surf: %d", i);
				//ZONETOOL_INFO("vertCount: %d", surfs[i].vertCount);
				//ZONETOOL_INFO("triCount: %d", surfs[i].triCount);
				//for (int j = 0; j < surfs[i].vertCount; j++) {
				//	auto packedMotionVerts0 = reinterpret_cast<zonetool::GfxPackedMotionVertex*>(surfs[i].verts0.packedMotionVerts0);
				//	ZONETOOL_INFO("xyz: %f %f %f", packedMotionVerts0[j].xyz[0], packedMotionVerts0[j].xyz[1], packedMotionVerts0[j].xyz[2]);
				//}

				//for (int j = 0; j < blendVertsDataLength; j++) {
				//	int weight = reinterpret_cast<int>(blendVerts);
				//	ZONETOOL_INFO("blendVert: %d", weight);
				//}
			}

			dump.close();
		}
	}
}
