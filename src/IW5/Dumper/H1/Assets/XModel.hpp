#pragma once

namespace ZoneTool::IW5
{
	namespace H1Dumper
	{
		void dump(XModel* asset, ZoneMemory* mem, const std::function<const char* (uint16_t)>& convertToString);
	}
}