#include "stdafx.hpp"

namespace ZoneTool::H1
{
	void IGfxLightDef::dump(GfxLightDef* asset)
	{
		const auto path = "lights\\"s + asset->name + ".json"s;
		auto file = filesystem::file(path);
		file.open("wb");

		ordered_json data;

		data["name"] = asset->name;

		data["attenuation"] = {};
		data["attenuation"]["image"] = asset->attenuation.image ? asset->attenuation.image->name : "";
		data["attenuation"]["samplerState"] = asset->attenuation.samplerState;

		data["cucoloris"] = {};
		data["cucoloris"]["image"] = asset->cucoloris.image ? asset->cucoloris.image->name : "";
		data["cucoloris"]["samplerState"] = asset->cucoloris.samplerState;

		data["lmapLookupStart"] = asset->lmapLookupStart;

		const auto json = data.dump(4);

		file.write(json.data(), json.size(), 1);

		file.close();
	}
}