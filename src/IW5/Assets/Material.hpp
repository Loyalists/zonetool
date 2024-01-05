#pragma once

namespace ZoneTool
{
	namespace H1
	{
		extern std::unordered_map<std::string, std::string> mapped_techsets;
	}

	namespace IW6
	{
		extern std::unordered_map<std::string, std::string> mapped_techsets;
	}

	namespace IW5
	{
		class IMaterial
		{
		public:
			static void dump(Material* asset, ZoneMemory* mem);
		};
	}
}