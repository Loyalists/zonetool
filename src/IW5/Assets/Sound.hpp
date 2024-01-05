#pragma once

namespace ZoneTool::IW5
{
	extern std::string filesystem_read_big_file(const char* filename);

	class ISound
	{
	public:
		static void dump(snd_alias_list_t* asset, ZoneMemory* mem, const std::function<std::string(const char* filename)>& get_streamed_sound_data = filesystem_read_big_file);
	};
}