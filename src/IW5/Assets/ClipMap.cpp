#include "stdafx.hpp"

#include "Dumper/H1/Assets/ClipMap.hpp"
#include "Dumper/IW6/Assets/ClipMap.hpp"

namespace ZoneTool::IW5
{
	void IClipMap::dump(clipMap_t* asset, ZoneMemory* mem)
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