#include "stdafx.hpp"
#include "Material.hpp"

//#include "IW6/Assets/Material.hpp"
#include "H1/Utils/IO/assetmanager.hpp"

#include "IW5/Assets/Material.hpp"

namespace ZoneTool
{
	namespace IW6
	{
		namespace
		{
			std::string get_iw6_techset(std::string name, std::string matname, bool* result)
			{
				if (mapped_techsets.find(name) == mapped_techsets.end())
				{
					ZONETOOL_ERROR("Could not find mapped IW6 techset for IW5 techset \"%s\" (material: %s)", name.data(), matname.data());
					*result = false;
					return "2d";
				}
				*result = true;
				return mapped_techsets[name];
			}

			std::unordered_map<std::uint8_t, std::uint8_t> mapped_sortkeys =
			{
				// should be the same
			};

			std::unordered_map<std::string, std::uint8_t> mapped_sortkeys_by_techset =
			{
				
			};

			std::uint8_t get_iw6_sortkey(std::uint8_t sortkey, std::string matname, std::string iw6_techset)
			{
				if (mapped_sortkeys_by_techset.find(iw6_techset) != mapped_sortkeys_by_techset.end())
				{
					return mapped_sortkeys_by_techset[iw6_techset];
				}

				if (mapped_sortkeys.contains(sortkey))
				{
					return mapped_sortkeys[sortkey];
				}

				//ZONETOOL_ERROR("Could not find mapped IW6 sortkey for sortkey: %d (material: %s)", sortkey, matname.data());

				return sortkey;
			}

			std::unordered_map<std::uint8_t, std::uint8_t> mapped_camera_regions =
			{
				{IW4::CAMERA_REGION_LIT_OPAQUE, IW6::CAMERA_REGION_LIT_OPAQUE},
				{IW4::CAMERA_REGION_LIT_TRANS, IW6::CAMERA_REGION_LIT_TRANS},
				{IW4::CAMERA_REGION_EMISSIVE, IW6::CAMERA_REGION_EMISSIVE},
				{IW4::CAMERA_REGION_DEPTH_HACK, IW6::CAMERA_REGION_DEPTH_HACK},
				{IW4::CAMERA_REGION_LIGHT_MAP_OPAQUE, IW6::CAMERA_REGION_LIT_OPAQUE},
				{IW4::CAMERA_REGION_NONE, IW6::CAMERA_REGION_NONE},
			};

			std::unordered_map<std::string, std::uint8_t> mapped_camera_regions_by_techset =
			{
				
			};

			std::uint8_t get_iw6_camera_region(std::uint8_t camera_region, std::string matname, std::string iw6_techset)
			{
				if (mapped_camera_regions_by_techset.find(iw6_techset) != mapped_camera_regions_by_techset.end())
				{
					return mapped_camera_regions_by_techset[iw6_techset];
				}

				if (mapped_camera_regions.contains(camera_region))
				{
					return mapped_camera_regions[camera_region];
				}

				ZONETOOL_ERROR("Could not find mapped IW6 camera region for camera region: %d (material: %s)", camera_region, matname.data());

				return camera_region;
			}

			std::uint8_t get_material_type_from_name(const std::string& name)
			{
				auto prefix_idx = name.find("/");
				if (prefix_idx != std::string::npos && prefix_idx)
				{
					std::string prefix = std::string(name.begin(), name.begin() + prefix_idx);
					if (prefix == "m")
					{
						return IW6::MTL_TYPE_MODEL;
					}
					else if (prefix == "me")
					{
						return IW6::MTL_TYPE_MODEL_VERTCOL;
					}
					else if (prefix == "mc")
					{
						return IW6::MTL_TYPE_MODEL_VERTCOL;
					}
					else if (prefix == "w")
					{
						return IW6::MTL_TYPE_WORLD;
					}
					else if (prefix == "wc")
					{
						return IW6::MTL_TYPE_WORLD_VERTCOL;
					}
					else if (prefix != "gfx")
					{
						ZONETOOL_WARNING("Unknown material type for prefix \"%s\" (material: %s)", prefix.data(), name.data());
					}
				}
				return IW6::MTL_TYPE_DEFAULT;
			}
		}
	}

	namespace IW4::IW6Dumper
	{
		std::string clean_name(const std::string& name)
		{
			auto new_name = name;

			for (auto i = 0u; i < name.size(); i++)
			{
				switch (new_name[i])
				{
				case '*':
					new_name[i] = '_';
					break;
				}
			}

			return new_name;
		}

#define MATERIAL_DUMP_STRING(entry) \
	matdata[#entry] = std::string(asset->entry);

#define MATERIAL_DUMP(entry) \
	matdata[#entry] = asset->entry;

#define MATERIAL_DUMP_INFO(entry) \
	matdata[#entry] = asset->info.entry;

		void dump(Material* asset, ZoneMemory* mem)
		{
			if (asset)
			{
				auto c_name = clean_name(asset->name);

				const auto path = "materials\\"s + c_name + ".json"s;
				auto file = zonetool::filesystem::file(path);

				ordered_json matdata;

				MATERIAL_DUMP_STRING(name);

				std::string iw4_techset;
				std::string iw6_techset;
				if (asset->techniqueSet)
				{
					iw4_techset = asset->techniqueSet->name;
					if (iw4_techset.starts_with("iw3/"))
					{
						iw4_techset.erase(0, 4);
					}

					if (iw4_techset.ends_with("_sat"))
					{
						auto idx = iw4_techset.find("_sat");
						iw4_techset.erase(idx, 4);
					}

					if (iw4_techset.ends_with(".3x")) // iw3xport
					{
						auto idx = iw4_techset.find(".3x");
						iw4_techset.erase(idx, 3);
					}

					bool result = false;
					iw6_techset = IW6::get_iw6_techset(iw4_techset, asset->name, &result);
					if (!result)
					{
						ZONETOOL_ERROR("Not dumping material \"%s\"", asset->name);
						return;
					}
					matdata["techniqueSet->name"] = iw6_techset;
				}

				matdata["gameFlags"] = asset->gameFlags; // convert
				matdata["sortKey"] = IW6::get_iw6_sortkey(asset->sortKey, asset->name, iw6_techset); // convert
				matdata["renderFlags"] = 0; // idk

				matdata["textureAtlasRowCount"] = asset->animationX;
				matdata["textureAtlasColumnCount"] = asset->animationY;
				matdata["textureAtlasFrameBlend"] = 0;
				matdata["textureAtlasAsArray"] = 0;

				matdata["surfaceTypeBits"] = asset->surfaceTypeBits; // convert
				// hashIndex;

				//matdata["stateFlags"] = asset->stateFlags; // convert
				matdata["cameraRegion"] = IW6::get_iw6_camera_region(asset->cameraRegion, asset->name, iw6_techset);
				matdata["materialType"] = IW6::get_material_type_from_name(asset->name);
				matdata["assetFlags"] = IW6::MTL_ASSETFLAG_NONE;

				ordered_json constant_table;
				for (int i = 0; i < asset->constantCount && iw4_techset != "2d"; i++)
				{
					ordered_json table;
					std::string constant_name = asset->constantTable[i].name;

					if (constant_name.size() > 12)
					{
						constant_name.resize(12);
					}

					table["name"] = constant_name.data();
					table["nameHash"] = asset->constantTable[i].nameHash;

					nlohmann::json literal_entry;
					literal_entry[0] = asset->constantTable[i].literal[0];
					literal_entry[1] = asset->constantTable[i].literal[1];
					literal_entry[2] = asset->constantTable[i].literal[2];
					literal_entry[3] = asset->constantTable[i].literal[3];
					table["literal"] = literal_entry;

					constant_table[constant_table.size()] = table;
				}

#define CONSTANT_TABLE_ADD_IF_NOT_FOUND(CONST_NAME, CONST_HASH, LITERAL_1, LITERAL_2, LITERAL_3, LITERAL_4) \
				bool has_table = false; \
				unsigned int table_idx = 0; \
				for (std::size_t i = 0; i < constant_table.size(); i++) \
				{ \
					if (constant_table[i]["nameHash"].get<unsigned int>() == CONST_HASH) \
					{ \
						has_table = true; \
					} \
				} \
				if (!has_table) \
				{ \
					for (std::size_t i = 0; i < constant_table.size(); i++) \
					{ \
						if (constant_table[i]["nameHash"].get<unsigned int>() > CONST_HASH) \
						{ \
							table_idx = i; \
							break; \
						} \
					} \
					if (table_idx == 0) \
					{ \
						table_idx = static_cast<unsigned int>(constant_table.size()); \
					} \
					ordered_json table; \
					table["name"] = CONST_NAME; \
					table["nameHash"] = CONST_HASH; \
					nlohmann::json literal_entry; \
					literal_entry[0] = LITERAL_1; \
					literal_entry[1] = LITERAL_2; \
					literal_entry[2] = LITERAL_3; \
					literal_entry[3] = LITERAL_4; \
					table["literal"] = literal_entry; \
					if (constant_table.is_null()) \
					{ \
						constant_table[constant_table.size()] = table; \
					} \
					else \
					{ \
						constant_table.insert(constant_table.begin() + table_idx, table); \
					} \
				}

				if (iw6_techset.find("_flag_") != std::string::npos)
				{
					CONSTANT_TABLE_ADD_IF_NOT_FOUND("flagParms", 2292903761, 1.0f, 0.0f, 0.0f, 0.0f);
				}

				if (iw6_techset.find("_cso_") != std::string::npos)
				{
					CONSTANT_TABLE_ADD_IF_NOT_FOUND("hdrColorParm", 3379990750, 20.0f, 0.0f, 0.0f, 0.0f);
				}

				if (iw6_techset.find("shadowcaster") != std::string::npos)
				{
					CONSTANT_TABLE_ADD_IF_NOT_FOUND("uvScale", 3809220315, 1.0f, 1.0f, 0.0f, 0.0f);
				}

				if (iw6_techset != "2d")
				{
					CONSTANT_TABLE_ADD_IF_NOT_FOUND("bloomParams", 3733414975, 0.0f, 0.0f, 0.0f, 0.0f);
				}

				matdata["constantTable"] = constant_table;

				int i_3447584578 = -1;

				ordered_json material_images;
				for (auto i = 0; i < asset->numMaps; i++)
				{
					if (asset->maps[i].typeHash > 3447584578 && i_3447584578 == -1)
					{
						i_3447584578 = i;
					}

					ordered_json image;
					if (asset->maps[i].semantic == 11)
					{
						auto* water = reinterpret_cast<water_t*>(asset->maps[i].image);
						if (water->image && water->image->name)
						{
							image["image"] = water->image->name;
						}
						else
						{
							image["image"] = "";
						}
						//image["waterinfo"] = nullptr;
					}
					else
					{
						if (asset->maps[i].image && asset->maps[i].image->name)
						{
							image["image"] = asset->maps[i].image->name;
						}
						else
						{
							image["image"] = "";
						}
					}

					image["semantic"] = asset->maps[i].semantic == 11 ? 2 : asset->maps[i].semantic; // convert? ( should be the same )
					image["samplerState"] = asset->maps[i].sampleState == 11 ? 19 : asset->maps[i].sampleState; // convert? ( should be fine )
					image["lastCharacter"] = asset->maps[i].secondLastCharacter;
					image["firstCharacter"] = asset->maps[i].firstCharacter;
					image["typeHash"] = asset->maps[i].typeHash;

					// add image data to material
					material_images.push_back(image);
				}

				// fix for certain techniques
				if (iw6_techset.find("_lmpb_") != std::string::npos || iw6_techset.find("_flag_") != std::string::npos)
				{
					if (i_3447584578 == -1)
					{
						i_3447584578 = asset->numMaps;
					}

					ordered_json image;
					image["image"] = "~envbrdflut_ggx_16-rg";
					image["semantic"] = 15;
					image["samplerState"] = 226;
					image["lastCharacter"] = 116;
					image["firstCharacter"] = 101;
					image["typeHash"] = 3447584578;
					material_images.insert(material_images.begin() + i_3447584578, image);
				}

				matdata["textureTable"] = material_images;

				auto str = matdata.dump(4, ' ', true, nlohmann::detail::error_handler_t::replace);

				matdata.clear();

				file.open("wb");
				file.write(str);
				file.close();
			}
		}
	}
}