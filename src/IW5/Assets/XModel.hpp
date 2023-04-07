#pragma once

namespace ZoneTool
{
	namespace IW5
	{
		static const char* SL_ConvertToString(std::uint16_t index);

		class IXModel
		{
		public:
			static void dump(XModel* asset, ZoneMemory* mem, const std::function<const char* (uint16_t)>& convertToString = SL_ConvertToString);
		};
	}
}