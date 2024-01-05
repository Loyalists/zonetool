#include "stdafx.hpp"

#include "GfxImage.hpp"
#include "Converter/IW6/Assets/GfxImage.hpp"
#include "IW6/Assets/GfxImage.hpp"

namespace ZoneTool::IW5::IW6Dumper
{
	void dump(GfxImage* asset, ZoneMemory* mem)
	{
		std::string name = asset->name;

		bool isMapImage = (name.size() >= 6)
			? ((name.substr(0, 6) == "*light" || name.substr(0, 6) == "*refle" ||
				name == "$outdoor")
				? true
				: false)
			: false;

		if (!isMapImage) return;

		if (!asset->texture.loadDef->resourceSize)
		{
			ZONETOOL_INFO("Not dumping image %s", asset->name);
			return;
		}

		// generate IW6 gfximage
		auto* iw6_asset = IW6Converter::convert(asset, mem);

		// dump IW6 gfximage
		IW6::IGfxImage::dump(iw6_asset);
	}
}