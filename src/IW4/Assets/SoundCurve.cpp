#include "stdafx.hpp"
#include "IW5/Structs.hpp"

#include "IW5/Assets/SoundCurve.hpp"

namespace ZoneTool
{
	namespace IW4
	{
		void ISoundCurve::dump(SndCurve* asset, ZoneMemory* mem)
		{
			// dump asset
			IW5::ISoundCurve::dump(reinterpret_cast<IW5::SndCurve*>(asset), mem);
		}
	}
}