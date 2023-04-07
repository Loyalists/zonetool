// ======================= ZoneTool =======================
// zonetool, a fastfile linker for various
// Call of Duty titles. 
//
// Project: https://github.com/ZoneTool/zonetool
// Author: RektInator (https://github.com/RektInator)
// License: GNU GPL v3.0
// ========================================================
#pragma once

#define SELECT(mp, zm) (strcmp(reinterpret_cast<char*>(0xBC8D34), "COD_T6_S MP") ? mp : zm)

#include <ZoneUtils.hpp>
#include "Structs.hpp"
#include "Functions.hpp"
#include "Patches/FFCompression.hpp"
#include "Patches/AssetHandler.hpp"

#include "H1/Utils/IO/filesystem.hpp"
#include "H1/Utils/IO/assetmanager.hpp"
#include "H1/Structs.hpp"

using namespace zonetool;

#include "Json.hpp"
using json = nlohmann::json;
using ordered_json = nlohmann::ordered_json;

#include "Assets/ComWorld.hpp"
#include "Assets/LocalizeEntry.hpp"
#include "Assets/MapEnts.hpp"
#include "Assets/PhysPreset.hpp"
#include "Assets/RawFile.hpp"
#include "Assets/StringTable.hpp"
#include "Assets/ScriptParseTree.hpp"
#include "Assets/AddonMapEnts.hpp"
#include "Assets/WeaponVariantDef.hpp"
#include "Assets/XModel.hpp"
#include "Assets/XAnimParts.hpp"
#include "Assets/Material.hpp"
#include "Assets/Techset.hpp"
#include "Assets/LeaderBoardDef.hpp"
#include "Assets/ClipMap.hpp"
#include "Assets/ZBarrierDef.hpp"
#include "Assets/VehicleDef.hpp"
#include "Assets/Slug.hpp"
#include "Assets/FontDef.hpp"
#include "Assets/FontIcon.hpp"
#include "Assets/PixelShader.hpp"
#include "Assets/GfxImage.hpp"

namespace ZoneTool
{
	namespace T6
	{
		class params
		{
		public:
			params();

			int size() const;
			const char* get(int index) const;
			std::string join(int index) const;

			const char* operator[](const int index) const
			{
				return this->get(index);
			}

		private:
			int nesting_;
		};

		void init();
	}
}
