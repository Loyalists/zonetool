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
		class IAddonMapEnts : public IAsset
		{
		private:
			//std::string name_;
			//MapEnts* asset_ = nullptr;

		public:
			//MapEnts* parse(std::string name, ZoneMemory* mem);
			//
			//void init(const std::string& name, ZoneMemory* mem) override;
			//void prepare(ZoneBuffer* buf, ZoneMemory* mem) override;
			//void load_depending(IZone* zone) override;
			//static void load_depending_internal(IZone* zone, const char* entityString);

			//std::string name() override;
			//std::int32_t type() override;
			//void write(IZone* zone, ZoneBuffer* buffer) override;

			static void dump(AddonMapEnts* asset);

			// sadly, this cannot be moved to a CPP file.
			//static void write_triggers(IZone* zone, ZoneBuffer* buf, MapTriggers* dest);
		};
	}
}
