#include "stdafx.hpp"
#include "H1/Assets/RawFile.hpp"
#include "IW5/Structs.hpp"

#include "IW5/Assets/RawFile.hpp"

namespace ZoneTool
{
	namespace IW4
	{
		void IRawFile::dump(RawFile* asset, ZoneMemory* mem)
		{
			// dump rawfile
			IW5::IRawFile::dump(reinterpret_cast<IW5::RawFile*>(asset), mem);
		}
	}
}