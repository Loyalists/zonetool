#pragma once

namespace ZoneTool::IW5
{
	namespace IW6Converter
	{
		IW6::snd_alias_list_t* convert(snd_alias_list_t* asset, ZoneMemory* mem, const std::function<std::string(const char* filename)>& get_streamed_sound_data);
	}
}