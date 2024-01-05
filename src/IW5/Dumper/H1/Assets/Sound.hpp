#pragma once

namespace ZoneTool::IW5
{
	namespace H1Dumper
	{
		void dump(snd_alias_list_t* asset, ZoneMemory* mem, const std::function<std::string(const char* filename)>& get_streamed_sound_data);
	}
}