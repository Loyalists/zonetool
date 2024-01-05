#include "stdafx.hpp"

#include <zlib.h>

namespace ZoneTool::H1
{
	void IRawFile::dump(RawFile* asset)
	{
		auto file = filesystem::file(asset->name);
		file.open("wb");

		if (asset->compressedLen > 0)
		{
			std::vector<std::uint8_t> uncompressed;
			uncompressed.resize(asset->len);

			uncompress(uncompressed.data(), (uLongf*)&asset->len, (Bytef*)asset->buffer, asset->compressedLen);

			file.write(uncompressed.data(), uncompressed.size(), 1);
		}
		else if (asset->len > 0)
		{
			file.write(asset->buffer, asset->len, 1);
		}

		file.close();
	}
}