#include "stdafx.hpp"

namespace ZoneTool::IW6
{
	void IComWorld::dump(ComWorld* asset)
	{
		const auto path = asset->name + ".commap"s;

		assetmanager::dumper write;
		if (!write.open(path))
		{
			return;
		}

		write.dump_single(asset);
		write.dump_string(asset->name);

		write.dump_array(asset->primaryLights, asset->primaryLightCount);
		for (unsigned int i = 0; i < asset->primaryLightCount; i++)
		{
			write.dump_string(asset->primaryLights[i].defName);
		}
		write.dump_array(asset->primaryLightEnvs, asset->primaryLightEnvCount);

		write.close();
	}
}