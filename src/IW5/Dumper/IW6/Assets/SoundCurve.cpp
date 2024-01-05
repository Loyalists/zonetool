#include "stdafx.hpp"

#include "SoundCurve.hpp"
#include "Converter/IW6/Assets/SoundCurve.hpp"
//#include "IW6/Assets/SoundCurve.hpp"

namespace ZoneTool::IW5::IW6Dumper
{
	void dump(SndCurve* asset, ZoneMemory* mem)
	{
		// generate IW6 asset
		auto* iw6_asset = IW6Converter::convert(asset, mem);

		// dump soundcurve
		//IW6::ISoundCurve::dump(iw6_asset);
	}
}