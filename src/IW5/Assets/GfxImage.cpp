#include "stdafx.hpp"

#include "Dumper/H1/Assets/GfxImage.hpp"
#include "Dumper/IW6/Assets/GfxImage.hpp"

namespace ZoneTool::IW5
{
	void IGfxImage::dump(GfxImage* asset, ZoneMemory* mem)
	{
		if (zonetool::dumping_target == zonetool::dump_target::h1)
		{
			return H1Dumper::dump(asset, mem);
		}
		else if (zonetool::dumping_target == zonetool::dump_target::iw6)
		{
			return IW6Dumper::dump(asset, mem);
		}
	}
}