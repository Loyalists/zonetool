// ======================= ZoneTool =======================
// zonetool, a fastfile linker for various
// Call of Duty titles. 
//
// Project: https://github.com/ZoneTool/zonetool
// Author: RektInator (https://github.com/RektInator)
// License: GNU GPL v3.0
// ========================================================
#include "stdafx.hpp"

namespace ZoneTool
{
	namespace T6
	{
		//void ILocalizeEntry::init(const std::string& name, ZoneMemory* mem)
		//{
		//	this->name_ = name;
		//	this->asset_ = DB_FindXAssetHeader(this->type(), this->name().data(), 1).localize;
		//}

		//void ILocalizeEntry::prepare(ZoneBuffer* buf, ZoneMemory* mem)
		//{
		//}

		//void ILocalizeEntry::load_depending(IZone* zone)
		//{
		//}

		//std::string ILocalizeEntry::name()
		//{
		//	return this->name_;
		//}

		//std::int32_t ILocalizeEntry::type()
		//{
		//	return localize_entry;
		//}

		//void ILocalizeEntry::write(IZone* zone, ZoneBuffer* buf)
		//{
		//	auto data = this->asset_;
		//	auto dest = buf->write(data);

		//	sizeof LocalizeEntry;

		//	buf->push_stream(3);
		//	START_LOG_STREAM;

		//	dest->localizedString = buf->write_str(data->localizedString);
		//	dest->name = buf->write_str(this->name());

		//	END_LOG_STREAM;
		//	buf->pop_stream();
		//}

		void ILocalizeEntry::dump(LocalizeEntry* asset)
		{
			localize_entries_buffer[asset->name] = asset->value;
		}

		void ILocalizeEntry::finish_dump()
		{
			if (localize_entries_buffer.empty() || localize_entries_buffer.is_null())
			{
				return;
			}
			std::string path = "localizations.json"s;
			std::string jsonString = localize_entries_buffer.dump(4);
			auto file = FileSystem::FileOpen(path, "wb"s);
			fwrite(jsonString.data(), jsonString.size(), 1, file);
			FileSystem::FileClose(file);
			localize_entries_buffer = { {} };
		}
	}
}
