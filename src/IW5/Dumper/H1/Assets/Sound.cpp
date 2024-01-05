#include "stdafx.hpp"

#include "Sound.hpp"
#include "Converter/H1/Assets/Sound.hpp"
#include "H1/Assets/Sound.hpp"

namespace ZoneTool::IW5::H1Dumper
{
	void dump(snd_alias_list_t* asset, ZoneMemory* mem, const std::function<std::string(const char* filename)>& get_streamed_sound_data)
	{
		// generate h1 asset
		auto* h1_asset = H1Converter::convert(asset, mem, get_streamed_sound_data);

		// dump sound
		H1::ISound::dump(h1_asset);
	}
}