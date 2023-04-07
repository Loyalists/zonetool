#include "stdafx.hpp"
#include "H1/Assets/PhysPreset.hpp"
#include "IW5/Structs.hpp"

#include "IW5/Assets/PhysPreset.hpp"

namespace ZoneTool
{
	namespace IW4
	{
		void IPhysPreset::dump(PhysPreset* asset, ZoneMemory* mem)
		{
			// dump asset
			IW5::IPhysPreset::dump(reinterpret_cast<IW5::PhysPreset*>(asset), mem);
		}
	}
}