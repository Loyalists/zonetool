#include "stdafx.hpp"
#include "../Include.hpp"

#include "RawFile.hpp"

namespace ZoneTool::IW5
{
	namespace IW6Converter
	{
		IW6::RawFile* GenerateIW6RawFile(RawFile* asset, ZoneMemory* mem)
		{
			auto* iw6_asset = mem->Alloc<IW6::RawFile>();
			iw6_asset->name = asset->name;
			iw6_asset->compressedLen = asset->compressedLen;
			iw6_asset->len = asset->len;
			iw6_asset->buffer = asset->buffer;
			return iw6_asset;
		}

		IW6::RawFile* convert(RawFile* asset, ZoneMemory* mem)
		{
			// generate IW6 rawfile
			return GenerateIW6RawFile(asset, mem);
		}
	}
}