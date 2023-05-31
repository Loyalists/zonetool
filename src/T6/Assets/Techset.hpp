// ======================= ZoneTool =======================
// zonetool, a fastfile linker for various
// Call of Duty titles. 
//
// Project: https://github.com/ZoneTool/zonetool
// Author: RektInator (https://github.com/RektInator)
// License: GNU GPL v3.0
// ========================================================
#pragma once

namespace ZoneTool
{
	namespace T6
	{
		extern std::unordered_map<int, int> mapped_techniques;

		class ITechset : public IAsset
		{
		public:
			static void dump(MaterialTechniqueSet* asset);
		};
	}
}
