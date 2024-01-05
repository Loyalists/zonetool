#include "stdafx.hpp"

#include "XSurface.hpp"
#include "Converter/H1/Assets/XSurface.hpp"
#include "H1/Assets/XSurface.hpp"

namespace ZoneTool::IW5::H1Dumper
{
	void dump(XModelSurfs* asset, ZoneMemory* mem)
	{
		// generate h1 surfaces
		auto h1_asset = H1Converter::convert(asset, mem);

		// dump h1 surfaces
		H1::IXSurface::dump(h1_asset);
	}
}