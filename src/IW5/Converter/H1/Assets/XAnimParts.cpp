#include "stdafx.hpp"
#include "../Include.hpp"

#include "XAnimParts.hpp"

namespace ZoneTool::IW5
{
	namespace H1Converter
	{
		H1::XAnimParts* GenerateH1XAnimParts(XAnimParts* asset, ZoneMemory* mem)
		{
			// allocate H1 XAnimParts structure
			const auto h1_asset = mem->Alloc<H1::XAnimParts>();

			h1_asset->name = asset->name;
			h1_asset->dataByteCount = asset->dataByteCount;
			h1_asset->dataShortCount = asset->dataShortCount;
			h1_asset->dataIntCount = asset->dataIntCount;
			h1_asset->randomDataByteCount = asset->randomDataByteCount;
			h1_asset->randomDataIntCount = asset->randomDataIntCount;
			h1_asset->numframes = asset->numframes;
			h1_asset->flags = asset->flags;
			memcpy(&h1_asset->boneCount, &asset->boneCount, sizeof(asset->boneCount));
			h1_asset->notifyCount = asset->notifyCount;
			h1_asset->assetType = asset->assetType;
			//h1_asset->ikType = asset->ikType;
			h1_asset->randomDataShortCount = asset->randomDataShortCount;
			h1_asset->indexCount = asset->indexCount;
			h1_asset->framerate = asset->framerate;
			h1_asset->frequency = asset->frequency;
			h1_asset->names = mem->Alloc<H1::scr_string_t>(h1_asset->boneCount[9]);
			for (auto i = 0; i < h1_asset->boneCount[9]; i++)
			{
				h1_asset->names[i] = static_cast<H1::scr_string_t>(asset->names[i]);
			}
			h1_asset->dataByte = reinterpret_cast<char* __ptr64>(asset->dataByte);
			h1_asset->dataShort = reinterpret_cast<short* __ptr64>(asset->dataShort);
			h1_asset->dataInt = reinterpret_cast<int* __ptr64>(asset->dataInt);
			h1_asset->randomDataShort = reinterpret_cast<short* __ptr64>(asset->randomDataShort);
			h1_asset->randomDataByte = reinterpret_cast<unsigned char* __ptr64>(asset->randomDataByte);
			h1_asset->randomDataInt = reinterpret_cast<int* __ptr64>(asset->randomDataInt);

			h1_asset->indices.data = reinterpret_cast<void*>(asset->indices.data);

			h1_asset->notify = mem->Alloc<H1::XAnimNotifyInfo>(h1_asset->notifyCount);
			for (auto i = 0; i < asset->notifyCount; i++)
			{
				h1_asset->notify[i].name = static_cast<H1::scr_string_t>(asset->notify[i].name);
				h1_asset->notify[i].time = asset->notify[i].time;
			}

			if (asset->deltaPart)
			{
				h1_asset->deltaPart = mem->Alloc<H1::XAnimDeltaPart>();
				if (asset->deltaPart->trans)
				{
					auto extra_size = 0;

					if (asset->deltaPart->trans->size)
					{
						if (asset->numframes >= 256)
						{
							extra_size += (asset->deltaPart->trans->size * 2) + 2;
						}
						else
						{
							extra_size += asset->deltaPart->trans->size + 1;
						}
					}

					h1_asset->deltaPart->trans = mem->ManualAlloc<H1::XAnimPartTrans>(sizeof(H1::XAnimPartTrans) + extra_size);

					h1_asset->deltaPart->trans->size = asset->deltaPart->trans->size;
					h1_asset->deltaPart->trans->smallTrans = static_cast<unsigned short>(asset->deltaPart->trans->smallTrans);

					if (asset->deltaPart->trans->size)
					{
						for (auto i = 0; i < 3; i++)
						{
							h1_asset->deltaPart->trans->u.frames.mins[i] = asset->deltaPart->trans->u.frames.mins[i];
							h1_asset->deltaPart->trans->u.frames.size[i] = asset->deltaPart->trans->u.frames.size[i];
						}
						if (asset->numframes >= 256)
						{
							for (auto i = 0; i < asset->deltaPart->trans->size + 1; i++)
							{
								h1_asset->deltaPart->trans->u.frames.indices._2[i] = asset->deltaPart->trans->u.frames.indices._2[i];
							}
						}
						else
						{
							for (auto i = 0; i < asset->deltaPart->trans->size + 1; i++)
							{
								h1_asset->deltaPart->trans->u.frames.indices._1[i] = static_cast<unsigned char>(asset->deltaPart->trans->u.frames.indices._1[i]);
							}
						}
						if (asset->deltaPart->trans->u.frames.frames._1)
						{
							if (asset->deltaPart->trans->smallTrans)
							{
								h1_asset->deltaPart->trans->u.frames.frames._1 = mem->Alloc<unsigned char[3]>(asset->deltaPart->trans->size + 1);
								for (auto i = 0; i < asset->deltaPart->trans->size + 1; i++)
								{
									h1_asset->deltaPart->trans->u.frames.frames._1[i][0] = static_cast<unsigned char>(asset->deltaPart->trans->u.frames.frames._1[i][0]);
									h1_asset->deltaPart->trans->u.frames.frames._1[i][1] = static_cast<unsigned char>(asset->deltaPart->trans->u.frames.frames._1[i][1]);
									h1_asset->deltaPart->trans->u.frames.frames._1[i][2] = static_cast<unsigned char>(asset->deltaPart->trans->u.frames.frames._1[i][2]);
								}
							}
							else
							{
								h1_asset->deltaPart->trans->u.frames.frames._2 = mem->Alloc<unsigned short[3]>(asset->deltaPart->trans->size + 1);
								for (auto i = 0; i < asset->deltaPart->trans->size + 1; i++)
								{
									h1_asset->deltaPart->trans->u.frames.frames._2[i][0] = asset->deltaPart->trans->u.frames.frames._2[i][0];
									h1_asset->deltaPart->trans->u.frames.frames._2[i][1] = asset->deltaPart->trans->u.frames.frames._2[i][1];
									h1_asset->deltaPart->trans->u.frames.frames._2[i][2] = asset->deltaPart->trans->u.frames.frames._2[i][2];
								}
							}
						}
					}
					else
					{
						for (auto i = 0; i < 3; i++)
						{
							h1_asset->deltaPart->trans->u.frame0[i] = asset->deltaPart->trans->u.frame0[i];
						}
					}
				}

				if (asset->deltaPart->quat)
				{
					auto extra_size = 0;

					if (asset->deltaPart->quat->size)
					{
						if (asset->numframes >= 256)
						{
							extra_size += (asset->deltaPart->quat->size * 2) + 2;
						}
						else
						{
							extra_size += asset->deltaPart->quat->size + 1;
						}
					}
					else
					{
						// quat data contains 4 extra bytes
						extra_size += 4;
					}

					h1_asset->deltaPart->quat = mem->ManualAlloc<H1::XAnimDeltaPartQuat>(sizeof(H1::XAnimDeltaPartQuat) + extra_size);
					h1_asset->deltaPart->quat->size = asset->deltaPart->quat->size;

					if (asset->deltaPart->quat->size)
					{
						if (asset->numframes >= 256)
						{
							for (auto i = 0; i < asset->deltaPart->quat->size + 1; i++)
							{
								h1_asset->deltaPart->quat->u.frames.indices._2[i] = asset->deltaPart->quat->u.frames.indices._2[i];
							}
						}
						else
						{
							for (auto i = 0; i < asset->deltaPart->quat->size + 1; i++)
							{
								h1_asset->deltaPart->quat->u.frames.indices._1[i] = static_cast<unsigned char>(asset->deltaPart->quat->u.frames.indices._1[i]);
							}
						}
						if (asset->deltaPart->quat->u.frames.frames)
						{
							h1_asset->deltaPart->quat->u.frames.frames = mem->Alloc<short[4]>(asset->deltaPart->quat->size + 1);
							for (auto i = 0; i < asset->deltaPart->quat->size + 1; i++)
							{
								h1_asset->deltaPart->quat->u.frames.frames[i][0] = asset->deltaPart->quat->u.frames.frames[i][0];
								h1_asset->deltaPart->quat->u.frames.frames[i][1] = asset->deltaPart->quat->u.frames.frames[i][1];
							}
						}
					}
					else
					{
						for (auto i = 0; i < 2; i++)
						{
							h1_asset->deltaPart->quat->u.frame0[i] = asset->deltaPart->quat->u.frame0[i];
						}
					}
				}
			}

			return h1_asset;
		}

		H1::XAnimParts* convert(XAnimParts* asset, ZoneMemory* mem)
		{
			// generate h1 anims
			return GenerateH1XAnimParts(asset, mem);
		}
	}
}