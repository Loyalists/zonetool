#include "stdafx.hpp"

namespace ZoneTool::IW6
{
	void IFxWorld::dump(FxWorld* asset)
	{
		const auto path = asset->name + ".fxmap"s;

		assetmanager::dumper write;
		if (!write.open(path))
		{
			return;
		}

		write.dump_single(asset);
		write.dump_string(asset->name);

		write.dump_array(asset->glassSys.defs, asset->glassSys.defCount);
		for (unsigned int i = 0; i < asset->glassSys.defCount; i++)
		{
			write.dump_asset(asset->glassSys.defs[i].material);
			write.dump_asset(asset->glassSys.defs[i].materialShattered);

			write.dump_asset(asset->glassSys.defs[i].physPreset);

			write.dump_asset(asset->glassSys.defs[i].pieceBreakEffect);
			write.dump_asset(asset->glassSys.defs[i].shatterEffect);
			write.dump_asset(asset->glassSys.defs[i].shatterSmallEffect);
			write.dump_asset(asset->glassSys.defs[i].crackDecalEffect);

			write.dump_asset(asset->glassSys.defs[i].damagedSound);
			write.dump_asset(asset->glassSys.defs[i].destroyedSound);
			write.dump_asset(asset->glassSys.defs[i].destroyedQuietSound);
		}

		write.dump_array(asset->glassSys.piecePlaces, asset->glassSys.pieceLimit);

		write.dump_array(asset->glassSys.pieceStates, asset->glassSys.pieceLimit);

		write.dump_array(asset->glassSys.pieceDynamics, asset->glassSys.pieceLimit);

		write.dump_array(asset->glassSys.geoData, asset->glassSys.geoDataLimit);

		write.dump_array(asset->glassSys.isInUse, asset->glassSys.pieceWordCount);

		write.dump_array(asset->glassSys.cellBits, asset->glassSys.pieceWordCount * asset->glassSys.cellCount);

		write.dump_array(asset->glassSys.visData, (asset->glassSys.pieceLimit + 15) & 0xFFFFFFF0);

		write.dump_array(asset->glassSys.linkOrg, asset->glassSys.pieceLimit);

		write.dump_array(asset->glassSys.halfThickness, (asset->glassSys.pieceLimit + 3) & 0xFFFFFFFC);

		write.dump_array(asset->glassSys.lightingHandles, asset->glassSys.initPieceCount);

		write.dump_array(asset->glassSys.initPieceStates, asset->glassSys.initPieceCount);

		write.dump_array(asset->glassSys.initGeoData, asset->glassSys.initGeoDataCount);

		write.close();
	}
}