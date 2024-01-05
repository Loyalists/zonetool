#pragma once

namespace ZoneTool::H1
{
	class IXModel
	{
	public:
		static void dump(XModel* asset, const std::function<const char* (std::uint16_t)>& SL_ConvertToString);
	};
}