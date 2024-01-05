#include "stdafx.hpp"
#include "IW5/Structs.hpp"

#include "IW5/Assets/XSurface.hpp"

namespace ZoneTool
{
	namespace IW4
	{
		void IXSurface::dump(XModelSurfs* asset, ZoneMemory* mem)
		{
			auto* iw5_asset = mem->Alloc<IW5::XModelSurfs>();
			std::memcpy(iw5_asset, asset, sizeof(IW5::XModelSurfs));

			iw5_asset->surfs = mem->Alloc<IW5::XSurface>(asset->numsurfs);
			for (unsigned short i = 0; i < asset->numsurfs; i++)
			{
				auto* surf = &asset->surfs[i];
				auto* iw5_surf = &iw5_asset->surfs[i];

				iw5_surf->tileMode = surf->tileMode;
				iw5_surf->flags = surf->deformed ? IW5::XSurfaceFlags::SURF_FLAG_SKINNED : 0;
				iw5_surf->vertCount = surf->vertCount;
				iw5_surf->triCount = surf->triCount;
				//iw5_surf->streamHandle = surf->streamHandle;
				iw5_surf->zoneHandle = surf->zoneHandle;
				iw5_surf->baseTriIndex = surf->baseTriIndex;
				iw5_surf->baseVertIndex = surf->baseVertIndex;
				iw5_surf->quantizeScale = 0;
				iw5_surf->triIndices = reinterpret_cast<unsigned short*>(surf->triIndices);
				std::memcpy(&iw5_surf->vertInfo, &surf->vertexInfo, sizeof(IW5::XSurfaceVertexInfo));
				iw5_surf->verts0.packedVerts0 = reinterpret_cast<IW5::GfxPackedVertex*>(surf->verticies);
				iw5_surf->vertListCount = surf->vertListCount;
				iw5_surf->vertList = reinterpret_cast<IW5::XRigidVertList*>(surf->rigidVertLists);
				std::memcpy(&iw5_surf->partBits, &surf->partBits, sizeof(int[6]));
			}

			// dump surfaces
			IW5::IXSurface::dump(iw5_asset, mem);
		}
	}
}