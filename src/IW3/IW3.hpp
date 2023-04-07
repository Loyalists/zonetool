// ======================= ZoneTool =======================
// zonetool, a fastfile linker for various
// Call of Duty titles. 
//
// Project: https://github.com/ZoneTool/zonetool
// Author: RektInator (https://github.com/RektInator)
// License: GNU GPL v3.0
// ========================================================
#pragma once

#include <ZoneUtils.hpp>
#include "Functions.hpp"
#include "Structs.hpp"

#include "H1/Utils/IO/filesystem.hpp"
#include "H1/Utils/IO/assetmanager.hpp"
#include "H1/Structs.hpp"

using namespace zonetool;

#include "Json.hpp"
using json = nlohmann::json;
using ordered_json = nlohmann::ordered_json;

namespace bounds
{
	static auto compute(float* mins, float* maxs)
	{
		float bounds[2][3]{ 0 };
		for (int i = 0; i < 3; ++i)
		{
			bounds[1][i] = (maxs[i] - mins[i]) / 2;
			bounds[0][i] = bounds[1][i] + mins[i];
		}
		return bounds;
	}
}

#include "Assets/ClipMap.hpp"
#include "Assets/ComWorld.hpp"
#include "Assets/FxEffectDef.hpp"
#include "Assets/GameWorldMp.hpp"
#include "Assets/GfxImage.hpp"
#include "Assets/GfxLightDef.hpp"
#include "Assets/GfxWorld.hpp"
#include "Assets/LoadedSound.hpp"
#include "Assets/MapEnts.hpp"
#include "Assets/Material.hpp"
#include "Assets/RawFile.hpp"
#include "Assets/Sound.hpp"
#include "Assets/SoundCurve.hpp"
#include "Assets/XAnimParts.hpp"
#include "Assets/XModel.hpp"

// oh nee toch niet

namespace ZoneTool
{
	namespace IW3
	{
		struct XAsset
		{
			XAssetType type;
			XAssetHeader ptr;
		};

		class Linker : public ILinker
		{
		public:
			Linker();
			~Linker();

			const char* version() override;
			bool is_used() override;
			void startup() override;
			std::shared_ptr<IZone> alloc_zone(const std::string& zone) override;
			std::shared_ptr<ZoneBuffer> alloc_buffer() override;
			void load_zone(const std::string& name) override;
			void unload_zones() override;
			bool is_valid_asset_type(const std::string& type) override;
			std::int32_t type_to_int(std::string type) override;
			std::string type_to_string(std::int32_t type) override;
            bool supports_building() override;
			bool supports_version(const zone_target_version version) override;

			void dump_zone(const std::string& name) override;
			void verify_zone(const std::string& name) override;

			static void* Dedicated_RegisterDvarBool(const char* name, bool defaultValue, unsigned int flags,
			                                        const char* description);
			static void* DB_AddXAsset(XAsset* asset, int unk);
			static const char* GetAssetName(XAsset* asset);
			static void HandleAsset(XAsset* asset);
		};
	}
}
