#include "stdafx.hpp"
//#include "H1/Assets/Material.hpp"
#include "H1/Utils/IO/assetmanager.hpp"

namespace ZoneTool
{
	namespace
	{
		std::unordered_map<std::string, std::string> mapped_techsets =
		{
		//	IW3,										H1
			{"wc_l_sm_a0c0",							"wc_l_sm_a0c0_nfwpf_frt_aat"},
			{"wc_l_sm_r0c0",							"wc_l_sm_r0c0_nfwpf"},
			{"wc_l_sm_r0c0_nocast",						"wc_l_sm_r0c0_nfwpf_nocast"},
			{"wc_l_sm_r0c0d0n0s0",						"wc_l_sm_r0c0d0n0sd0_nfwpf"},
			{"wc_l_sm_r0c0d0n0s0p0",					"wc_l_sm_r0c0d0n0sd0_nfwpf"}, // couldn't find
			{"wc_l_sm_r0c0n0",							"wc_l_sm_r0c0n0_nfwpf"},
			{"wc_l_sm_r0c0n0s0",						"wc_l_sm_r0c0n0sd0_nfwpf"},
			{"wc_l_sm_r0c0n0s0_nocast",					"wc_l_sm_r0c0n0sd0_nfwpf"}, // no nocast
			{"wc_l_sm_r0c0n0s0p0",						"wc_l_sm_r0c0n0sd0p0_nfwpf"},
			{"wc_l_sm_r0c0q0n0s0",						"wc_l_sm_r0c0q0n0sd0_nfwpf"},
			{"wc_l_sm_r0c0q0n0s0p0",					"wc_l_sm_r0c0q0n0sd0p0_nfwpf"},
			{"wc_l_sm_r0c0s0",							"wc_l_sm_r0c0sd0_nfwpf"},
			{"wc_l_sm_r0c0s0p0",						"wc_l_sm_r0c0sd0p0_nfwpf"},
			{"wc_l_sm_r0c0p0",							"wc_l_sm_r0c0_nfwpf"}, // couldn't find
			{"wc_l_sm_t0c0",							"wc_l_sm_lmpb_t0c0_nfwpf"},
			{"wc_l_sm_t0c0n0",							"wc_l_sm_lmpb_t0c0n0_nfwpf"},
			{"wc_l_sm_t0c0n0s0",						"wc_l_sm_lmpb_t0c0n0sd0_nfwpf"},
			{"wc_l_sm_t0c0n0s0p0",						"wc_l_sm_lmpb_t0c0n0sd0_nfwpf"}, // couldn't find
			{"wc_l_sm_t0c0s0",							"wc_l_sm_lmpb_t0c0sd0_nfwpf"},
			{"wc_l_sm_t0c0p0",							"wc_l_sm_lmpb_t0c0_nfwpf"}, // couldn't find
			{"wc_l_sm_b0c0",							"wc_l_sm_lmpb_ndw_b0c0_nfwpf_frt_im_aat"},
			{"wc_l_sm_b0c0d0n0",						"wc_l_sm_ndw_b0c0d0n0_nfwpf_frt_aat"},
			{"wc_l_sm_b0c0d0n0s0",						"wc_l_sm_ndw_b0c0d0n0_nfwpf_frt_aat"}, // couldn't find
			{"wc_l_sm_b0c0n0",							"wc_l_sm_lmpb_ndw_b0c0n0_nfwpf_frt_im_aat"},
			{"wc_l_sm_b0c0n0s0",						"wc_l_sm_lmpb_ndw_b0c0n0sd0_nfwpf_frt_im_aat"},
			{"wc_l_sm_b0c0n0s0p0",						"wc_l_sm_lmpb_ndw_b0c0n0sd0_nfwpf_frt_im_aat"}, // couldn't find
			{"wc_l_sm_b0c0n0p0",						"wc_l_sm_lmpb_ndw_b0c0n0_nfwpf_frt_im_aat"}, // couldn't find
			{"wc_l_sm_b0c0s0",							"wc_l_sm_lmpb_ndw_b0c0sd0_nfwpf_frt_aat"},
			{"wc_l_sm_b0c0s0_nocast",					"wc_l_sm_lmpb_ndw_b0c0sd0_nfwpf_frt_aat"}, // no nocast
			{"wc_l_sm_b0c0s0p0",						"wc_l_sm_lmpb_ndw_b0c0sd0_nfwpf_frt_aat"}, // couldn't find
			{"wc_l_sm_b0c0q0n0s0",						"wc_l_sm_lmpb_ndw_b0c0q0n0sd0_nfwpf_frt_aat"},
			{"wc_l_sm_b0c0q0n0s0p0",					"wc_l_sm_lmpb_ndw_b0c0q0n0sd0_nfwpf_frt_aat"}, // couldn't find
			{"wc_l_sm_ua_b0c0n0s0p0_nocast",			"wc_l_sm_ndw_ua_b0c0n0sd0p0_cltrans_nocast_frt_aat"},
			//{"wc_l_sm_b0c0n0s0_custom_growing_ice_cracks", "wc_l_sm_lmpb_ndw_b0c0n0sd0_nfwpf_frt_im_aat"}, // coudln't find
			//{"wc_l_sm_b0c0n0s0_custom_growing_ice_cracks_sat", "wc_l_sm_lmpb_ndw_b0c0n0sd0_nfwpf_frt_im_aat"}, // couldn't find

			{"wc_l_ua_b0c0_nocast",						"wc_l_sm_ndw_ua_b0c0_cltrans_nocast"}, // could be wrong

			{"wc_unlit",								"wc_unlit_blend_lin_ndw_nfwpf"}, // couldn't find
			{"wc_unlit_nofog",							"wc_unlit_blend_lin_ndw_nfwpf"}, // couldn't find
			{"wc_unlit_alphatest",						"wc_unlit_blend_lin_ndw_nfwpf"}, // couldn't find
			{"wc_unlit_add",							"wc_unlit_add_lin_ndw_nfwpf"}, // coudln't find
			{"wc_unlit_add_lin",						"wc_unlit_add_lin_ndw_nfwpf"},
			{"wc_unlit_add_lin_ua",						"wc_unlit_add_lin_ndw_ua_nfwpf"},
			{"wc_unlit_blend",							"wc_unlit_blend_lin_ndw_nfwpf"}, // couldn't find
			{"wc_unlit_blend_lin_ua",					"wc_unlit_blend_lin_ndw_ua_cltrans"},
			{"wc_unlit_distfalloff",					"wc_unlit_distfalloff_replace_ndw_cltrans"}, // couldn't find
			{"wc_unlit_distfalloff_replace",			"wc_unlit_distfalloff_replace_ndw_cltrans"},
			{"wc_unlit_falloff_add",					"wc_unlit_falloff_add_lin_ndw_cltrans"}, // couldn't find
			{"wc_unlit_falloff_add_lin",				"wc_unlit_falloff_add_lin_ndw_cltrans"},
			{"wc_unlit_falloff_add_lin_ua",				"wc_unlit_falloff_add_lin_ndw_cltrans"}, // couldn't find
			{"wc_unlit_multiply",						"wc_unlit_multiply_lin_ndw_nfwpf"}, // couldn't find
			{"wc_unlit_multiply_lin",					"wc_unlit_multiply_lin_ndw_nfwpf_im"},
			{"wc_unlit_replace",						"wc_unlit_replace_lin_nfwpf"}, // couldn't find
			{"wc_unlit_replace_lin",					"wc_unlit_replace_lin_nfwpf"},
			{"wc_unlit_replace_lin_nocast",				"wc_unlit_replace_lin_nfwpf_nocast"},
			{"wc_effect",								"wc_unlit_blend_lin_ndw_nfwpf"}, // ??
			{"wc_ambient_t0c0",							"wc_ambient_t0c0_nfwpf"},
			{"wc_sky",									"wc_sky_cso_nfwpf"},
			{"wc_shadowcaster",							"wc_shadowcaster"},
			{"wc_water",								"2d"}, // couldn't find
			{"wc_tools",								"wc_tools_r0c0ct0"}, // possibly be wrong
			{"wc_default",								"wc_default"},

			{"m_l_sm_b0c0n0s0p0",						"m_l_sm_b0c0n0sd0p0_cltrans"},
			{"m_l_sm_b0c0q0n0s0",						"m_l_sm_b0c0n0sd0_cltrans"}, // couldn't find

			{"mc_l_sm_a0c0",							"wc_l_sm_a0c0_nfwpf_frt_aat"},
			{"mc_l_sm_a0c0_nocast",						"wc_l_sm_a0c0_nfwpf_frt_aat"}, // no nocast
			{"mc_l_sm_r0c0",							"mc_l_sm_r0c0_nfwpf"},
			{"mc_l_sm_r0c0_nocast",						"mc_l_sm_r0c0_nfwpf"}, // no nocast
			{"mc_l_sm_r0c0d0",							"mc_l_sm_r0c0_nfwpf"}, // couldn't find
			{"mc_l_sm_r0c0d0s0",						"mc_l_sm_r0c0sd0_nfwpf"}, // couldn't find
			{"mc_l_sm_r0c0d0n0",						"mc_l_sm_r0c0n0_nfwpf"}, // couldn't find
			{"mc_l_sm_r0c0d0n0s0",						"mc_l_sm_r0c0d0n0sd0_nfwpf"},
			{"mc_l_sm_r0c0d0n0s0p0",					"mc_l_sm_r0c0d0n0sd0p0_nfwpf"},
			{"mc_l_sm_r0c0s0",							"mc_l_sm_r0c0sd0_nfwpf"},
			{"mc_l_sm_r0c0s0_nocast",					"mc_l_sm_r0c0sd0_nfwpf"}, // no nocast
			{"mc_l_sm_r0c0s0p0",						"mc_l_sm_r0c0sd0p0_nfwpf"},
			{"mc_l_sm_r0c0n0",							"mc_l_sm_r0c0n0_nfwpf"},
			{"mc_l_sm_r0c0n0s0",						"mc_l_sm_r0c0n0sd0_nfwpf"},
			{"mc_l_sm_r0c0n0s0_em",						"mc_l_sm_r0c0n0sd0_nfwpf"}, // codo
			{"mc_l_sm_r0c0n0s0_nocast",					"mc_l_sm_r0c0n0sd0_nfwpf"}, // no nocast
			{"mc_l_sm_r0c0n0s0p0",						"mc_l_sm_r0c0n0sd0p0_nfwpf"},
			{"mc_l_sm_r0c0p0",							"mc_l_sm_r0c0p0_nfwpf"},
			{"mc_l_sm_r0c0q0n0",						"mc_l_sm_r0c0n0_nfwpf"}, // couldn't find
			{"mc_l_sm_r0c0q0n0s0",						"mc_l_sm_r0c0n0_nfwpf"}, // couldn't find
			{"mc_l_sm_r0c0q0n0s0p0",					"mc_l_sm_r0c0q0n0sd0p0_nfwpf"},
			{"mc_l_sm_t0c0",							"mc_l_sm_t0c0_nfwpf"},
			{"mc_l_sm_t0c0_nocast",						"mc_l_sm_t0c0_nfwpf_nocast"},
			{"mc_l_sm_t0c0s0",							"mc_l_sm_t0c0sd0_nfwpf"},
			{"mc_l_sm_t0c0n0",							"mc_l_sm_t0c0n0_nfwpf_frt_aat"}, // could be wrong
			{"mc_l_sm_t0c0n0_nocast",					"mc_l_sm_t0c0n0_nfwpf_frt_aat"}, // no nocast
			{"mc_l_sm_t0c0n0s0",						"mc_l_sm_t0c0n0sd0_nfwpf"},
			{"mc_l_sm_t0c0n0s0_nocast",					"mc_l_sm_t0c0n0sd0_nfwpf_nocast"},
			{"mc_l_sm_t0c0n0s0p0",						"mc_l_sm_t0c0n0sd0p0_nfwpf"},
			{"mc_l_sm_t0c0p0",							"mc_l_sm_t0c0_nfwpf"}, // couldn't find
			{"mc_l_sm_t0c0q0n0s0",						"mc_l_sm_t0c0n0sd0_nfwpf"}, // couldn't find
			{"mc_l_sm_t0c0q0n0s0p0",					"mc_l_sm_t0c0n0sd0p0_nfwpf"}, // couldn't find // mc_l_sm_t0c0d0n0sd0p0ct0_nfwpf
			{"mc_l_sm_b0c0",							"mc_l_sm_lmpb_ndw_b0c0_nfwpf_frt_im_aat"},
			{"mc_l_sm_b0c0_nocast",						"mc_l_sm_lmpb_ndw_b0c0_nfwpf_frt_im_aat"}, // couldn't find
			{"mc_l_sm_b0c0d0p0",						"mc_l_sm_ndw_b0c0d0p0_cltrans"},
			{"mc_l_sm_b0c0s0",							"mc_l_sm_lmpb_ndw_b0c0sd0_nfwpf_frt_aat"},
			{"mc_l_sm_b0c0n0",							"mc_l_sm_lmpb_ndw_b0c0n0_nfwpf_frt_im_aat"},
			{"mc_l_sm_b0c0n0s0",						"mc_l_sm_lmpb_ndw_b0c0n0sd0_nfwpf_frt_im_aat"},
			{"mc_l_sm_b0c0n0s0p0",						"mc_l_sm_lmpb_ndw_b0c0n0sd0_nfwpf_frt_im_aat"}, // couldn't find
			{"mc_l_sm_b0c0p0",							"mc_l_sm_lmpb_ndw_b0c0_nfwpf_frt_im_aat"}, // couldn't find
			{"mc_l_sm_b0c0q0n0s0",						"mc_l_sm_ndw_b0c0q0n0sd0_nfwpf_frt_aat"},
			{"mc_l_sm_b0c0n0s0_custom_growing_ice_cracks", "mc_l_sm_lmpb_ndw_b0c0n0sd0_nfwpf_frt_im_aat"}, // couldn't find
			{"mc_l_sm_b0c0n0s0_custom_growing_ice_cracks_sat", "mc_l_sm_lmpb_ndw_b0c0n0sd0_nfwpf_frt_im_aat"}, // couldn't find
			{"mc_l_sm_flag_t0c0n0s0",					"mc_l_sm_flag_fuv_t0c0n0sd0_nfwpf"},
			{"mc_l_r0c0n0s0",							"mc_l_r0c0n0sd0_nfwpf"},
			{"mc_l_r0c0n0s0_nocast",					"mc_l_r0c0n0sd0_nfwpf"}, // no nocast
			{"mc_l_t0c0n0s0",							"mc_l_t0c0n0sd0_nfwpf"},

			{"mc_unlit",								"mc_unlit_blend_lin_ndw_nfwpf"}, // couldn't find
			{"mc_unlit_nofog",							"mc_unlit_blend_lin_ndw_nfwpf"}, // couldn't find
			{"mc_unlit_alphatest",						"mc_unlit_blend_lin_ndw_nfwpf"}, // couldn't find
			{"mc_unlit_add",							"mc_unlit_add_lin_ndw_cltrans"}, // couldn't find
			{"mc_unlit_add_lin",						"mc_unlit_add_lin_ndw_cltrans"},
			{"mc_unlit_add_lin_ua",						"mc_unlit_add_lin_ndw_cltrans"}, // no ua
			{"mc_unlit_blend_lin",						"mc_unlit_blend_lin_ct_ndw_nfwpf"},
			{"mc_unlit_multiply",						"mc_unlit_multiply_lin_ndw_nfwpf"}, // couldn't find
			{"mc_unlit_multiply_lin",					"mc_unlit_multiply_lin_ndw_nfwpf"},
			{"mc_unlit_replace",						"mc_unlit_replace_lin_nfwpf"}, // couldn't find
			{"mc_unlit_replace_lin",					"mc_unlit_replace_lin_nfwpf"},
			{"mc_unlit_replace_lin_nofog",				"mc_unlit_replace_lin_nfwpf"}, // no nofog
			{"mc_unlit_replace_lin_nocast",				"mc_unlit_replace_lin_nfwpf_nocast"},
			{"mc_ambient_t0c0",							"mc_ambient_t0c0_nfwpf"},
			{"mc_ambient_t0c0_nocast",					"mc_ambient_t0c0_nfwpf_nocast"},
			{"mc_shadowcaster",							"mc_shadowcaster_atest"}, // couldn't find
			{"mc_shadowcaster_atest",					"mc_shadowcaster_atest"},
			{"mc_reflexsight",							"mc_reflexsight"},

			{"mc_effect",								"mc_effect_blend_nofog_ndw"}, // couldn't find
			{"mc_effect_add_nofog",						"mc_effect_blend_nofog_ndw"}, // couldn't find
			{"mc_effect_blend_nofog",					"mc_effect_blend_nofog_ndw"},
			{"mc_effect_falloff_add_nofog",				"mc_effect_blend_nofog_ndw"}, // couldn't find
			{"mc_effect_falloff_add_lin_nofog",			"mc_effect_blend_nofog_ndw"}, // couldn't find
			{"mc_effect_zfeather_falloff_add_nofog",	"mc_effect_zf_add_nofog_ndw"}, // couldn't find
			{"mc_effect_zfeather_falloff_add_nofog_eyeoffset", "mc_effect_zf_falloff_add_nofog_eo_ndw"},
			{"mc_effect_zfeather_falloff_add_lin_nofog", "mc_effect_zf_add_nofog_ndw"}, // couldn't find
			{"mc_effect_zfeather_falloff_add_lin_nofog_eyeoffset", "mc_effect_zf_falloff_add_nofog_eo_ndw"}, // couldn't find
			{"mc_effect_zfeather_falloff_screen_nofog_eyeoffset", "mc_effect_zf_screen_nofog_spot_sm_ndw"}, // couldn't find

			//{"mc_tools",								"2d"}, // couldn't find

			{"2d",										"2d"},

			{"distortion_scale",						"distortion_scale_legacydst_dat"}, // could be wrong
			{"distortion_scale_zfeather",				"distortion_scale_legacydst_zf_dat"}, // could be wrong

			{"effect",									"effect_blend_ndw"}, // couldn't find
			{"effect_nofog",							"effect_blend_nofog_ndw"}, // couldn't find
			{"effect_add",								"effect_add_ndw"},
			{"effect_add_eyeoffset",					"effect_add_eo"},
			{"effect_add_nofog",						"effect_add_nofog_ndw"},
			{"effect_add_nofog_eyeoffset",				"effect_add_nofog_eo_ndw"},
			{"effect_blend",							"effect_blend_ndw"},
			{"effect_blend_nofog",						"effect_blend_nofog_ndw"},
			//{"effect_replace_lin",					"2d"}, // m_effect_replace_ndw
			{"effect_falloff_add",						"effect_falloff_add_ndw"},
			{"effect_falloff_add_nofog",				"effect_falloff_add_nofog_ndw"},
			{"effect_falloff_blend",					"effect_falloff_blend_ndw"},
			{"effect_zfeather",							"effect_zf_blend_ndw"}, // couldn't find
			{"effect_zfeather_nofog",					"effect_zf_blend_nofog_ndw" }, // couldn't find
			{"effect_zfeather_add",						"effect_zf_add_ndw"},
			{"effect_zfeather_add_nofog",				"effect_zf_add_nofog_ndw"},
			{"effect_zfeather_add_nofog_eyeoffset",		"effect_zf_add_nofog_eo_ndw"},
			{"effect_zfeather_add_eyeoffset",			"effect_zf_add_eo_ndw"},
			{"effect_zfeather_blend",					"effect_zf_blend_ndw"},
			{"effect_zfeather_blend_nofog",				"effect_zf_blend_nofog_ndw"},
			{"effect_zfeather_blend_spot_sm",			"effect_zf_blend_ndw"}, // couldn't find
			{"effect_zfeather_falloff",					"effect_zf_falloff_blend_ndw"}, // couldn't find
			{"effect_zfeather_falloff_nofog",			"effect_zf_falloff_blend_nofog_ndw"}, // couldn't find
			{"effect_zfeather_falloff_add",				"effect_zf_falloff_add_ndw"},
			{"effect_zfeather_falloff_add_nofog",		"effect_zf_falloff_add_nofog_ndw" },
			{"effect_zfeather_falloff_add_eyeoffset",	"effect_zf_falloff_add_eo_ndw"},
			{"effect_zfeather_falloff_add_nofog_eyeoffset", "effect_zf_falloff_add_nofog_eo_ndw"},
			{"effect_zfeather_falloff_blend",			"effect_zf_falloff_blend_ndw"},
			{"effect_zfeather_falloff_screen",			"effect_zf_falloff_screen_nofog_ndw"}, // closest i could find
			{"effect_zfeather_outdoor_blend",			"effect_zf_outdoor_blend_ndw"},
			{"effect_zfeather_screen",					"effect_zf_screen_ndw"},

			{"particle_cloud",							"particle_cloud_replace_ga"}, // could be wrong
			{"particle_cloud_add",						"particle_cloud_add_ga"},
			{"particle_cloud_outdoor",					"particle_cloud_outdoor_replace_ga"}, // could be wrong
			{"particle_cloud_outdoor_add",				"particle_cloud_outdoor_add_ga"},
			{"particle_cloud_sparkf_add",				"particle_cloud_sparkf_add_ga"},
			{"particle_cloud_spark_add",				"particle_cloud_spark_add_ga"},

			{"grain_overlay",							"grain_overlay"},

			{"splatter_alt",							"splatter_alt"},

			{"tools",									"tools_r0c0ct0"}, // could be wrong
			{"tools_b0c0",								"tools_b0c0ct0"}, // could be wrong
		};

		std::string get_h1_techset(std::string name, std::string matname, bool* result)
		{
			if (mapped_techsets.find(name) == mapped_techsets.end())
			{
				ZONETOOL_ERROR("Could not find mapped H1 techset for IW3 techset \"%s\" (material: %s)", name.data(), matname.data());
				*result = false;
				return "2d";
			}
			*result = true;
			return mapped_techsets[name];
		}

		std::uint64_t convert_surf_type_bits(std::uint32_t bits)
		{
			std::uint64_t h1_bits = H1::SurfaceTypeBits::SURFTYPE_BITS_DEFAULT;

			auto convert = [&](IW3::SurfaceTypeBits a, H1::SurfaceTypeBits b)
			{
				h1_bits |= ((bits & a) == a) ? b : 0;
			};

			convert(IW3::SurfaceTypeBits::SURFTYPE_BITS_BARK, H1::SurfaceTypeBits::SURFTYPE_BITS_BARK);
			convert(IW3::SurfaceTypeBits::SURFTYPE_BITS_BRICK, H1::SurfaceTypeBits::SURFTYPE_BITS_BRICK);
			convert(IW3::SurfaceTypeBits::SURFTYPE_BITS_CARPET, H1::SurfaceTypeBits::SURFTYPE_BITS_CARPET);
			convert(IW3::SurfaceTypeBits::SURFTYPE_BITS_CLOTH, H1::SurfaceTypeBits::SURFTYPE_BITS_CLOTH);
			convert(IW3::SurfaceTypeBits::SURFTYPE_BITS_CONCRETE, H1::SurfaceTypeBits::SURFTYPE_BITS_CONCRETE);
			convert(IW3::SurfaceTypeBits::SURFTYPE_BITS_DIRT, H1::SurfaceTypeBits::SURFTYPE_BITS_DIRT);
			convert(IW3::SurfaceTypeBits::SURFTYPE_BITS_FLESH, H1::SurfaceTypeBits::SURFTYPE_BITS_FLESH);
			convert(IW3::SurfaceTypeBits::SURFTYPE_BITS_FOLIAGE, H1::SurfaceTypeBits::SURFTYPE_BITS_FOLIAGE_DEBRIS);
			convert(IW3::SurfaceTypeBits::SURFTYPE_BITS_GLASS, H1::SurfaceTypeBits::SURFTYPE_BITS_GLASS);
			convert(IW3::SurfaceTypeBits::SURFTYPE_BITS_GRASS, H1::SurfaceTypeBits::SURFTYPE_BITS_GRASS);
			convert(IW3::SurfaceTypeBits::SURFTYPE_BITS_GRAVEL, H1::SurfaceTypeBits::SURFTYPE_BITS_GRAVEL);
			convert(IW3::SurfaceTypeBits::SURFTYPE_BITS_ICE, H1::SurfaceTypeBits::SURFTYPE_BITS_ICE);
			convert(IW3::SurfaceTypeBits::SURFTYPE_BITS_METAL, H1::SurfaceTypeBits::SURFTYPE_BITS_METAL_SOLID);
			convert(IW3::SurfaceTypeBits::SURFTYPE_BITS_MUD, H1::SurfaceTypeBits::SURFTYPE_BITS_MUD);
			convert(IW3::SurfaceTypeBits::SURFTYPE_BITS_PAPER, H1::SurfaceTypeBits::SURFTYPE_BITS_PAPER);
			convert(IW3::SurfaceTypeBits::SURFTYPE_BITS_PLASTER, H1::SurfaceTypeBits::SURFTYPE_BITS_PLASTER);
			convert(IW3::SurfaceTypeBits::SURFTYPE_BITS_ROCK, H1::SurfaceTypeBits::SURFTYPE_BITS_ROCK);
			convert(IW3::SurfaceTypeBits::SURFTYPE_BITS_SAND, H1::SurfaceTypeBits::SURFTYPE_BITS_SAND);
			convert(IW3::SurfaceTypeBits::SURFTYPE_BITS_SNOW, H1::SurfaceTypeBits::SURFTYPE_BITS_SNOW);
			convert(IW3::SurfaceTypeBits::SURFTYPE_BITS_WATER, H1::SurfaceTypeBits::SURFTYPE_BITS_WATER_WAIST);
			convert(IW3::SurfaceTypeBits::SURFTYPE_BITS_WOOD, H1::SurfaceTypeBits::SURFTYPE_BITS_WOOD_SOLID);
			convert(IW3::SurfaceTypeBits::SURFTYPE_BITS_ASPHALT, H1::SurfaceTypeBits::SURFTYPE_BITS_ASPHALT);
			convert(IW3::SurfaceTypeBits::SURFTYPE_BITS_CERAMIC, H1::SurfaceTypeBits::SURFTYPE_BITS_CERAMIC);
			convert(IW3::SurfaceTypeBits::SURFTYPE_BITS_PLASTIC, H1::SurfaceTypeBits::SURFTYPE_BITS_PLASTIC_SOLID);
			convert(IW3::SurfaceTypeBits::SURFTYPE_BITS_RUBBER, H1::SurfaceTypeBits::SURFTYPE_BITS_RUBBER);
			convert(IW3::SurfaceTypeBits::SURFTYPE_BITS_CUSHION, H1::SurfaceTypeBits::SURFTYPE_BITS_CUSHION);
			convert(IW3::SurfaceTypeBits::SURFTYPE_BITS_FRUIT, H1::SurfaceTypeBits::SURFTYPE_BITS_FRUIT);
			convert(IW3::SurfaceTypeBits::SURFTYPE_BITS_PAINTEDMETAL, H1::SurfaceTypeBits::SURFTYPE_BITS_PAINTEDMETAL);
			convert(IW3::SurfaceTypeBits::SURFTYPE_BITS_SLUSH, H1::SurfaceTypeBits::SURFTYPE_BITS_SLUSH);

			return h1_bits;
		} IW3::CSurfaceFlags;

		std::unordered_map<std::uint8_t, std::uint8_t> mapped_sortkeys =
		{
			{0, 48},	// Distortion (confirmed)
						// Opaque water (never used)
						// Boat hull (never used)
			{3, 1},		// Opaque ambient
			{4, 2},		// Opaque (confirmed)
			{5, 3},		// Sky (confirmed)
			{6, 4},		// Skybox sun/moon
			{7, 5},		// Clouds  NOT SURE
			{8, 6},		// Horizon NOT SURE
			{9, 7},		// Decal bottom 1
			{10, 8},	// Decal bottom 2
			{11, 9},	// Decal bottom 3
			{12, 10},	// Decal static (confirmed)
			{13, 11},	// Decal mid 1
			{14, 12},	// Decal mid 2 (confirmed)
			{15, 13},	// Decal mid 3
			{24, 14},	// Weapon Impact (confirmed)
			{29, 15},	// Decal top 1
			{30, 16},	// Decal top 2 (confirmed)
			{31, 17},	// Decal top 3
			//{32, 32},	// Multiplicative
			//{33, 33},	// Banner/ Curtain (wild guess!)
			//{34, 34},	// Hair. I matched it with german shepherd material sortkey, i hope its ok.
			//{35, 35},	// Underwater
			//{36, 36},	// Transparent water
			//{37, 37},	// Corona (wild guess)
			{38, 26},	// Window inside
			{39, 27},	// Window outside (confirmed)
			//{40, 40},	// Before effects 1 (wild guess)
			//{41, 41},	// Before effects 2 (wild guess)
			//{42, 42},	// Before effects 3 (extremely wild guess)
			{43, 7},	// Blend / additive => to a decal layer (confirmed)
			{48, 53},	// Effect auto sort! (confirmed)
			{56, 30},	// AE Bottom
			{57, 31},	// AE Middle
			{58, 32},	// AE top (confirmed)
			{59, 36},	// Viewmodel effect
		};

		std::unordered_map<std::string, std::uint8_t> mapped_sortkeys_by_techset =
		{
			{"2d", 60},
			{"mc_shadowcaster_atest", 38},
			{"wc_shadowcaster", 38},
		};

		std::uint8_t get_h1_sortkey(std::uint8_t sortkey, std::string matname, std::string h1_techset, std::string iw3_techset)
		{
			if (iw3_techset == "wc_effect")
			{
				return 12;
			}

			if (mapped_sortkeys_by_techset.find(h1_techset) != mapped_sortkeys_by_techset.end())
			{
				return mapped_sortkeys_by_techset[h1_techset];
			}

			if (mapped_sortkeys.contains(sortkey))
			{
				return mapped_sortkeys[sortkey];
			}

			ZONETOOL_ERROR("Could not find mapped H1 sortkey for sortkey: %d (material: %s)", sortkey, matname.data());

			return sortkey;
		}

		std::unordered_map<std::uint8_t, std::uint8_t> mapped_camera_regions =
		{
			{IW3::CAMERA_REGION_LIT, H1::CAMERA_REGION_LIT_OPAQUE},
			{IW3::CAMERA_REGION_DECAL, H1::CAMERA_REGION_LIT_TRANS},
			{IW3::CAMERA_REGION_EMISSIVE, H1::CAMERA_REGION_EMISSIVE},
			{IW3::CAMERA_REGION_NONE, H1::CAMERA_REGION_NONE},
		};

		std::unordered_map<std::string, std::uint8_t> mapped_camera_regions_by_techset =
		{
			{"2d", H1::CAMERA_REGION_NONE},
			{"mc_shadowcaster_atest", H1::CAMERA_REGION_NONE},
			{"wc_shadowcaster", H1::CAMERA_REGION_NONE},
		};

		std::uint8_t get_h1_camera_region(std::uint8_t camera_region, std::string matname, std::string h1_techset, std::string iw3_techset)
		{
			if (iw3_techset == "wc_effect")
			{
				return H1::CAMERA_REGION_LIT_DECAL;
			}

			if (mapped_camera_regions_by_techset.find(h1_techset) != mapped_camera_regions_by_techset.end())
			{
				return mapped_camera_regions_by_techset[h1_techset];
			}

			if (h1_techset.find("_t0c0") != std::string::npos || h1_techset.find("_b0c0") != std::string::npos)
			{
				//return H1::CAMERA_REGION_LIT_TRANS;
			}

			if (mapped_camera_regions.contains(camera_region))
			{
				return mapped_camera_regions[camera_region];
			}

			ZONETOOL_ERROR("Could not find mapped H1 camera region for camera region: %d (material: %s)", camera_region, matname.data());

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
					return H1::MTL_TYPE_MODEL;
				}
				else if (prefix == "me")
				{
					return H1::MTL_TYPE_MODEL_GREY;
				}
				else if (prefix == "mc")
				{
					return H1::MTL_TYPE_MODEL_VERTCOL;
				}
				else if (prefix == "w")
				{
					return H1::MTL_TYPE_WORLD;
				}
				else if (prefix == "wc")
				{
					return H1::MTL_TYPE_WORLD_VERTCOL;
				}
				else if (prefix != "gfx")
				{
					ZONETOOL_WARNING("Unknown material type for prefix \"%s\" (material: %s)", prefix.data(), name.data());
				}
			}
			return H1::MTL_TYPE_DEFAULT;
		}

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
	}

	namespace H1
	{
		struct MaterialGameFlagsFields
		{
			unsigned char unk1 : 1; // 0x1
			unsigned char addShadowToPrimaryLight : 1; // 0x2
			unsigned char isFoliageRequiresGroundLighting : 1; // 0x4
			unsigned char unk4 : 1; // 0x8
			unsigned char unk5 : 1; // 0x10
			unsigned char unk6 : 1; // 0x20
			unsigned char unk7 : 1; // 0x40
			unsigned char unkCastShadowMaybe : 1; // 0x80
		};

		union MaterialGameFlags
		{
			MaterialGameFlagsFields fields;
			unsigned char packed;
		};
	}

	namespace IW3
	{
		void IMaterial::dump(Material* asset, ZoneMemory* mem)
		{
			if (asset)
			{
				auto c_name = clean_name(asset->name);

				const auto path = "materials\\"s + c_name + ".json"s;
				auto file = zonetool::filesystem::file(path);

				ordered_json matdata;

				MATERIAL_DUMP_STRING(name);

				std::string iw3_techset;
				std::string h1_techset;
				if (asset->techniqueSet)
				{
					iw3_techset = asset->techniqueSet->name;

					bool result = false;
					h1_techset = get_h1_techset(iw3_techset, asset->name, &result);
					if (!result)
					{
						ZONETOOL_ERROR("Not dumping material \"%s\"", asset->name);
						return;
					}
					matdata["techniqueSet->name"] = h1_techset;
				}

				MaterialGameFlags iw3_game_flags;
				iw3_game_flags.packed = asset->gameFlags;

				H1::MaterialGameFlags h1_game_flags;
				h1_game_flags.packed = iw3_game_flags.packed;
				h1_game_flags.fields.unk7 = iw3_game_flags.fields.unkNeededForSModelDisplay;
				h1_game_flags.fields.unkCastShadowMaybe = iw3_game_flags.fields.MTL_GAMEFLAG_CASTS_SHADOW;

				matdata["gameFlags"] = h1_game_flags.packed;//asset->gameFlags; // convert

				matdata["sortKey"] = get_h1_sortkey(asset->sortKey, asset->name, h1_techset, iw3_techset);
				matdata["renderFlags"] = 0; // idk

				matdata["textureAtlasRowCount"] = asset->textureAtlasRowCount;
				matdata["textureAtlasColumnCount"] = asset->textureAtlasColumnCount;
				matdata["textureAtlasFrameBlend"] = 0;
				matdata["textureAtlasAsArray"] = 0;

				matdata["surfaceTypeBits"] = convert_surf_type_bits(asset->surfaceTypeBits);
				// hashIndex;

				//matdata["stateFlags"] = asset->stateFlags; // convert ( should be the same )
				matdata["cameraRegion"] = get_h1_camera_region(asset->cameraRegion, asset->name, h1_techset, iw3_techset);
				matdata["materialType"] = get_material_type_from_name(asset->name);
				matdata["assetFlags"] = H1::MTL_ASSETFLAG_NONE;

				/*if (asset->drawSurf.packed != 0)
				{
					matdata["drawSurf"]["objectId"] = static_cast<int>(asset->drawSurf.fields.objectId);
					matdata["drawSurf"]["reflectionProbeIndex"] = static_cast<int>(asset->drawSurf.fields.reflectionProbeIndex);
					matdata["drawSurf"]["hasGfxEntIndex"] = 0;
					matdata["drawSurf"]["customIndex"] = static_cast<int>(asset->drawSurf.fields.customIndex);
					matdata["drawSurf"]["materialSortedIndex"] = static_cast<int>(asset->drawSurf.fields.materialSortedIndex);
					matdata["drawSurf"]["tessellation"] = 0;
					matdata["drawSurf"]["prepass"] = static_cast<int>(asset->drawSurf.fields.prepass);
					matdata["drawSurf"]["useHeroLighting"] = 0;
					matdata["drawSurf"]["sceneLightEnvIndex"] = static_cast<int>(asset->drawSurf.fields.primaryLightIndex);
					matdata["drawSurf"]["viewModelRender"] = 0;
					matdata["drawSurf"]["surfType"] = static_cast<int>(asset->drawSurf.fields.surfType); // convert
					matdata["drawSurf"]["primarySortKey"] = matdata["sortKey"].get<int>(); // static_cast<int>(asset->drawSurf.fields.primarySortKey)
				}*/

				ordered_json constant_table;
				for (int i = 0; i < asset->constantCount; i++)
				{
					ordered_json table;
					std::string constant_name = asset->constantTable[i].name;

					if (constant_name.size() > 12)
					{
						constant_name.resize(12);
					}

					if (constant_name == "colorTint" && 
						asset->constantTable[i].literal[0] == 1.0f && 
						asset->constantTable[i].literal[1] == 1.0f && 
						asset->constantTable[i].literal[2] == 1.0f && 
						asset->constantTable[i].literal[3] == 1.0f)
					{
						continue;
					}

					table["name"] = constant_name.data();
					table["nameHash"] = asset->constantTable[i].nameHash;

					nlohmann::json literal_entry;
					if (constant_name == "envMapParms")
					{
						literal_entry[0] = asset->constantTable[i].literal[0] * 0.0875f;
						literal_entry[1] = asset->constantTable[i].literal[1] * 0.165f;
						literal_entry[2] = asset->constantTable[i].literal[2] * 1.4f;
						literal_entry[3] = asset->constantTable[i].literal[3] * 3.2f;
					}
					else
					{
						literal_entry[0] = asset->constantTable[i].literal[0];
						literal_entry[1] = asset->constantTable[i].literal[1];
						literal_entry[2] = asset->constantTable[i].literal[2];
						literal_entry[3] = asset->constantTable[i].literal[3];
					}
					table["literal"] = literal_entry;

					constant_table[constant_table.size()] = table;
				}

#define CONSTANT_TABLE_ADD_IF_NOT_FOUND(CONST_NAME, CONST_HASH, LITERAL_1, LITERAL_2, LITERAL_3, LITERAL_4) \
				bool has_table = false; \
				for (std::size_t i = 0; i < constant_table.size(); i++) \
				{ \
					if (constant_table[i]["name"] == CONST_NAME) \
					{ \
						has_table = true; \
					} \
				} \
				if (!has_table) \
				{ \
					ordered_json table; \
					table["name"] = CONST_NAME; \
					table["nameHash"] = CONST_HASH; \
					nlohmann::json literal_entry; \
					literal_entry[0] = LITERAL_1; \
					literal_entry[1] = LITERAL_2; \
					literal_entry[2] = LITERAL_3; \
					literal_entry[3] = LITERAL_4; \
					table["literal"] = literal_entry; \
					constant_table[constant_table.size()] = table; \
				} \

				if (h1_techset.find("_flag_") != std::string::npos)
				{
					CONSTANT_TABLE_ADD_IF_NOT_FOUND("flagParms", 2292903761, 1.0f, 0.0f, 0.0f, 0.0f);
				}

				if (h1_techset.find("_cso_") != std::string::npos)
				{
					CONSTANT_TABLE_ADD_IF_NOT_FOUND("hdrColorParm", 3379990750, 20.0f, 0.0f, 0.0f, 0.0f);
				}

				if (h1_techset.find("shadowcaster") != std::string::npos)
				{
					CONSTANT_TABLE_ADD_IF_NOT_FOUND("uvScale", 3809220315, 1.0f, 1.0f, 0.0f, 0.0f);
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
						image["image"] = "default";
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

					image["semantic"] = asset->maps[i].semantic; // convert? ( should be the same )
					image["samplerState"] = asset->maps[i].sampleState; // convert? ( should be fine )
					image["lastCharacter"] = asset->maps[i].secondLastCharacter;
					image["firstCharacter"] = asset->maps[i].firstCharacter;
					image["typeHash"] = asset->maps[i].typeHash;

					// add image data to material
					material_images.push_back(image);
				}

				// fix for certain techniques
				if (h1_techset.find("_lmpb_") != std::string::npos || h1_techset.find("_flag_") != std::string::npos)
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

				auto str = matdata.dump(4);

				matdata.clear();

				file.open("wb");
				file.write(str);
				file.close();
			}
		}
	}
}