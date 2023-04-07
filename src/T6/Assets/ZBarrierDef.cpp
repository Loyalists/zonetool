#include "stdafx.hpp"

namespace ZoneTool
{
	namespace T6
	{
#define ZBARRIER_DUMP_FIELD(__field__) \
	data[#__field__] = asset->__field__

#define ZBARRIER_DUMP_ASSET(__field__) \
	if (asset->__field__) \
	{ \
		data[#__field__] = asset->__field__->name; \
	} \
	else \
	{ \
		data[#__field__] = ""; \
	}

#define ZBARRIER_DUMP_FIELD_ARR(__field__, __size__) \
	for (auto idx##__field__ = 0; idx##__field__ < __size__; idx##__field__++) \
	{ \
		data[#__field__][idx##__field__] = asset->__field__[idx##__field__]; \
	}

		Json IZBarrierDef::dumpboards(ZBarrierDef* asset)
		{
			Json data;
			for (int i = 0; i < 6; i++)
			{
				if (asset->boards[i].pBoardModel && asset->boards[i].pBoardModel->name)
				{
					data[i]["pBoardModel"] = asset->boards[i].pBoardModel->name;
				}
				else
				{
					data[i]["pBoardModel"] = "";
				}
				if (asset->boards[i].pAlternateBoardModel && asset->boards[i].pAlternateBoardModel->name)
				{
					data[i]["pAlternateBoardModel"] = asset->boards[i].pAlternateBoardModel->name;
				}
				else
				{
					data[i]["pAlternateBoardModel"] = "";
				}
				if (asset->boards[i].pUpgradedBoardModel && asset->boards[i].pUpgradedBoardModel->name)
				{
					data[i]["pUpgradedBoardModel"] = asset->boards[i].pUpgradedBoardModel->name;
				}
				else
				{
					data[i]["pTearAnim"] = "";
				}
				if (asset->boards[i].repairEffect1 && asset->boards[i].repairEffect1->name)
				{
					data[i]["repairEffect1"] = asset->boards[i].repairEffect1->name;
				}
				else
				{
					data[i]["repairEffect1"] = "";
				}
				if (asset->boards[i].repairEffect2 && asset->boards[i].repairEffect2->name)
				{
					data[i]["repairEffect2"] = asset->boards[i].repairEffect2->name;
				}
				else
				{
					data[i]["repairEffect2"] = "";
				}
				for (int j = 0; j < 3; j++)
				{
					data[i]["repairEffect1Offset"][j] = asset->boards[i].repairEffect1Offset[j];
					data[i]["repairEffect1Offset"][j] = asset->boards[i].repairEffect2Offset[j];
				}
				if (asset->boards[i].pTearAnim)
				{
					data[i]["pTearAnim"] = asset->boards[i].pTearAnim;
				}
				else
				{
					data[i]["pTearAnim"] = "";
				}
				if (asset->boards[i].pBoardAnim)
				{
					data[i]["pBoardAnim"] = asset->boards[i].pBoardAnim;
				}
				else
				{
					data[i]["pBoardAnim"] = "";
				}
				data[i]["boardRepairSound"] = asset->boards[i].boardRepairSound;
				data[i]["boardRepairHoverSound"] = asset->boards[i].boardRepairHoverSound;
				data[i]["pauseAndRepeatRepSound"] = asset->boards[i].pauseAndRepeatRepSound;
				data[i]["minPause"] = asset->boards[i].minPause;
				data[i]["maxPause"] = asset->boards[i].maxPause;
				data[i]["zombieBoardTearStateName"] = asset->boards[i].zombieBoardTearStateName;
				data[i]["zombieBoardTearSubStateName"] = asset->boards[i].zombieBoardTearSubStateName;
				data[i]["numRepsToPullProBoard"] = asset->boards[i].numRepsToPullProBoard;
			}
			return data;
		}

		void IZBarrierDef::dump(ZBarrierDef* asset)
		{
			Json data;
			data["name"] = asset->name;
			ZBARRIER_DUMP_FIELD(generalRepairSound1);
			ZBARRIER_DUMP_FIELD(generalRepairSound2);
			ZBARRIER_DUMP_FIELD(upgradedGeneralRepairSound1);
			ZBARRIER_DUMP_FIELD(upgradedGeneralRepairSound2);
			ZBARRIER_DUMP_FIELD(delayBetweenRepSounds);
			ZBARRIER_DUMP_FIELD(delayBetweenRepSoundsDuration);
			ZBARRIER_DUMP_FIELD(earthquakeOnRepair);
			ZBARRIER_DUMP_FIELD(earthquakeMinScale);
			ZBARRIER_DUMP_FIELD(earthquakeMaxScale);
			ZBARRIER_DUMP_FIELD(earthquakeMinDuration);
			ZBARRIER_DUMP_FIELD(earthquakeMaxDuration);
			ZBARRIER_DUMP_FIELD(earthquakeRadius);
			ZBARRIER_DUMP_FIELD(numBoardsInBarrier);
			ZBARRIER_DUMP_FIELD(autoHideOpenPieces);
			ZBARRIER_DUMP_FIELD(taunts);
			ZBARRIER_DUMP_FIELD(reachThroughAttacks);
			ZBARRIER_DUMP_FIELD(zombieTauntAnimState);
			ZBARRIER_DUMP_FIELD(zombieReachThroughAnimState);
			ZBARRIER_DUMP_FIELD(numAttackSlots);
			ZBARRIER_DUMP_FIELD(attackSpotHorzOffset);
			data["boards"] = dumpboards(asset);
			std::string json = data.dump(4);
			auto file = FileSystem::FileOpen("zbarriers\\"s + asset->name, "wb");
			fwrite(json.data(), json.size(), 1, file);
			FileSystem::FileClose(file);
		}
	}
}