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

		void write_xsurface(IZone* zone, ZoneBuffer* buf, zonetool::XSurface* dest, zonetool::XSurface* data)
		{
			dest->vb0 = 0;
			dest->vb0View = 0;
			dest->indexBuffer = 0;
			dest->blendVertsBuffer = 0;
			dest->blendVertsView = 0;
			dest->vblmapBuffer = 0;
			dest->vblmapView = 0;
			dest->tensionAccumTableBuffer = 0;
			dest->tensionAccumTableView = 0;
			dest->tensionDataBuffer = 0;
			dest->tensionDataView = 0;
			dest->indexBufferView = 0;

			if (data->verts0.verts0)
			{
				buf->align(15);
				if ((data->flags & 8) != 0)
				{
					buf->write(reinterpret_cast<GfxPackedMotionVertex*>(data->verts0.verts0), data->vertCount);
				}
				else
				{
					buf->write(reinterpret_cast<GfxPackedVertex*>(data->verts0.verts0), data->vertCount);
				}

				ZoneBuffer::clear_pointer(&dest->verts0.verts0);
			}

			if (data->triIndices)
			{
				buf->align(15);
				buf->write(data->triIndices, data->triCount);
				ZoneBuffer::clear_pointer(&dest->triIndices);
			}

			if (data->triIndices2)
			{
				buf->align(15);
				buf->write(data->triIndices2, data->triCount);
				ZoneBuffer::clear_pointer(&dest->triIndices2);
			}

			if (data->rigidVertLists)
			{
				buf->align(3);
				dest->rigidVertLists = buf->write(data->rigidVertLists, data->rigidVertListCount);
				for (unsigned char vert = 0; vert < data->rigidVertListCount; vert++)
				{
					if (data->rigidVertLists[vert].collisionTree)
					{
						buf->align(3);
						dest->rigidVertLists[vert].collisionTree = buf->write(data->rigidVertLists[vert].collisionTree);

						if (data->rigidVertLists[vert].collisionTree->nodes)
						{
							buf->align(15);
							dest->rigidVertLists[vert].collisionTree->nodes = buf->write(data->rigidVertLists[vert].collisionTree->nodes, data->rigidVertLists[vert].collisionTree->nodeCount);
						}

						if (data->rigidVertLists[vert].collisionTree->leafs)
						{
							buf->align(1);
							dest->rigidVertLists[vert].collisionTree->leafs = buf->write(data->rigidVertLists[vert].collisionTree->leafs, data->rigidVertLists[vert].collisionTree->leafCount);
						}
						ZoneBuffer::clear_pointer(&dest->rigidVertLists[vert].collisionTree);
					}
				}
				ZoneBuffer::clear_pointer(&dest->rigidVertLists);
			}

			if (data->unknown0)
			{
				buf->align(15);
				buf->write_stream(data->unknown0, 16, data->vertCount);
				ZoneBuffer::clear_pointer(&dest->unknown0);
			}

			if (data->blendVerts)
			{
				buf->align(1);
				buf->write_stream(data->blendVerts, 2, (data->blendVertCounts[0]
					+ 3 * data->blendVertCounts[1]
					+ 5 * data->blendVertCounts[2]
					+ 7 * data->blendVertCounts[3]
					+ 9 * data->blendVertCounts[4]
					+ 11 * data->blendVertCounts[5]
					+ 13 * data->blendVertCounts[6]
					+ 15 * data->blendVertCounts[7]));
				ZoneBuffer::clear_pointer(&dest->blendVerts);
			}

			if (data->blendVertsTable)
			{
				buf->align(0);
				buf->write_stream(data->blendVertsTable, 32, data->vertCount);
				ZoneBuffer::clear_pointer(&dest->blendVertsTable);
			}

			if (data->lmapUnwrap)
			{
				buf->align(3);
				buf->write_stream(data->lmapUnwrap, 4, data->vertCount);
				ZoneBuffer::clear_pointer(&dest->lmapUnwrap);
			}

			if (data->subdiv || data->subdivLevelCount)
			{
				dest->subdiv = nullptr;
				dest->subdivLevelCount = 0;
			}

			if (data->tensionData)
			{
				buf->align(3);
				buf->write_stream(data->tensionData, 4, (data->blendVertCounts[0]
					+ data->blendVertCounts[1]
					+ data->blendVertCounts[2]
					+ data->blendVertCounts[3]
					+ data->blendVertCounts[4]
					+ data->blendVertCounts[5]
					+ data->blendVertCounts[6]
					+ data->blendVertCounts[7]));

				ZoneBuffer::clear_pointer(&dest->tensionData);
			}

			if (data->tensionAccumTable)
			{
				buf->align(1);
				buf->write_stream(data->tensionAccumTable, 32, data->vertCount);
				ZoneBuffer::clear_pointer(&dest->tensionAccumTable);
			}

			if (data->blendShapes)
			{
				dest->blendShapes = nullptr;
				dest->blendShapesCount = 0;
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

		void IXSurface::dump(XModelSurfs* asset)
		{
			AssetDumper dump;
			dump.open("XSurface\\"s + asset->name + ".xsurface_export");

			if (asset->name == "tntbomb_mp_low10"s)
			{
				return;
			}

			dump.dump_array(asset, 1);
			dump.dump_string(asset->name);

			for (auto i = 0u; i < asset->numsurfs; i++)
			{
				dump.dump_int(asset->surfs[i].tileMode);
				dump.dump_int(asset->surfs[i].deformed);
				dump.dump_int(asset->surfs[i].baseTriIndex);
				dump.dump_int(asset->surfs[i].baseVertIndex);

				for (auto j = 0; j < 6; j++)
				{
					dump.dump_int(asset->surfs[i].partBits[j]);
				}

				// vertex bs
				dump.dump_array(&asset->surfs[i].vertexInfo, 1);
				dump.dump_array(asset->surfs[i].vertexInfo.vertsBlend,
				           asset->surfs[i].vertexInfo.vertCount[0] +
				           (asset->surfs[i].vertexInfo.vertCount[1] * 3) +
				           (asset->surfs[i].vertexInfo.vertCount[2] * 5) +
				           (asset->surfs[i].vertexInfo.vertCount[3] * 7)
				);

				dump.dump_int(asset->surfs[i].vertCount);
				dump.dump_array(asset->surfs[i].verticies, asset->surfs[i].vertCount);

				dump.dump_int(asset->surfs[i].triCount);
				dump.dump_array(asset->surfs[i].triIndices, asset->surfs[i].triCount);

				dump.dump_int(asset->surfs[i].vertListCount);
				dump.dump_array(asset->surfs[i].rigidVertLists, asset->surfs[i].vertListCount);
				for (auto vert = 0; vert < asset->surfs[i].vertListCount; vert++)
				{
					if (asset->surfs[i].rigidVertLists[vert].collisionTree)
					{
						dump.dump_array(asset->surfs[i].rigidVertLists[vert].collisionTree, 1);

						if (asset->surfs[i].rigidVertLists[vert].collisionTree->leafs)
						{
							dump.dump_array(asset->surfs[i].rigidVertLists[vert].collisionTree->leafs,
							           asset->surfs[i].rigidVertLists[vert].collisionTree->leafCount);
						}

						if (asset->surfs[i].rigidVertLists[vert].collisionTree->nodes)
						{
							dump.dump_array(asset->surfs[i].rigidVertLists[vert].collisionTree->nodes,
							           asset->surfs[i].rigidVertLists[vert].collisionTree->nodeCount);
						}
					}
				}
			}

			dump.close();
		}
	}
}
