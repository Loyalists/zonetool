#include "stdafx.hpp"

#include "SoundCurve.hpp"
#include "Converter/H1/Assets/SoundCurve.hpp"
#include "H1/Assets/SoundCurve.hpp"

namespace ZoneTool::IW5::H1Dumper
{
	void dump(SndCurve* asset, ZoneMemory* mem)
	{
		// generate h1 asset
		auto* h1_asset = H1Converter::convert(asset, mem);

		// dump soundcurve
		H1::ISoundCurve::dump(h1_asset);
	}
}