#pragma once

namespace ZoneTool::IW6
{
	class IXAnimParts
	{
	public:
		static void dump(XAnimParts* asset, const std::function<const char* (std::uint16_t)>& SL_ConvertToString);
	};
}