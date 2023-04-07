#include "stdafx.hpp"
#include "H1/Assets/XAnimParts.hpp"
#include "IW5/Structs.hpp"

#include "IW5/Assets/XAnimParts.hpp"

namespace ZoneTool
{
	namespace IW4
	{
		void IXAnimParts::dump(XAnimParts* asset, ZoneMemory* mem)
		{
			// dump anims
			IW5::IXAnimParts::dump(reinterpret_cast<IW5::XAnimParts*>(asset), mem, SL_ConvertToString);
		}
	}
}