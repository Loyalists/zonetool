#include "stdafx.hpp"

#include "XSurface.hpp"
#include "Converter/IW6/Assets/XSurface.hpp"
#include "IW6/Assets/XSurface.hpp"

namespace ZoneTool::IW5::IW6Dumper
{
	void dump(XModelSurfs* asset, ZoneMemory* mem)
	{
		// generate IW6 surfaces
		auto iw6_asset = IW6Converter::convert(asset, mem);

		// dump IW6 surfaces
		IW6::IXSurface::dump(iw6_asset);
	}
}