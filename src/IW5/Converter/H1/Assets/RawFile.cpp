#include "stdafx.hpp"
#include "../Include.hpp"

#include "RawFile.hpp"

namespace ZoneTool::IW5
{
	namespace H1Converter
	{
		H1::RawFile* GenerateH1RawFile(RawFile* asset, ZoneMemory* mem)
		{
			auto* h1_asset = mem->Alloc<H1::RawFile>();
			h1_asset->name = asset->name;
			h1_asset->compressedLen = asset->compressedLen;
			h1_asset->len = asset->len;
			h1_asset->buffer = asset->buffer;
			return h1_asset;
		}

		H1::RawFile* convert(RawFile* asset, ZoneMemory* mem)
		{
			// generate h1 rawfile
			return GenerateH1RawFile(asset, mem);
		}
	}
}