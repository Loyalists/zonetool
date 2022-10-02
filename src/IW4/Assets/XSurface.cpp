// ======================= ZoneTool =======================
// zonetool, a fastfile linker for various
// Call of Duty titles.
//
// Project: https://github.com/ZoneTool/zonetool
// Author: RektInator (https://github.com/RektInator)
// License: GNU GPL v3.0
// ========================================================
#include "stdafx.hpp"
#include <h2utils/assetmanager.hpp>

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
						(data[surf].vertexInfo.vertCount[1] * 3) + (data[surf].vertexInfo.vertCount[2] * 5) + (data[surf].vertexInfo.vertCount[3] * 7));
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

		void IXSurface::PrepareVertexWeights(zonetool::XSurface* asset)
		{
			// from: https://github.com/Scobalula/Greyhound/blob/15641dae5383190e43b2396d12b8868723735917/src/WraithXCOD/WraithXCOD/CoDXModelTranslator.cpp#L577
			// The index of read weight data
			uint32_t WeightDataIndex = 0;
			auto blendVerts = reinterpret_cast<zonetool::XBlendInfo*>(asset->blendVerts);
			int blendVertsDataLength = asset->blendVertCounts[0] + 3 * asset->blendVertCounts[1] + 5 * asset->blendVertCounts[2] + 7 * asset->blendVertCounts[3];
			int currentPosition = 0;
			struct WeightsData {
				unsigned short BoneValues[4];
				unsigned short WeightValues[4];
				uint8_t WeightCount;
			};

			std::vector<WeightsData> Weights = std::vector<WeightsData>(asset->vertCount);

			// Prepare the simple, rigid weights
			for (uint32_t i = 0; i < asset->rigidVertListCount; i++)
			{
				// Simple weights build, rigid, just apply the proper bone id
				uint32_t VertexCount = 0;
				uint32_t BoneIndex = 0;

				// Read rigid struct, QS does not have the pointer
				auto RigidInfo = reinterpret_cast<zonetool::XRigidVertList*>(asset->rigidVertLists);
				VertexCount = RigidInfo->vertCount;
				BoneIndex = RigidInfo->boneOffset / 64;

				// Apply bone ids properly
				for (uint32_t w = 0; w < VertexCount; w++)
				{
					Weights[WeightDataIndex].WeightCount = 1;
					// Apply
					Weights[WeightDataIndex].BoneValues[0] = BoneIndex;
					Weights[WeightDataIndex].WeightValues[0] = 65536;
					// Advance
					WeightDataIndex++;
				}
			}

			// Prepare single bone weights
			for (uint32_t w = 0; w < asset->blendVertCounts[0]; w++)
			{
				Weights[WeightDataIndex].WeightCount = 1;
				// Apply
				Weights[WeightDataIndex].BoneValues[0] = (blendVerts[currentPosition++] / 64);
				Weights[WeightDataIndex].WeightValues[0] = 65536;
				// Advance
				WeightDataIndex++;
			}

			// Prepare two bone weights
			for (uint32_t w = 0; w < asset->blendVertCounts[1]; w++)
			{
				// Set size
				Weights[WeightDataIndex].WeightCount = 2;

				// Read IDs (1, 2)
				Weights[WeightDataIndex].BoneValues[0] = (blendVerts[currentPosition++] / 64);
				Weights[WeightDataIndex].BoneValues[1] = (blendVerts[currentPosition++] / 64);
				// Read value for 2 and calculate 1
				Weights[WeightDataIndex].WeightValues[1] = blendVerts[currentPosition++];
				Weights[WeightDataIndex].WeightValues[0] = (65536 - Weights[WeightDataIndex].WeightValues[1]);

				// Advance
				WeightDataIndex++;
			}

			// Prepare three bone weights
			for (uint32_t w = 0; w < asset->blendVertCounts[2]; w++)
			{
				// Set size
				Weights[WeightDataIndex].WeightCount = 3;

				// Read 2 IDs (1, 2)
				Weights[WeightDataIndex].BoneValues[0] = (blendVerts[currentPosition++] / 64);
				Weights[WeightDataIndex].BoneValues[1] = (blendVerts[currentPosition++] / 64);
				// Read value for 2
				Weights[WeightDataIndex].WeightValues[1] = blendVerts[currentPosition++];
				// Read 1 ID (3)
				Weights[WeightDataIndex].BoneValues[2] = (blendVerts[currentPosition++] / 64);
				// Read value for 3
				Weights[WeightDataIndex].WeightValues[2] = blendVerts[currentPosition++];
				// Calculate first value
				Weights[WeightDataIndex].WeightValues[0] = (65536 - (Weights[WeightDataIndex].WeightValues[1] + Weights[WeightDataIndex].WeightValues[2]));

				// Advance
				WeightDataIndex++;
			}

			// Prepare four bone weights
			for (uint32_t w = 0; w < asset->blendVertCounts[3]; w++)
			{
				// Set size
				Weights[WeightDataIndex].WeightCount = 4;

				// Read 2 IDs (1, 2)
				Weights[WeightDataIndex].BoneValues[0] = (blendVerts[currentPosition++] / 64);
				Weights[WeightDataIndex].BoneValues[1] = (blendVerts[currentPosition++] / 64);
				// Read value for 2
				Weights[WeightDataIndex].WeightValues[1] = blendVerts[currentPosition++];
				// Read 1 ID (3)
				Weights[WeightDataIndex].BoneValues[2] = blendVerts[currentPosition++];
				// Read value for 3
				Weights[WeightDataIndex].WeightValues[2] = blendVerts[currentPosition++];
				// Read 1 ID (4)
				Weights[WeightDataIndex].BoneValues[3] = (blendVerts[currentPosition++] / 64);
				// Read value for 4
				Weights[WeightDataIndex].WeightValues[3] = blendVerts[currentPosition++];
				// Calculate first value
				Weights[WeightDataIndex].WeightValues[0] = (65536 - (Weights[WeightDataIndex].WeightValues[1] + Weights[WeightDataIndex].WeightValues[2] + Weights[WeightDataIndex].WeightValues[3]));

				// Advance
				WeightDataIndex++;
			}

			auto blendVertsTable = reinterpret_cast<zonetool::BlendVertsUnknown*>(asset->blendVertsTable);
			for (uint32_t i = 0; i < asset->vertCount; i++) {
				blendVertsTable[i].blendVertCountIndex = Weights[i].WeightCount;
				for (uint32_t bonePos = 0; bonePos < Weights[i].WeightCount; bonePos++) {
					blendVertsTable[i].b[bonePos] = Weights[i].BoneValues[bonePos];
					// the first weight is to be computed so fall back
					uint32_t weightPos = bonePos + 8 - 1;
					if (bonePos != 0) {
						blendVertsTable[i].b[weightPos] = Weights[i].WeightValues[bonePos];
					}
				}
			}
		}

		void IXSurface::ConvertXSurface(zonetool::XSurface* surf, XSurface* asset)
		{
			// character assets have this set as 6 while weapons set this as 2...
			surf->flags = 6;
			surf->vertCount = asset->vertCount;
			surf->triCount = asset->triCount;
			memset(surf->blendVertCounts, 0, sizeof(zonetool::XSurface::blendVertCounts));
			memcpy(surf->blendVertCounts, asset->vertexInfo.vertCount, sizeof(XSurfaceVertexInfo::vertCount));

			int blendVertsDataLength = asset->vertexInfo.vertCount[0] + 3 * asset->vertexInfo.vertCount[1] + 5 * asset->vertexInfo.vertCount[2] + 7 * asset->vertexInfo.vertCount[3];

			int blendVertsTotal = asset->vertexInfo.vertCount[0] + asset->vertexInfo.vertCount[1] + asset->vertexInfo.vertCount[2] + asset->vertexInfo.vertCount[3];

			auto packedVerts0 = new zonetool::GfxPackedVertex[asset->vertCount]();
			auto unknown0 = new zonetool::UnknownXSurface0[asset->vertCount]();

			for (int v = 0; v < asset->vertCount; v++)
			{
				auto& vert = packedVerts0[v];
				memcpy(vert.xyz, asset->verticies[v].xyz, sizeof(GfxPackedVertex::xyz));
				vert.binormalSign = asset->verticies[v].binormalSign;
				unsigned char arr[4];
				for (int j = 0; j < 4; j++)
				{
					arr[j] = static_cast<unsigned char>(asset->verticies[v].color.array[j]);
				}
				// wtf is this
				vert.color = {
					{arr[0], arr[1], arr[2], arr[3]},
				};
				vert.texCoord = {
					.packed = asset->verticies[v].texCoord.packed };
				vert.normal = {
					.packed = asset->verticies[v].normal.packed };
				vert.tangent = {
					.packed = asset->verticies[v].tangent.packed };

				memcpy(unknown0[v].xyz, vert.xyz, sizeof(zonetool::GfxPackedVertex::xyz));
				unknown0[v].normal = vert.normal;
			}

			surf->verts0.packedMotionVerts0 = 0;
			surf->verts0.packedVerts0 = 0;
			surf->verts0.verts0 = 0;
			surf->unknown0 = reinterpret_cast<std::uint64_t>(unknown0);

			// everybody gangsta until reinterpret_cast returns 0
			surf->verts0.packedVerts0 = reinterpret_cast<std::uint64_t>(packedVerts0);
			surf->verts0.packedMotionVerts0 = surf->verts0.packedVerts0;

			auto triIndices = new zonetool::Face[asset->triCount]();
			auto triIndices2 = new zonetool::Face[asset->triCount]();
			for (int f = 0; f < asset->triCount; f++)
			{
				auto& face = triIndices[f];
				face.v1 = asset->triIndices[f].v1;
				face.v2 = asset->triIndices[f].v2;
				face.v3 = asset->triIndices[f].v3;
			}
			memcpy(triIndices2, triIndices, asset->triCount * sizeof(zonetool::Face));
			surf->triIndices = reinterpret_cast<std::uint64_t>(triIndices);
			surf->triIndices2 = reinterpret_cast<std::uint64_t>(triIndices2);

			surf->rigidVertListCount = asset->vertListCount;
			auto rigidVertLists = new zonetool::XRigidVertList[asset->vertListCount]();
			for (int j = 0; j < asset->vertListCount; j++)
			{
				rigidVertLists[j].boneOffset = asset->rigidVertLists->boneOffset;
				rigidVertLists[j].vertCount = asset->rigidVertLists->vertCount;
				rigidVertLists[j].triOffset = asset->rigidVertLists->triOffset;
				rigidVertLists[j].triCount = asset->rigidVertLists->triCount;
				rigidVertLists[j].collisionTree = 0;

				if (asset->rigidVertLists->collisionTree)
				{
					auto collisionTree = new zonetool::XSurfaceCollisionTree();
					memcpy(collisionTree->trans, asset->rigidVertLists->collisionTree->trans, sizeof(XSurfaceCollisionTree::trans));
					memcpy(collisionTree->scale, asset->rigidVertLists->collisionTree->scale, sizeof(XSurfaceCollisionTree::scale));
					collisionTree->nodeCount = asset->rigidVertLists->collisionTree->nodeCount;
					auto nodes = new zonetool::XSurfaceCollisionNode[collisionTree->nodeCount]();
					for (int n = 0; n < collisionTree->nodeCount; n++)
					{
						memcpy(nodes[n].aabb.mins, asset->rigidVertLists->collisionTree->nodes[n].aabb.mins, sizeof(XSurfaceCollisionAabb::mins));
						memcpy(nodes[n].aabb.maxs, asset->rigidVertLists->collisionTree->nodes[n].aabb.maxs, sizeof(XSurfaceCollisionAabb::maxs));
						nodes[n].childBeginIndex = asset->rigidVertLists->collisionTree->nodes[n].childBeginIndex;
						nodes[n].childCount = asset->rigidVertLists->collisionTree->nodes[n].childCount;
					}
					collisionTree->nodes = reinterpret_cast<std::uint64_t>(nodes);

					collisionTree->leafCount = asset->rigidVertLists->collisionTree->leafCount;
					auto leafs = new zonetool::XSurfaceCollisionLeaf[collisionTree->leafCount]();
					for (int n = 0; n < collisionTree->leafCount; n++)
					{
						leafs[n].triangleBeginIndex = asset->rigidVertLists->collisionTree->leafs[n].triangleBeginIndex;
					}
					collisionTree->leafs = reinterpret_cast<std::uint64_t>(leafs);

					rigidVertLists[j].collisionTree = reinterpret_cast<std::uint64_t>(collisionTree);
				}
			}
			surf->rigidVertLists = reinterpret_cast<std::uint64_t>(rigidVertLists);

			//auto lmapUnwrap = new zonetool::alignVertBufFloat16Vec2_t[asset->vertCount]();
			//for (int j = 0; j < asset->vertCount; j++)
			//{
			//	lmapUnwrap[0][j] = 0;
			//	lmapUnwrap[1][j] = 0;
			//}
			//surf->lmapUnwrap = reinterpret_cast<std::uint64_t>(lmapUnwrap);

			if (blendVertsTotal > 0)
			{
				auto blendVerts = new zonetool::XBlendInfo[blendVertsDataLength]();
				for (int j = 0; j < blendVertsDataLength; j++)
				{
					blendVerts[j] = asset->vertexInfo.vertsBlend[j];
				}
				surf->blendVerts = reinterpret_cast<std::uint64_t>(blendVerts);

				auto blendVertsTable = new zonetool::BlendVertsUnknown[asset->vertCount]();
				surf->blendVertsTable = reinterpret_cast<std::uint64_t>(blendVertsTable);
				PrepareVertexWeights(surf);

				// auto tensionData = new zonetool::alignCompBufFloat_t[blendVertsTotal]();
				// for (int j = 0; j < blendVertsTotal; j++)
				// {
				// 	tensionData[j] = 0;
				// }

				// surf->tensionData = reinterpret_cast<std::uint64_t>(tensionData);

				// auto tensionAccumTable = new zonetool::alignCompBufUShort_t[asset->vertCount][16]();
				// for (int j = 0; j < asset->vertCount; j++)
				// {
				// 	for (int k = 0; k < 16; k++)
				// 		tensionAccumTable[j][k] = 0;
				// }
				// surf->tensionAccumTable = reinterpret_cast<std::uint64_t>(tensionAccumTable);
			}
		}

		void IXSurface::dump(XModelSurfs* asset)
		{
			const auto name = reinterpret_cast<std::uint64_t>(asset->name);
			auto surfs = new zonetool::XSurface[asset->numsurfs]();

			for (int i = 0; i < asset->numsurfs; i++)
			{
				ConvertXSurface(&surfs[i], &asset->surfs[i]);
			}

			auto converted_asset = new zonetool::XModelSurfs{
				.name = name,
				.surfs = reinterpret_cast<std::uint64_t>(surfs),
				.numsurfs = asset->numsurfs,
				.partBits = {0},
			};

			dump_converted(converted_asset);
		}

		void IXSurface::dump_converted(zonetool::XModelSurfs* asset)
		{
			const char* name = reinterpret_cast<const char*>(asset->name);
			auto surfs = reinterpret_cast<zonetool::XSurface*>(asset->surfs);

			const auto path = "xsurface\\"s + name + ".xsurface_export";

			zonetool::assetmanager::dumper dump;
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

				dump.dump_raw(blendVerts, 2 * (surfs[i].blendVertCounts[0] + 3 * surfs[i].blendVertCounts[1] + 5 * surfs[i].blendVertCounts[2] + 7 * surfs[i].blendVertCounts[3] + 9 * surfs[i].blendVertCounts[4] + 11 * surfs[i].blendVertCounts[5] + 13 * surfs[i].blendVertCounts[6] + 15 * surfs[i].blendVertCounts[7]));
				dump.dump_raw(blendVertsTable, 32 * surfs[i].vertCount);

				dump.dump_raw(lmapUnwrap, 4 * surfs[i].vertCount);

				dump.dump_raw(tensionData, 4 * (surfs[i].blendVertCounts[0] + surfs[i].blendVertCounts[1] + surfs[i].blendVertCounts[2] + surfs[i].blendVertCounts[3] + surfs[i].blendVertCounts[4] + surfs[i].blendVertCounts[5] + surfs[i].blendVertCounts[6] + surfs[i].blendVertCounts[7]));
				dump.dump_raw(tensionAccumTable, 32 * surfs[i].vertCount);

				// DEBUG
				//ZONETOOL_INFO("vertCount: %d", surfs[i].vertCount);
				//ZONETOOL_INFO("triCount: %d", surfs[i].triCount);
				//auto packedMotionVerts0 = reinterpret_cast<zonetool::GfxPackedMotionVertex*>(surfs[i].verts0.packedMotionVerts0);
				//auto packedVerts0 = reinterpret_cast<zonetool::GfxPackedVertex*>(surfs[i].verts0.packedVerts0);
				//ZONETOOL_INFO("packedMotionVerts0: %p", packedMotionVerts0);
				//ZONETOOL_INFO("packedVerts0: %p", packedVerts0);
				//ZONETOOL_INFO("rigidVertLists: %p", rigidVertLists);
				//ZONETOOL_INFO("surfs[i].rigidVertListCount: %d", surfs[i].rigidVertListCount);
				//std::stringstream ss2;
				//for (int j = 0; j < surfs[i].vertCount; j++) {
				//	if (!surfs[i].blendVertsTable) {
				//		break;
				//	}

				//	auto blendVertsTable = reinterpret_cast<zonetool::BlendVertsUnknown*>(surfs[i].blendVertsTable);

				//	for (int k = 0; k < 15; k++) {
				//		ss2 << blendVertsTable[j].b[k];
				//		ss2 << " ";
				//	}
				//	std::string out = ss2.str();
				//	ZONETOOL_INFO("blendVertsTable[j].b: %s", out.c_str());
				//	ZONETOOL_INFO("blendVertsTable[j].blendVertCountIndex: %d", blendVertsTable[j].blendVertCountIndex);
				//	ss2.clear();
				//	ss2.str("");
				//}
			}

			dump.close();
		}
	}
}
