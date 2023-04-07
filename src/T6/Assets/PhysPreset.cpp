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
#define PHYSPRESET_DUMP_FIELD(__field__) \
	data[#__field__] = asset->__field__

#define PHYSPRESET_DUMP_FIELD_ARR(__field__, __size__) \
	for (auto idx##__field__ = 0; idx##__field__ < __size__; idx##__field__++) \
	{ \
		data[#__field__][idx##__field__] = asset->__field__[idx##__field__]; \
	}

		//void IPhysPreset::init(const std::string& name, ZoneMemory* mem)
		//{
		//	this->name_ = name;
		//	this->asset_ = DB_FindXAssetHeader(this->type(), this->name().data(), 1).physpreset;
		//}

		//void IPhysPreset::prepare(ZoneBuffer* buf, ZoneMemory* mem)
		//{
		//}

		//void IPhysPreset::load_depending(IZone* zone)
		//{
		//}

		//std::string IPhysPreset::name()
		//{
		//	return this->name_;
		//}

		//std::int32_t IPhysPreset::type()
		//{
		//	return physpreset;
		//}

		//void IPhysPreset::write(IZone* zone, ZoneBuffer* buf)
		//{
		//	auto data = this->asset_;
		//	auto dest = buf->write(data);

		//	buf->push_stream(3);

		//	dest->name = buf->write_str(this->name());

		//	if (data->sndAliasPrefix)
		//	{
		//		dest->sndAliasPrefix = buf->write_str(data->sndAliasPrefix);
		//	}

		//	buf->pop_stream();
		//}

		void IPhysPreset::dump(PhysPreset* asset)
		{
			Json data;
			data["name"] = asset->name;
			PHYSPRESET_DUMP_FIELD(flags);
			PHYSPRESET_DUMP_FIELD(mass);
			PHYSPRESET_DUMP_FIELD(bounce);
			PHYSPRESET_DUMP_FIELD(friction);
			PHYSPRESET_DUMP_FIELD(bulletForceScale);
			PHYSPRESET_DUMP_FIELD(explosiveForceScale);
			if (asset->sndAliasPrefix)
			{
				data["sndAliasPrefix"] = asset->sndAliasPrefix;
			}
			else
			{
				data["sndAliasPrefix"] = "";
			}
			PHYSPRESET_DUMP_FIELD(piecesSpreadFraction);
			PHYSPRESET_DUMP_FIELD(piecesUpwardVelocity);
			PHYSPRESET_DUMP_FIELD(canFloat);
			PHYSPRESET_DUMP_FIELD(gravityScale);
			PHYSPRESET_DUMP_FIELD_ARR(centerOfMassOffset, 3);
			PHYSPRESET_DUMP_FIELD_ARR(buoyancyBoxMin, 3);
			PHYSPRESET_DUMP_FIELD_ARR(buoyancyBoxMax, 3);
			std::string json = data.dump(4);
			auto file = FileSystem::FileOpen("physpresets\\"s + asset->name, "wb");
			fwrite(json.data(), json.size(), 1, file);
			FileSystem::FileClose(file);
		}
	}
}
