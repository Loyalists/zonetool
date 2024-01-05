#include "stdafx.hpp"

#include "Dumper/LoadedSound.hpp"

namespace ZoneTool::IW5
{
	void ILoadedSound::dump(LoadedSound* asset, ZoneMemory* mem)
	{
		Dumper::dump(asset, mem);
	}
}