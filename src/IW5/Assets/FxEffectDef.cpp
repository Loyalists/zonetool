#include "stdafx.hpp"

#include "Dumper/H1/Assets/FxEffectDef.hpp"
#include "Dumper/IW6/Assets/FxEffectDef.hpp"

namespace ZoneTool::IW5
{
	void IFxEffectDef::dump(FxEffectDef* asset, ZoneMemory* mem)
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