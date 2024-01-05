#pragma once

namespace ZoneTool::IW6
{
	class IClipMap
	{
	private:
		static void dump_info(ClipInfo* info, assetmanager::dumper& write, const std::function<const char* (std::uint16_t)>& SL_ConvertToString);

	public:
		static void dump(clipMap_t* asset, const std::function<const char* (std::uint16_t)>& SL_ConvertToString);
	};
}