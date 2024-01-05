#include "stdafx.hpp"

#include "Dumper/H1/Assets/ComWorld.hpp"
#include "Dumper/IW6/Assets/ComWorld.hpp"

namespace ZoneTool::IW5
{
	void IComWorld::dump(ComWorld* asset, ZoneMemory* mem)
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