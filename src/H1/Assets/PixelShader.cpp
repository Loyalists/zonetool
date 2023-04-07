#include "stdafx.hpp"

namespace ZoneTool::H1
{
	void IPixelShader::dump(MaterialPixelShader* asset)
	{
		const auto path = "techsets\\"s + asset->name + ".pixelshader"s;

		assetmanager::dumper write;
		if (!write.open(path))
		{
			return;
		}

		write.dump_single(asset);
		write.dump_string(asset->name);
		write.dump_array(asset->prog.loadDef.program, asset->prog.loadDef.programSize);
		write.close();
	}
}