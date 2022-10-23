#pragma once
#include <cstdint>
#include <d3d11.h>
#include <iphlpapi.h>

namespace ZoneTool
{
	namespace H2
	{
		typedef float vec_t;
		typedef vec_t vec2_t[2];
		typedef vec_t vec3_t[3];
		typedef vec_t vec4_t[4];

		template <std::size_t N>
		struct VecInternal
		{
			float data[N];
		};

		struct dummy
		{
		};

		enum scr_string_t : std::int32_t
		{
		};

		enum XAssetType
		{
			ASSET_TYPE_PHYSPRESET,
			ASSET_TYPE_PHYSCOLLMAP,
			ASSET_TYPE_PHYSWATERPRESET,
			ASSET_TYPE_PHYSWORLDMAP,
			ASSET_TYPE_PHYSCONSTRAINT,
			ASSET_TYPE_XANIM,
			ASSET_TYPE_XMODEL_SURFS,
			ASSET_TYPE_XMODEL,
			ASSET_TYPE_MATERIAL,
			ASSET_TYPE_COMPUTESHADER,
			ASSET_TYPE_VERTEXSHADER,
			ASSET_TYPE_HULLSHADER,
			ASSET_TYPE_DOMAINSHADER,
			ASSET_TYPE_PIXELSHADER,
			ASSET_TYPE_VERTEXDECL,
			ASSET_TYPE_TECHNIQUE_SET,
			ASSET_TYPE_IMAGE,
			ASSET_TYPE_SOUND,
			ASSET_TYPE_SOUNDSUBMIX,
			ASSET_TYPE_SOUND_CURVE,
			ASSET_TYPE_LPF_CURVE,
			ASSET_TYPE_REVERB_CURVE,
			ASSET_TYPE_SOUND_CONTEXT,
			ASSET_TYPE_LOADED_SOUND,
			ASSET_TYPE_COL_MAP_SP,
			ASSET_TYPE_COM_MAP,
			ASSET_TYPE_GLASS_MAP,
			ASSET_TYPE_AIPATHS,
			ASSET_TYPE_VEHICLE_TRACK,
			ASSET_TYPE_MAP_ENTS,
			ASSET_TYPE_FX_MAP,
			ASSET_TYPE_GFX_MAP,
			ASSET_TYPE_LIGHT_DEF,
			ASSET_TYPE_UI_MAP,
			ASSET_TYPE_MENUFILE,
			ASSET_TYPE_MENU,
			ASSET_TYPE_ANIMCLASS,
			ASSET_TYPE_LOCALIZE_ENTRY,
			ASSET_TYPE_ATTACHMENT,
			ASSET_TYPE_WEAPON,
			ASSET_TYPE_SNDDRIVERGLOBALS,
			ASSET_TYPE_FX,
			ASSET_TYPE_IMPACT_FX,
			ASSET_TYPE_SURFACE_FX,
			ASSET_TYPE_AITYPE,
			ASSET_TYPE_MPTYPE,
			ASSET_TYPE_CHARACTER,
			ASSET_TYPE_XMODELALIAS,
			ASSET_TYPE_RAWFILE,
			ASSET_TYPE_SCRIPTFILE,
			ASSET_TYPE_STRINGTABLE,
			ASSET_TYPE_LEADERBOARDDEF,
			ASSET_TYPE_VIRTUAL_LEADERBOARD,
			ASSET_TYPE_STRUCTUREDDATADEF,
			ASSET_TYPE_DDL,
			ASSET_TYPE_PROTO,
			ASSET_TYPE_TRACER,
			ASSET_TYPE_VEHICLE,
			ASSET_TYPE_ADDON_MAP_ENTS,
			ASSET_TYPE_NET_CONST_STRINGS,
			ASSET_TYPE_REVERB_PRESET,
			ASSET_TYPE_LUA_FILE,
			ASSET_TYPE_SCRIPTABLE,
			ASSET_TYPE_EQUIPMENT_SND_TABLE,
			ASSET_TYPE_VECTORFIELD,
			ASSET_TYPE_DOPPLER_PRESET,
			ASSET_TYPE_PARTICLE_SIM_ANIMATION,
			ASSET_TYPE_LASER,
			ASSET_TYPE_SKELETONSCRIPT,
			ASSET_TYPE_CLUT,
			ASSET_TYPE_TTF,
			ASSET_TYPE_COUNT
		};

		enum CSurfaceFlags : std::uint32_t
		{
			SURF_FLAG_DEFAULT = 0x00000000,
			SURF_FLAG_BARK = 0x00100000,
			SURF_FLAG_BRICK = 0x00200000,
			SURF_FLAG_CARPET = 0x00300000,
			SURF_FLAG_CLOTH = 0x00400000,
			SURF_FLAG_CONCRETE = 0x00500000,
			SURF_FLAG_DIRT = 0x00600000,
			SURF_FLAG_FLESH = 0x00700000,
			SURF_FLAG_FOLIAGE_DEBRIS = 0x00800000,
			SURF_FLAG_GLASS = 0x00900000,
			SURF_FLAG_GRASS = 0x00A00000,
			SURF_FLAG_GRAVEL = 0x00B00000,
			SURF_FLAG_ICE = 0x00C00000,
			SURF_FLAG_METAL_SOLID = 0x00D00000,
			SURF_FLAG_METAL_GRATE = 0x00E00000,
			SURF_FLAG_MUD = 0x00F00000,
			SURF_FLAG_PAPER = 0x01000000,
			SURF_FLAG_PLASTER = 0x01100000,
			SURF_FLAG_ROCK = 0x01200000,
			SURF_FLAG_SAND = 0x01300000,
			SURF_FLAG_SNOW = 0x01400000,
			SURF_FLAG_WATER_WAIST = 0x01500000,
			SURF_FLAG_WOOD_SOLID = 0x01600000,
			SURF_FLAG_ASPHALT = 0x01700000,
			SURF_FLAG_CERAMIC = 0x01800000,
			SURF_FLAG_PLASTIC_SOLID = 0x01900000,
			SURF_FLAG_RUBBER = 0x01A00000,
			SURF_FLAG_FRUIT = 0x01B00000,
			SURF_FLAG_PAINTEDMETAL = 0x01C00000,
			SURF_FLAG_RIOTSHIELD = 0x01D00000,
			SURF_FLAG_SLUSH = 0x01E00000,
			SURF_FLAG_ASPHALT_WET = 0x01F00000,
			SURF_FLAG_ASPHALT_DEBRIS = 0x02000000,
			SURF_FLAG_CONCRETE_WET = 0x02100000,
			SURF_FLAG_CONCRETE_DEBRIS = 0x02200000,
			SURF_FLAG_FOLIAGE_VEGETATION = 0x02300000,
			SURF_FLAG_FOLIAGE_LEAVES = 0x02400000,
			SURF_FLAG_GRASS_TALL = 0x02500000,
			SURF_FLAG_METAL_HOLLOW = 0x02600000,
			SURF_FLAG_METAL_VEHICLE = 0x02700000,
			SURF_FLAG_METAL_THIN = 0x02800000,
			SURF_FLAG_METAL_WET = 0x02900000,
			SURF_FLAG_METAL_DEBRIS = 0x02A00000,
			SURF_FLAG_PLASTIC_HOLLOW = 0x02B00000,
			SURF_FLAG_PLASTIC_TARP = 0x02C00000,
			SURF_FLAG_ROCK_WET = 0x02D00000,
			SURF_FLAG_ROCK_DEBRIS = 0x02E00000,
			SURF_FLAG_WATER_ANKLE = 0x02F00000,
			SURF_FLAG_WATER_KNEE = 0x03000000,
			SURF_FLAG_WATER_HOLLOW = 0x03100000,
			SURF_FLAG_WOOD_HOLLOW = 0x03200000,
			SURF_FLAG_WOOD_DEBRIS = 0x03300000,
			SURF_FLAG_CUSHION = 0x03400000,
			SURF_FLAG_CLIPMISSILE = 0x00000000,
			SURF_FLAG_AI_NOSIGHT = 0x00000000,
			SURF_FLAG_CLIPSHOT = 0x00000000,
			SURF_FLAG_PLAYERCLIP = 0x00000000,
			SURF_FLAG_MONSTERCLIP = 0x00000000,
			SURF_FLAG_AICLIPALLOWDEATH = 0x00000000,
			SURF_FLAG_VEHICLECLIP = 0x00000000,
			SURF_FLAG_ITEMCLIP = 0x00000000,
			SURF_FLAG_NODROP = 0x00000000,
			SURF_FLAG_NONSOLID = 0x00004000,
			SURF_FLAG_NOGRAPPLE = 0x00008000,
			SURF_FLAG_DETAIL = 0x00000000,
			SURF_FLAG_STRUCTURAL = 0x00000000,
			SURF_FLAG_PORTAL = 0x80000000,
			SURF_FLAG_CANSHOOTCLIP = 0x00000000,
			SURF_FLAG_ORIGIN = 0x00000000,
			SURF_FLAG_SKY = 0x00000004,
			SURF_FLAG_NOCASTSHADOW = 0x00040000,
			SURF_FLAG_PHYSICSGEOM = 0x00000000,
			SURF_FLAG_LIGHTPORTAL = 0x00000000,
			SURF_FLAG_OUTDOORBOUNDS = 0x00000000,
			SURF_FLAG_SLICK = 0x00000002,
			SURF_FLAG_NOIMPACT = 0x00000010,
			SURF_FLAG_NOMARKS = 0x00000020,
			SURF_FLAG_NOPENETRATE = 0x00000100,
			SURF_FLAG_LADDER = 0x00000008,
			SURF_FLAG_NODAMAGE = 0x00000001,
			SURF_FLAG_MANTLEON = 0x04000000,
			SURF_FLAG_MANTLEOVER = 0x08000000,
			SURF_FLAG_STAIRS = 0x00000200,
			SURF_FLAG_SOFT = 0x00001000,
			SURF_FLAG_NOSTEPS = 0x00002000,
			SURF_FLAG_NODRAW = 0x00000080,
			SURF_FLAG_NOLIGHTMAP = 0x00000400,
			SURF_FLAG_NODLIGHT = 0x00020000,
			SURF_FLAG_TRANSSORT = 0x00080000,
		};

		struct FxEffectDef;

		struct Bounds
		{
			vec3_t midPoint;
			vec3_t halfSize;
		};

		struct PhysPreset
		{
			const std::uint64_t name;
			char __pad0[32];
			const std::uint64_t sndAliasPrefix;
			char __pad1[48];
		}; static_assert(sizeof(PhysPreset) == 0x60);

		struct dmMeshNode_array_t
		{
			char __pad0[16];
		};

		struct dmMeshTriangle
		{
			char __pad0[32];
		};

		struct dmMeshData
		{
			std::uint64_t meshNodes;
			std::uint64_t vec4_array0;
			std::uint64_t meshTriangles;
			char __pad0[36];
			unsigned int count0;
			unsigned int count1;
			unsigned int count2;
			char __pad1[8];
		}; static_assert(sizeof(dmMeshData) == 0x50);

		struct dmSubEdge
		{
			int value;
		};

		struct dmPolytopeData
		{
			std::uint64_t vec4_array0;
			std::uint64_t vec4_array1;
			std::uint64_t uint16_array0;
			std::uint64_t uint16_array1;
			std::uint64_t edges;
			std::uint64_t uint8_array0;
			char __pad0[12];
			unsigned int count0;
			unsigned int count1;
			unsigned int count2;
			char __pad1[40];
		}; static_assert(sizeof(dmPolytopeData) == 0x70);

		struct PhysGeomInfo
		{
			std::uint64_t data;
		};

		struct PhysMass
		{
			float centerOfMass[3];
			float momentsOfInertia[3];
			float productsOfInertia[3];
		};

		struct PhysCollmap
		{
			const std::uint64_t name;
			unsigned int count;
			std::uint64_t geoms;
			PhysMass mass;
			Bounds bounds;
		}; static_assert(sizeof(PhysCollmap) == 0x58);

		struct PhysWaterPreset
		{
			const std::uint64_t name;
			char __pad0[64];
			std::uint64_t fx0;
			std::uint64_t fx1;
			std::uint64_t fx2;
			std::uint64_t fx3;
			std::uint64_t fx4;
			std::uint64_t fx5;
			std::uint64_t fx6;
		}; static_assert(sizeof(PhysWaterPreset) == 0x80);

		struct PhysWaterVolumeDef
		{
			std::uint64_t physWaterPreset;
			char __pad0[12];
			scr_string_t string;
			char __pad1[8];
		}; static_assert(sizeof(PhysWaterVolumeDef) == 0x20);
		static_assert(offsetof(PhysWaterVolumeDef, string) == 20);

		struct PhysBrushModel
		{
			char __pad0[8];
		};

		struct PhysWorld
		{
			const std::uint64_t name;
			std::uint64_t models;
			std::uint64_t polytopeDatas;
			std::uint64_t meshDatas;
			std::uint64_t waterVolumes;
			unsigned int modelsCount;
			unsigned int polytopeDatasCount;
			unsigned int meshDatasCount;
			unsigned int waterVolumesCount;
		}; static_assert(sizeof(PhysWorld) == 0x38);

		struct PhysConstraint
		{
			const std::uint64_t name;
			char __pad0[32];
		}; static_assert(sizeof(PhysConstraint) == 0x28);

		struct Packed128
		{
			std::uint64_t p0;
			std::uint64_t p1;
		};

		union GfxDrawSurf
		{
			//GfxDrawSurfFields fields;
			Packed128 packed;
		};

		struct GfxComputeShaderLoadDef
		{
			std::uint64_t program;
			unsigned int programSize;
			char __pad[4];
		};

		struct ComputeShaderProgram
		{
			std::uint64_t cs;
			GfxComputeShaderLoadDef loadDef;
		};

		struct ComputeShader
		{
			const std::uint64_t name;
			ComputeShaderProgram prog;
		}; static_assert(sizeof(ComputeShader) == 0x20);

		struct GfxVertexShaderLoadDef
		{
			std::uint64_t program;
			unsigned int programSize;
			unsigned int microCodeCrc;
		};

		struct MaterialVertexShaderProgram
		{
			std::uint64_t vs;
			GfxVertexShaderLoadDef loadDef;
		};

		struct MaterialVertexShader
		{
			const std::uint64_t name;
			MaterialVertexShaderProgram prog;
		}; static_assert(sizeof(MaterialVertexShader) == 0x20);

		struct GfxPixelShaderLoadDef
		{
			std::uint64_t program;
			unsigned int programSize;
			unsigned int microCodeCrc;
		};

		struct MaterialPixelShaderProgram
		{
			std::uint64_t ps;
			GfxPixelShaderLoadDef loadDef;
		};

		struct MaterialPixelShader
		{
			const std::uint64_t name;
			MaterialPixelShaderProgram prog;
		}; static_assert(sizeof(MaterialPixelShader) == 0x20);

		struct GfxHullShaderLoadDef
		{
			std::uint64_t program;
			unsigned int programSize;
			char __pad[4];
		};

		struct MaterialHullShaderProgram
		{
			std::uint64_t hs;
			GfxHullShaderLoadDef loadDef;
		};

		struct MaterialHullShader
		{
			const std::uint64_t name;
			MaterialHullShaderProgram prog;
		}; static_assert(sizeof(MaterialHullShader) == 0x20);

		struct GfxDomainShaderLoadDef
		{
			std::uint64_t program;
			unsigned int programSize;
			char __pad[4];
		};

		struct MaterialDomainShaderProgram
		{
			std::uint64_t ds;
			GfxDomainShaderLoadDef loadDef;
		};

		struct MaterialDomainShader
		{
			const std::uint64_t name;
			MaterialDomainShaderProgram prog;
		}; static_assert(sizeof(MaterialDomainShader) == 0x20);

		struct MaterialArgumentCodeConst
		{
			unsigned short index;
			unsigned char firstRow;
			unsigned char rowCount;
		};

		union MaterialArgumentDef
		{
			const std::uint64_t literalConst;
			MaterialArgumentCodeConst codeConst;
			unsigned int codeSampler;
			unsigned int nameHash;
		};

		struct MaterialShaderArgument
		{
			unsigned char type;
			unsigned char shader;
			unsigned short dest;
			MaterialArgumentDef u;
		}; static_assert(sizeof(MaterialShaderArgument) == 0x10);

		struct MaterialStreamRouting
		{
			unsigned char source;
			unsigned char dest;
			unsigned char mask;
		};

		struct MaterialVertexStreamRouting
		{
			MaterialStreamRouting data[32];
			std::uint64_t decl[250];
		};

		struct MaterialVertexDeclaration
		{
			const std::uint64_t name;
			unsigned char streamCount;
			bool hasOptionalSource;
			MaterialVertexStreamRouting routing;
		}; static_assert(sizeof(MaterialVertexDeclaration) == 0x840);

		struct MaterialPass
		{
			std::uint64_t vertexShader;
			std::uint64_t vertexDecl;
			std::uint64_t hullShader;
			std::uint64_t domainShader;
			std::uint64_t pixelShader;
			unsigned char pixelOutputMask;
			unsigned char perPrimArgCount;
			unsigned char perObjArgCount;
			unsigned char stableArgCount;
			unsigned short perPrimArgSize;
			unsigned short perObjArgSize;
			unsigned short stableArgSize;
			unsigned short zone;
			unsigned char perPrimConstantBuffer;
			unsigned char perObjConstantBuffer;
			unsigned char stableConstantBuffer;
			unsigned int customBufferFlags;
			unsigned char customSamplerFlags;
			unsigned char precompiledIndex;
			unsigned char stageConfig;
			std::uint64_t args;
		};

		struct MaterialTechniqueHeader
		{
			const std::uint64_t name;
			unsigned short flags;
			unsigned short passCount;
		};

		struct MaterialTechnique
		{
			//const std::uint64_t name;
			//unsigned short flags;
			//unsigned short passCount;
			MaterialTechniqueHeader hdr;
			MaterialPass passArray[1];
		};

		struct MaterialTechniqueSet
		{
			const std::uint64_t name;
			unsigned short flags;
			unsigned char worldVertFormat;
			unsigned char preDisplacementOnlyCount;
			std::uint64_t techniques[252];
		}; static_assert(sizeof(MaterialTechniqueSet) == 0x7F0);

		static_assert(offsetof(MaterialTechniqueSet, techniques) == 16);

		struct GfxImage;

		struct WaterWritable
		{
			float floatTime;
		};

		struct water_t
		{
			WaterWritable writable;
			std::uint64_t H0X;
			std::uint64_t H0Y;
			std::uint64_t wTerm;
			int M;
			int N;
			float Lx;
			float Lz;
			float gravity;
			float windvel;
			float winddir[2];
			float amplitude;
			std::uint64_t image;
			std::uint64_t stagingImage;
		};

		union MaterialTextureDefInfo
		{
			std::uint64_t image;
			std::uint64_t water;
		};

		struct MaterialTextureDef
		{
			unsigned int nameHash;
			char nameStart;
			char nameEnd;
			unsigned char samplerState;
			unsigned char semantic;
			MaterialTextureDefInfo u;
		}; static_assert(sizeof(MaterialTextureDef) == 0x10);

		struct MaterialConstantDef
		{
			unsigned int nameHash;
			char name[12];
			float literal[4];
		}; static_assert(sizeof(MaterialConstantDef) == 0x20);

		struct GfxStateBits
		{
			unsigned int loadBits[6]; // loadbits[3], blendstatebits[3]
			unsigned short zone;
			unsigned char depthStencilState[10];
			unsigned char blendState;
			unsigned char rasterizerState;
		}; static_assert(sizeof(GfxStateBits) == 0x28);

		struct MaterialConstantBufferDef
		{
			unsigned int vsDataSize;
			unsigned int hsDataSize;
			unsigned int dsDataSize;
			unsigned int psDataSize;
			unsigned int vsOffsetDataSize;
			unsigned int hsOffsetDataSize;
			unsigned int dsOffsetDataSize;
			unsigned int psOffsetDataSize;
			std::uint64_t vsData;
			std::uint64_t hsData;
			std::uint64_t dsData;
			std::uint64_t psData;
			std::uint64_t vsOffsetData;
			std::uint64_t hsOffsetData;
			std::uint64_t dsOffsetData;
			std::uint64_t psOffsetData;
			std::uint64_t vsConstantBuffer;
			std::uint64_t hsConstantBuffer;
			std::uint64_t dsConstantBuffer;
			std::uint64_t psConstantBuffer;
		};

		enum SurfaceTypeBits : std::uint64_t
		{
			SURFTYPE_BITS_NONE = 0x0,
			SURFTYPE_BITS_DEFAULT = 0x1,
			SURFTYPE_BITS_BARK = 0x2,
			SURFTYPE_BITS_CARPET = 0x4,
			SURFTYPE_BITS_CLOTH = 0x8,
			SURFTYPE_BITS_CONCRETE = 0x10,
			SURFTYPE_BITS_DIRT = 0x20,
			SURFTYPE_BITS_FLESH = 0x40,
			SURFTYPE_BITS_FOLIAGE_DEBRIS = 0x80,
			SURFTYPE_BITS_GLASS = 0x100,
			SURFTYPE_BITS_GRASS = 0x200,
			SURFTYPE_BITS_GRAVEL = 0x400,
			SURFTYPE_BITS_ICE = 0x800,
			SURFTYPE_BITS_METAL_SOLID = 0x1000,
			SURFTYPE_BITS_METAL_GRATE = 0x2000,
			SURFTYPE_BITS_MUD = 0x4000,
			SURFTYPE_BITS_PAPER = 0x8000,
			SURFTYPE_BITS_PLASTER = 0x10000,
			SURFTYPE_BITS_ROCK = 0x20000,
			SURFTYPE_BITS_SAND = 0x40000,
			SURFTYPE_BITS_SNOW = 0x80000,
			SURFTYPE_BITS_WATER_WAIST = 0x100000,
			SURFTYPE_BITS_WOOD_SOLID = 0x200000,
			SURFTYPE_BITS_ASPHALT = 0x400000,
			SURFTYPE_BITS_CERAMIC = 0x800000,
			SURFTYPE_BITS_PLASTIC_SOLID = 0x1000000,
			SURFTYPE_BITS_RUBBER = 0x2000000,
			SURFTYPE_BITS_FRUIT = 0x4000000,
			SURFTYPE_BITS_PAINTEDMETAL = 0x8000000,
			SURFTYPE_BITS_RIOTSHIELD = 0x10000000,
			SURFTYPE_BITS_SLUSH = 0x20000000,
			SURFTYPE_BITS_ASPHALT_WET = 0x40000000,
			SURFTYPE_BITS_ASPHALT_DEBRIS = 0x80000000,
			SURFTYPE_BITS_CONCRETE_WET = 0x100000000,
			SURFTYPE_BITS_CONCRETE_DEBRIS = 0x200000000,
			SURFTYPE_BITS_FOLIAGE_VEGETATION = 0x400000000,
			SURFTYPE_BITS_FOLIAGE_LEAVES = 0x800000000,
			SURFTYPE_BITS_GRASS_TALL = 0x1000000000,
			SURFTYPE_BITS_METAL_HOLLOW = 0x2000000000,
			SURFTYPE_BITS_METAL_VEHICLE = 0x4000000000,
			SURFTYPE_BITS_METAL_THIN = 0x8000000000,
			SURFTYPE_BITS_METAL_WET = 0x10000000000,
			SURFTYPE_BITS_METAL_DEBRIS = 0x20000000000,
			SURFTYPE_BITS_PLASTIC_HOLLOW = 0x40000000000,
			SURFTYPE_BITS_PLASTIC_TARP = 0x80000000000,
			SURFTYPE_BITS_ROCK_WET = 0x100000000000,
			SURFTYPE_BITS_ROCK_DEBRIS = 0x200000000000,
			SURFTYPE_BITS_WATER_ANKLE = 0x400000000000,
			SURFTYPE_BITS_WATER_KNEE = 0x800000000000,
			SURFTYPE_BITS_WOOD_HOLLOW = 0x1000000000000,
			SURFTYPE_BITS_WOOD_WET = 0x2000000000000,
			SURFTYPE_BITS_WOOD_DEBRIS = 0x4000000000000,
			SURFTYPE_BITS_CUSHION = 0x8000000000000,
		};

		struct MaterialInfo
		{
			const std::uint64_t name;
			unsigned char gameFlags;
			unsigned char sortKey;
			unsigned char textureAtlasRowCount;
			unsigned char textureAtlasColumnCount;
			unsigned char textureAtlasFrameBlend;
			unsigned char textureAtlasAsArray;
			unsigned char renderFlags;
			GfxDrawSurf drawSurf;
			SurfaceTypeBits surfaceTypeBits;
			unsigned int hashIndex;
		}; static_assert(sizeof(MaterialInfo) == 48);

		struct Material
		{
			union
			{
				const std::uint64_t name;
				MaterialInfo info;
			};
			unsigned char stateBitsEntry[252];
			unsigned char textureCount;
			unsigned char constantCount;
			unsigned char stateBitsCount;
			unsigned char stateFlags;
			unsigned char cameraRegion;
			unsigned char materialType;
			unsigned char layerCount;
			unsigned char assetFlags;
			std::uint64_t techniqueSet;
			std::uint64_t textureTable;
			std::uint64_t constantTable;
			std::uint64_t stateBitsTable;
			unsigned char constantBufferIndex[252];
			char __pad0[4];
			std::uint64_t constantBufferTable;
			unsigned char constantBufferCount;
			const std::uint64_t subMaterials;
		}; static_assert(sizeof(Material) == 0x270);

		static_assert(offsetof(Material, textureCount) == 0x12C);
		static_assert(offsetof(Material, techniqueSet) == 0x138);
		static_assert(offsetof(Material, textureTable) == 0x140);
		static_assert(offsetof(Material, constantTable) == 0x148);
		static_assert(offsetof(Material, stateBitsTable) == 0x150);
		static_assert(offsetof(Material, constantBufferTable) == 0x258);
		static_assert(offsetof(Material, constantBufferCount) == 0x260);
		static_assert(offsetof(Material, subMaterials) == 0x268);

		struct GfxImageLoadDef
		{
			char levelCount;
			char numElements;
			char pad[2];
			int flags;
			int format;
			int resourceSize;
			char data[1];
		};

		struct GfxTexture
		{
			union
			{
				std::uint64_t linemap;
				std::uint64_t map;
				std::uint64_t volmap;
				std::uint64_t cubemap;
				std::uint64_t loadDef;
			};
			std::uint64_t shaderView;
			std::uint64_t shaderViewAlternate;
		};

		struct Picmip
		{
			unsigned char platform[2];
		};

		struct GfxImageStreamData
		{
			unsigned short width;
			unsigned short height;
			unsigned int pixelSize;
		};

		enum MapType : std::uint8_t
		{
			MAPTYPE_NONE = 0x0,
			MAPTYPE_INVALID1 = 0x1,
			MAPTYPE_1D = 0x2,
			MAPTYPE_2D = 0x3,
			MAPTYPE_3D = 0x4,
			MAPTYPE_CUBE = 0x5,
			MAPTYPE_ARRAY = 0x6,
			MAPTYPE_COUNT = 0x7,
		};

		struct GfxImage
		{
			GfxTexture texture;
			DXGI_FORMAT imageFormat;
			MapType mapType;
			unsigned char sematic;
			unsigned char category;
			unsigned char flags;
			Picmip picmip;
			char __pad0[2];
			unsigned int dataLen1;
			unsigned int dataLen2;
			unsigned short width;
			unsigned short height;
			unsigned short depth;
			unsigned short numElements;
			unsigned char levelCount;
			unsigned char streamed;
			char __pad1[2];
			std::uint64_t pixelData;
			GfxImageStreamData streams[4];
			const std::uint64_t name;
		}; static_assert(sizeof(GfxImage) == 0x68);

		struct GfxLightImage
		{
			std::uint64_t image;
			unsigned char samplerState;
		};

		struct GfxLightDef
		{
			const std::uint64_t name;
			GfxLightImage attenuation;
			GfxLightImage cucoloris;
			int lmapLookupStart;
		}; static_assert(sizeof(GfxLightDef) == 0x30);

		struct GfxColorFloat
		{
			float array[4];
		};

		enum snd_alias_type_t : std::int8_t
		{
			SAT_UNKNOWN = 0x0,
			SAT_LOADED = 0x1,
			SAT_STREAMED = 0x2,
			SAT_PRIMED = 0x3,
			SAT_COUNT = 0x4,
		};

		struct StreamFileNameRaw
		{
			const std::uint64_t dir;
			const std::uint64_t name;
		};

		struct StreamFileNamePacked
		{
			unsigned __int64 offset;
			unsigned __int64 length;
		};

		union StreamFileInfo
		{
			StreamFileNameRaw raw;
			StreamFileNamePacked packed;
		};

		struct StreamFileName
		{
			bool isLocalized;
			bool isStreamed;
			unsigned short fileIndex;
			StreamFileInfo info;
		};

		struct StreamedSound
		{
			StreamFileName filename;
			unsigned int totalMsec;
		};

		struct LoadedSoundInfo
		{
			std::uint64_t data;
			unsigned int sampleRate;
			unsigned int dataByteCount;
			unsigned int numSamples;
			char channels;
			char numBits;
			char blockAlign;
			short format;
			int loadedSize;
		}; static_assert(sizeof(LoadedSoundInfo) == 0x20);

		struct LoadedSound
		{
			const std::uint64_t name;
			StreamFileName filename;
			LoadedSoundInfo info;
		}; static_assert(sizeof(LoadedSound) == 0x40);

		struct PrimedSound
		{
			std::uint64_t loadedPart;
			StreamFileName streamedPart;
			int dataOffset; // not sure
			int totalSize; // not sure
		}; static_assert(sizeof(PrimedSound) == 0x28);

		union SoundFileRef
		{
			std::uint64_t loadSnd;
			StreamedSound streamSnd;
			PrimedSound primedSnd;
		};

		struct SoundFile
		{
			snd_alias_type_t type;
			bool exists;
			SoundFileRef u;
		};

		struct SndContext
		{
			const std::uint64_t name;
			char __pad0[8];
		};

		struct SndCurve
		{
			bool isDefault;
			union
			{
				const std::uint64_t filename;
				const std::uint64_t name;
			};
			unsigned short knotCount;
			float knots[16][2];
		}; static_assert(sizeof(SndCurve) == 0x98);

		struct SpeakerLevels
		{
			char speaker;
			char numLevels;
			float levels[2];
		};

		struct ChannelMap
		{
			int speakerCount;
			SpeakerLevels speakers[6];
		};

		struct SpeakerMap
		{
			bool isDefault;
			const std::uint64_t name;
			int unknown;
			ChannelMap channelMaps[2][2];
		}; static_assert(sizeof(SpeakerMap) == 0x148);

		struct DopplerPreset
		{
			const std::uint64_t name;
			float speedOfSound;
			float playerVelocityScale;
			float minPitch;
			float maxPitch;
			float smoothing;
		}; static_assert(sizeof(DopplerPreset) == 0x20);

		union SoundAliasFlags
		{
			struct _
			{
				unsigned int looping : 1;
				unsigned int isMaster : 1;
				unsigned int isSlave : 1;
				unsigned int fullDryLevel : 1;
				unsigned int noWetLevel : 1;
				unsigned int is3d : 1;
				unsigned int type : 2;
			};
			unsigned int intValue;
		};

		struct snd_alias_t
		{
			const std::uint64_t aliasName;
			const std::uint64_t subtitle;
			const std::uint64_t secondaryAliasName;
			const std::uint64_t chainAliasName;
			std::uint64_t soundFile;
			const std::uint64_t mixerGroup;
			short poly;
			short polyGlobal;
			char polyEntityType;
			char polyGlobalType;
			char dspBusIndex;
			char priority;
			char __pad0[12]; // unknown
			float volMin;
			float volMax;
			short volModIndex;
			//char __padding0[2]; // padding
			float pitchMin;
			float pitchMax;
			float distMin;
			float distMax;
			float velocityMin;
			int flags;
			char masterPriority;
			float masterPercentage;
			float slavePercentage;
			char playbackPercentage;
			//char __padding1[3]; // padding
			float probability;
			char u1; // value: 0-4
			//char __padding2[3]; // padding
			std::uint64_t sndContext;
			unsigned char sequence;
			//char __padding3[3]; // padding
			float lfePercentage;
			float centerPercentage;
			int startDelay;
			std::uint64_t sndCurve;
			char __pad1[8];
			std::uint64_t lpfCurve;
			std::uint64_t hpfCurve;
			std::uint64_t reverbSendCurve;
			std::uint64_t speakerMap;
			float reverbWetMixOverride;
			float u4;
			float smartPanDistance2d;
			float smartPanDistance3d;
			float smartPanAttenuation3d;
			char __pad2[4]; // unknown
			short stereo3dAngle;
			//char __padding4[2]; // padding
			float stereo3dStart;
			float stereo3dEnd;
			unsigned char allowDoppler;
			//char __padding5[3]; // padding
			std::uint64_t dopplerPreset;
			float u6;
			//char __padding6[4]; // padding
		};

		static_assert(sizeof(snd_alias_t) == 256);

		struct snd_alias_list_t
		{
			union
			{
				const std::uint64_t aliasName;
				const std::uint64_t name;
			};
			std::uint64_t head;
			std::uint64_t unk;
			unsigned char count;
			unsigned char unkCount;
			char __pad0[6];
		};

		struct LocalizeEntry
		{
			const std::uint64_t value;
			const std::uint64_t name;
		}; static_assert(sizeof(LocalizeEntry) == 0x10);

		struct TriggerModel
		{
			int contents;
			unsigned short hullCount;
			unsigned short firstHull;
		};

		struct TriggerHull
		{
			Bounds bounds;
			int contents;
			unsigned short slabCount;
			unsigned short firstSlab;
		};

		struct TriggerSlab
		{
			float dir[3];
			float midPoint;
			float halfSize;
		};

		struct MapTriggers
		{
			unsigned int count;
			std::uint64_t models;
			unsigned int hullCount;
			std::uint64_t hulls;
			unsigned int slabCount;
			std::uint64_t slabs;
		};

		struct ClientTriggerAabbNode
		{
			Bounds bounds;
			unsigned short firstChild;
			unsigned short childCount;
		};

		struct ClientTriggers
		{
			MapTriggers trigger;
			unsigned short numClientTriggerNodes;
			std::uint64_t clientTriggerAabbTree;
			unsigned int triggerStringLength;
			std::uint64_t triggerString;
			std::uint64_t unk0;
			std::uint64_t unk1;
			std::uint64_t unk2;
			std::uint64_t triggerType;
			std::uint64_t origins;
			std::uint64_t scriptDelay;
			std::uint64_t unk3;
			std::uint64_t unk4;
			std::uint64_t unk5;
			std::uint64_t unk6;
			std::uint64_t unk7;
			std::uint64_t unk8;
		}; static_assert(sizeof(ClientTriggers) == 0xB0);

		struct ClientTriggerBlendNode
		{
			float pointA[3];
			float pointB[3];
			unsigned short triggerA;
			unsigned short triggerB;
		};

		struct ClientTriggerBlend
		{
			unsigned short numClientTriggerBlendNodes;
			std::uint64_t blendNodes;
		};

		struct SpawnPointEntityRecord
		{
			unsigned short index;
			scr_string_t name;
			scr_string_t target;
			scr_string_t script_noteworthy;
			scr_string_t unknown;
			float origin[3];
			float angles[3];
		};

		struct SpawnPointRecordList
		{
			unsigned short spawnsCount;
			std::uint64_t spawns;
		};

		struct SplinePointEntityRecord
		{
			int splineId;
			int splineNodeId;
			std::uint64_t splineNodeLabel;
			float splineNodeTension;
			float origin[3];
			float corridorDims[2];
			float tangent[3];
			float distToNextNode;
			std::uint64_t positionCubic;
			std::uint64_t tangentQuadratic;
		};

		struct SplinePointRecordList
		{
			unsigned short splinePointCount;
			float splineLength;
			std::uint64_t splinePoints;
		};

		struct SplineRecordList
		{
			unsigned short splineCount;
			std::uint64_t splines;
		};

		struct MapEnts
		{
			const std::uint64_t name;
			std::uint64_t entityString;
			int numEntityChars;
			MapTriggers trigger;
			ClientTriggers clientTrigger;
			ClientTriggerBlend clientTriggerBlend;
			SpawnPointRecordList spawnList;
			SplineRecordList splineList;
		}; static_assert(sizeof(MapEnts) == 0x128);

		struct AddonMapEnts
		{
			const std::uint64_t name;
			std::uint64_t entityString;
			int numEntityChars;
			MapTriggers trigger;
			std::uint64_t info;
			unsigned int numSubModels;
			std::uint64_t cmodels;
			std::uint64_t models;
			char __pad0[0x20];
		};

		static_assert(sizeof(AddonMapEnts) == 136);

		struct RawFile
		{
			const std::uint64_t name;
			int compressedLen;
			int len;
			const std::uint64_t buffer;
		}; static_assert(sizeof(RawFile) == 0x18);

		struct ScriptFile
		{
			const std::uint64_t name;
			int compressedLen;
			int len;
			int bytecodeLen;
			const std::uint64_t buffer;
			std::uint64_t bytecode;
		}; static_assert(sizeof(ScriptFile) == 0x28);

		struct StringTableCell
		{
			const std::uint64_t string;
			int hash;
		};

		struct StringTable
		{
			const std::uint64_t name;
			int columnCount;
			int rowCount;
			std::uint64_t values;
		}; static_assert(sizeof(StringTable) == 0x18);

		struct StructuredDataEnumEntry
		{
			scr_string_t string;
			unsigned short index;
		};

		struct StructuredDataEnum
		{
			int entryCount;
			int reservedEntryCount;
			std::uint64_t entries;
		};

		enum StructuredDataTypeCategory
		{
			DATA_INT = 0x0,
			DATA_BYTE = 0x1,
			DATA_BOOL = 0x2,
			DATA_STRING = 0x3,
			DATA_ENUM = 0x4,
			DATA_STRUCT = 0x5,
			DATA_INDEXED_ARRAY = 0x6,
			DATA_ENUM_ARRAY = 0x7,
			DATA_FLOAT = 0x8,
			DATA_SHORT = 0x9,
			DATA_COUNT = 0xA,
		};

		union StructuredDataTypeUnion
		{
			unsigned int stringDataLength;
			int enumIndex;
			int structIndex;
			int indexedArrayIndex;
			int enumedArrayIndex;
			int index;
		};

		struct StructuredDataType
		{
			StructuredDataTypeCategory type;
			StructuredDataTypeUnion u;
		};

		enum StructuredDataValidationType
		{
			VALIDATION_NONE = 0x0,
		};

		struct StructuredDataStructProperty
		{
			scr_string_t name;
			StructuredDataType type;
			unsigned int offset;
			StructuredDataValidationType validation;
		};

		struct StructuredDataStruct
		{
			int propertyCount;
			std::uint64_t properties;
			int size;
			unsigned int bitOffset;
		};

		struct StructuredDataIndexedArray
		{
			int arraySize;
			StructuredDataType elementType;
			unsigned int elementSize;
		};

		struct StructuredDataEnumedArray
		{
			int enumIndex;
			StructuredDataType elementType;
			unsigned int elementSize;
		};

		struct StructuredDataDef
		{
			int version;
			unsigned int formatChecksum;
			int enumCount;
			std::uint64_t enums;
			int structCount;
			std::uint64_t structs;
			int indexedArrayCount;
			std::uint64_t indexedArrays;
			int enumedArrayCount;
			std::uint64_t enumedArrays;
			StructuredDataType rootType;
			unsigned int size;
		}; static_assert(sizeof(StructuredDataDef) == 0x58);

		struct StructuredDataDefSet
		{
			const std::uint64_t name;
			unsigned int defCount;
			std::uint64_t defs;
		}; static_assert(sizeof(StructuredDataDefSet) == 0x18);

		enum NetConstStringType
		{
		};

		enum NetConstStringSource
		{
		};

		struct NetConstStrings
		{
			const std::uint64_t name;
			NetConstStringType stringType;
			NetConstStringSource sourceType;
			unsigned int entryCount;
			const std::uint64_t stringList;
		}; static_assert(sizeof(NetConstStrings) == 0x20);

		struct LuaFile
		{
			const std::uint64_t name;
			int len;
			char strippingType;
			const std::uint64_t buffer;
		}; static_assert(sizeof(LuaFile) == 0x18);

		struct TTFDef
		{
			const std::uint64_t name;
			int fileLen;
			const std::uint64_t file;
			std::uint64_t ftFace;
		}; static_assert(sizeof(TTFDef) == 0x20);

		struct FxParticleSimAnimationHeader
		{
			float playbackRate;
			float duration;
			unsigned int frameCount;
			float minX;
			float minY;
			float minZ;
			float boundsXDelta;
			float boundsYDelta;
			float boundsZDelta;
			float maxWidth;
			float maxHeight;
			unsigned int colorTableSize;
			unsigned int particleDataCount;
			bool evalVisStatePerParticle;
			bool sortParticlesAtRuntime;
		};

		struct FxParticleSimAnimationParticleData
		{
			unsigned short xNormalizedPos;
			unsigned short yNormalizedPos;
			unsigned short zNormalizedPos;
			unsigned short xNormalizedWidth;
			unsigned short yNormalizedHeight;
			unsigned short orientation;
			unsigned short lifetime;
			unsigned short particleID;
			unsigned short xNormalizedPosNextFrame;
			unsigned short yNormalizedPosNextFrame;
			unsigned short zNormalizedPosNextFrame;
			unsigned short xNormalizedWidthNextFrame;
			unsigned short yNormalizedHeightNextFrame;
			short orientationDelta;
			unsigned short colorTableIndex;
			unsigned short nextColorTableIndex;
		};

		struct FxParticleSimAnimationFrame
		{
			unsigned int particleDataOffset;
			unsigned int numActiveParticles;
		};

		struct FxParticleSimAnimation
		{
			const std::uint64_t name;
			std::uint64_t material;
			FxParticleSimAnimationHeader header;
			std::uint64_t particleData;
			std::uint64_t frames;
			std::uint64_t colorTable;
		};

		enum FxElemType : std::uint8_t
		{
			FX_ELEM_TYPE_SPRITE_BILLBOARD = 0,
			FX_ELEM_TYPE_SPRITE_ORIENTED = 1,
			FX_ELEM_TYPE_SPRITE_ROTATED = 2,
			FX_ELEM_TYPE_TAIL = 3,
			FX_ELEM_TYPE_LINE = 4,
			FX_ELEM_TYPE_TRAIL = 5,
			FX_ELEM_TYPE_FLARE = 6,
			FX_ELEM_TYPE_PARTICLE_SIM_ANIMATION = 7,
			FX_ELEM_TYPE_CLOUD = 8,
			FX_ELEM_TYPE_SPARK_CLOUD = 9,
			FX_ELEM_TYPE_SPARK_FOUNTAIN = 10,
			FX_ELEM_TYPE_MODEL = 11,
			FX_ELEM_TYPE_OMNI_LIGHT = 12,
			FX_ELEM_TYPE_SPOT_LIGHT = 13,
			FX_ELEM_TYPE_SOUND = 14,
			FX_ELEM_TYPE_DECAL = 15,
			FX_ELEM_TYPE_RUNNER = 16,
			FX_ELEM_TYPE_VECTORFIELD = 17,
		};

		struct FxFloatRange
		{
			float base;
			float amplitude;
		};

		struct FxSpawnDefLooping
		{
			int intervalMsec;
			int count;
		};

		struct FxIntRange
		{
			int base;
			int amplitude;
		};

		struct FxSpawnDefOneShot
		{
			FxIntRange count;
		};

		union FxSpawnDef
		{
			FxSpawnDefLooping looping;
			FxSpawnDefOneShot oneShot;
		};

		struct FxElemAtlas
		{
			unsigned char behavior;
			unsigned char index;
			unsigned char fps;
			unsigned char loopCount;
			unsigned char colIndexBits;
			unsigned char rowIndexBits;
			short entryCount;
		};

		struct FxEffectDef;
		union FxEffectDefRef
		{
			std::uint64_t handle;
			const std::uint64_t name;
		};

		struct FxElemVec3Range
		{
			float base[3];
			float amplitude[3];
			float unk_vec[3];
		};

		struct FxElemVelStateInFrame
		{
			FxElemVec3Range velocity;
			FxElemVec3Range totalDelta;
		};

		struct FxElemVelStateSample
		{
			FxElemVelStateInFrame local;
			FxElemVelStateInFrame world;
		}; static_assert(sizeof(FxElemVelStateSample) == 144);

		struct FxElemVisualState
		{
			float color[4];
			float unlitHDRScale;
			float rotationDelta;
			float rotationTotal;
			float size[2];
			float scale;
			char __pad0[16];
		};

		struct FxElemVisStateSample
		{
			FxElemVisualState base;
			FxElemVisualState amplitude;
		}; static_assert(sizeof(FxElemVisStateSample) == 112);

		struct FxElemMarkVisuals
		{
			std::uint64_t materials[3];
		};

		struct XModel;
		union FxElemVisuals
		{
			const std::uint64_t anonymous;
			std::uint64_t material;
			std::uint64_t model;
			FxEffectDefRef effectDef;
			const std::uint64_t soundName;
			const std::uint64_t vectorFieldName;
			std::uint64_t lightDef;
			std::uint64_t particleSimAnimation;
		};

		union FxElemDefVisuals
		{
			std::uint64_t markArray;
			std::uint64_t array;
			FxElemVisuals instance;
		};

		struct FxTrailVertex
		{
			float pos[2];
			float normal[2];
			float texCoord[2];
			char __pad0[8];
		}; static_assert(sizeof(FxTrailVertex) == 32);

		struct FxTrailDef
		{
			int scrollTimeMsec;
			int repeatDist;
			float invSplitDist;
			float invSplitArcDist;
			float invSplitTime;
			char __pad0[12];
			int vertCount;
			std::uint64_t verts;
			int indCount;
			std::uint64_t inds;
		}; static_assert(sizeof(FxTrailDef) == 0x40);
		static_assert(offsetof(FxTrailDef, verts) == 40);
		static_assert(offsetof(FxTrailDef, inds) == 56);
		static_assert(offsetof(FxTrailDef, vertCount) == 32);
		static_assert(offsetof(FxTrailDef, indCount) == 48);

		struct FxSparkFountainDef
		{
			float gravity;
			float bounceFrac;
			float bounceRand;
			float sparkSpacing;
			float sparkLength;
			int sparkCount;
			float loopTime;
			float velMin;
			float velMax;
			float velConeFrac;
			float restSpeed;
			float boostTime;
			float boostFactor;
		}; static_assert(sizeof(FxSparkFountainDef) == 0x34);

		struct FxSpotLightDef
		{
			float fovInnerFraction;
			float startRadius;
			float endRadius;
			float brightness;
			float maxLength;
			int exponent;
			char __pad0[24];
		}; static_assert(sizeof(FxSpotLightDef) == 0x30);

		struct FxOmniLightDef
		{
			char __pad0[16];
		}; static_assert(sizeof(FxOmniLightDef) == 0x10);

		struct FxFlareDef
		{
			float position;
			int angularRotCount;
			int flags;
			FxFloatRange depthScaleRange;
			FxFloatRange depthScaleValue;
			FxFloatRange radialRot;
			FxFloatRange radialScaleX;
			FxFloatRange radialScaleY;
			float dir[3];
			int intensityXIntervalCount;
			int intensityYIntervalCount;
			int srcCosIntensityIntervalCount;
			int srcCosScaleIntervalCount;
			std::uint64_t intensityX;
			std::uint64_t intensityY;
			std::uint64_t srcCosIntensity;
			std::uint64_t srcCosScale;
		}; static_assert(sizeof(FxFlareDef) == 0x70);

		union FxElemExtendedDefPtr
		{
			std::uint64_t unknownDef;
			std::uint64_t trailDef;
			std::uint64_t sparkFountainDef;
			std::uint64_t spotLightDef;
			std::uint64_t omniLightDef;
			std::uint64_t flareDef;
		};

		struct FxElemDef
		{
			int flags;
			int flags2;
			FxSpawnDef spawn;
			FxFloatRange spawnRange;
			FxFloatRange fadeInRange;
			FxFloatRange fadeOutRange;
			float spawnFrustumCullRadius;
			FxIntRange spawnDelayMsec;
			FxIntRange lifeSpanMsec;
			FxFloatRange spawnOrigin[3];
			char __pad0[4];
			FxFloatRange spawnOffsetRadius;
			FxFloatRange spawnOffsetHeight;
			char __pad1[8];
			FxFloatRange spawnAngles[3];
			FxFloatRange angularVelocity[3];
			FxFloatRange initialRotation;
			FxFloatRange gravity;
			FxFloatRange reflectionFactor;
			FxElemAtlas atlas;
			FxElemType elemType;
			unsigned char elemLitType;
			unsigned char visualCount;
			unsigned char velIntervalCount;
			unsigned char visStateIntervalCount;
			std::uint64_t velSamples;
			std::uint64_t visSamples;
			FxElemDefVisuals visuals;
			Bounds collBounds;
			FxEffectDefRef effectOnImpact;
			FxEffectDefRef effectOnDeath;
			FxEffectDefRef effectEmitted;
			FxFloatRange emitDist;
			FxFloatRange emitDistVariance;
			FxElemExtendedDefPtr extended;
			unsigned char sortOrder;
			unsigned char lightingFrac;
			unsigned char useItemClip;
			unsigned char fadeInfo;
			int randomSeed;
			char __pad2[16];
		}; static_assert(sizeof(FxElemDef) == 0x140);

		static_assert(offsetof(FxElemDef, spawnOrigin) == 60);
		static_assert(offsetof(FxElemDef, spawnOffsetRadius) == 88);
		static_assert(offsetof(FxElemDef, spawnOffsetHeight) == 96);
		static_assert(offsetof(FxElemDef, spawnAngles) == 112);
		static_assert(offsetof(FxElemDef, spawnDelayMsec) == 44);
		static_assert(offsetof(FxElemDef, lifeSpanMsec) == 52);
		static_assert(offsetof(FxElemDef, spawn) == 8);
		static_assert(offsetof(FxElemDef, visualCount) == 194);
		static_assert(offsetof(FxElemDef, effectOnDeath) == 256);
		static_assert(offsetof(FxElemDef, spawnAngles) == 112);
		static_assert(offsetof(FxElemDef, elemType) == 192);
		static_assert(offsetof(FxElemDef, visSamples) == 0xD0);
		static_assert(offsetof(FxElemDef, visuals) == 0xD8);
		static_assert(offsetof(FxElemDef, effectOnImpact) == 0xF8);
		static_assert(offsetof(FxElemDef, extended) == 0x120);
		static_assert(offsetof(FxElemDef, effectEmitted) == 0x108);
		static_assert(offsetof(FxElemDef, visStateIntervalCount) == 0xC4);
		static_assert(offsetof(FxElemDef, velIntervalCount) == 0xC3);

		struct FxEffectDef
		{
			const std::uint64_t name;
			int flags;
			int totalSize;
			int msecLoopingLife;
			int elemDefCountLooping;
			int elemDefCountOneShot;
			int elemDefCountEmission;
			float elemMaxRadius;
			float occlusionQueryDepthBias;
			int occlusionQueryFadeIn;
			int occlusionQueryFadeOut;
			FxFloatRange occlusionQueryScaleRange;
			float xU_01;
			std::uint64_t elemDefs;
		}; static_assert(sizeof(FxEffectDef) == 0x48);

		static_assert(offsetof(FxEffectDef, elemDefs) == 0x40);
		static_assert(offsetof(FxEffectDef, elemDefCountLooping) == 0x14);
		static_assert(offsetof(FxEffectDef, elemDefCountOneShot) == 0x18);
		static_assert(offsetof(FxEffectDef, elemDefCountEmission) == 0x1C);

		struct XModelIKData
		{
			unsigned char charDataLen;
			unsigned char floatDataLen;
			unsigned char int32DataLen;
			unsigned char stringsCount;
			std::uint64_t charData;
			std::uint64_t floatData;
			std::uint64_t int32Data;
			std::uint64_t strings;
		}; static_assert(sizeof(XModelIKData) == 0x28);

		struct SkeletonScriptCode
		{
			char __pad0[4];
		};

		struct SkeletonScript
		{
			const std::uint64_t name;
			XModelIKData ikData;
			unsigned short codeLen;
			std::uint64_t code;
		}; static_assert(sizeof(SkeletonScript) == 0x40);

		static_assert(offsetof(SkeletonScript, ikData) == 8);
		static_assert(offsetof(XModelIKData, strings) == 32);
		static_assert(offsetof(XModelIKData, stringsCount) == 3);
		static_assert(offsetof(XModelIKData, int32Data) == 24);
		static_assert(offsetof(XModelIKData, int32DataLen) == 2);
		static_assert(offsetof(XModelIKData, floatData) == 16);
		static_assert(offsetof(XModelIKData, floatDataLen) == 1);

		union XAnimDynamicFrames
		{
			std::uint64_t _1;
			std::uint64_t _2;
		};

		union XAnimDynamicIndices
		{
			unsigned char _1[1];
			unsigned short _2[1];
		};

		struct XAnimPartTransFrames
		{
			float mins[3];
			float size[3];
			XAnimDynamicFrames frames;
			XAnimDynamicIndices indices;
		};

		union XAnimPartTransData
		{
			XAnimPartTransFrames frames;
			float frame0[3];
		};

		struct XAnimPartTrans
		{
			unsigned short size;
			unsigned char smallTrans;
			XAnimPartTransData u;
		};

		struct XAnimDeltaPartQuatDataFrames2
		{
			std::uint64_t frames;
			XAnimDynamicIndices indices;
		};

		union XAnimDeltaPartQuatData2
		{
			XAnimDeltaPartQuatDataFrames2 frames;
			short frame0[2];
		};

		struct XAnimDeltaPartQuat2
		{
			unsigned short size;
			XAnimDeltaPartQuatData2 u;
		};

		struct XAnimDeltaPartQuatDataFrames
		{
			std::uint64_t frames;
			XAnimDynamicIndices indices;
		};

		union XAnimDeltaPartQuatData
		{
			XAnimDeltaPartQuatDataFrames frames;
			short frame0[4];
		};

		struct XAnimDeltaPartQuat
		{
			unsigned short size;
			XAnimDeltaPartQuatData u;
		};

		struct XAnimDeltaPart
		{
			std::uint64_t trans;
			std::uint64_t quat2;
			std::uint64_t quat;
		};

		union XAnimIndices
		{
			std::uint64_t _1;
			std::uint64_t _2;
			std::uint64_t data;
		};

		struct XAnimNotifyInfo
		{
			scr_string_t name;
			float time;
		};

		enum XAnimPartsFlags : std::uint8_t
		{
			ANIM_NONE = 0x0,
			ANIM_LOOP = 0x1,
			ANIM_DELTA = 0x2,
			ANIM_DELTA_3D = 0x4,
			ANIM_DEFAULT = 0x8,
		};

		typedef float BlendShapeWeight;
		typedef char XAnimScriptedViewmodelAnimData;

		struct XAnimParts
		{
			const std::uint64_t name; // 0
			unsigned short dataByteCount; // 8
			unsigned short dataShortCount; // 10
			unsigned short dataIntCount; // 12
			unsigned short numframes; // 14
			unsigned char flags; // 15
			unsigned char boneCount[10]; // 16
			char u1; // unused?
			char u2; // unused?
			unsigned char notifyCount; // 29
			unsigned char assetType; // 30
			unsigned char ikType; // 31
			unsigned int randomDataByteCount; // 32
			unsigned int randomDataShortCount; // 36
			unsigned int randomDataIntCount; // 40
			unsigned int indexCount; // 44
			float framerate;  // 48
			float frequency; // 56
			std::uint64_t names; // 56
			std::uint64_t dataByte; // 64
			std::uint64_t dataShort; // 72
			std::uint64_t dataInt; // 80
			std::uint64_t randomDataShort; // 88
			std::uint64_t randomDataByte; // 96
			std::uint64_t randomDataInt; // 104
			XAnimIndices indices; // 112
			std::uint64_t notify; // 120
			std::uint64_t deltaPart; // 128
			const std::uint64_t secondaryName; // 136
			short u3; // unknown
			unsigned short blendShapeWeightCount; // 146
			short u4; // unused? padding?
			std::uint64_t blendShapeWeightNames; // 152
			std::uint64_t blendShapeWeightUnknown1; // 160
			std::uint64_t blendShapeWeightUnknown2; // 168
			std::uint64_t blendShapeWeightUnknown3; // 176
			std::uint64_t blendShapeWeightUnknown4; // 184
			std::uint64_t blendShapeWeights; // 192
			std::uint64_t u5; // unused?
			std::uint64_t scriptedViewmodelAnimData; // 208 // count = 8
		}; static_assert(sizeof(XAnimParts) == 0xD8);

		union PackedUnitVec
		{
			unsigned int packed;
		};

		union PackedTexCoords
		{
			unsigned int packed;
		};

		union GfxColor
		{
			unsigned char array[4];
			unsigned int packed;
		};

		struct GfxPackedVertex
		{
			float xyz[3];
			float binormalSign;
			GfxColor color;
			PackedTexCoords texCoord;
			PackedUnitVec normal;
			PackedUnitVec tangent;
		};

		struct GfxPackedMotionVertex
		{
			float xyz[3];
			float binormalSignAndHeight;
			GfxColor pieceIndex;
			PackedTexCoords texCoord;
			PackedUnitVec normal;
			PackedUnitVec tangent;
		};

		union GfxVertexUnion0
		{
			std::uint64_t packedVerts0;
			std::uint64_t packedMotionVerts0;
			std::uint64_t verts0;
		};

		struct Face
		{
			unsigned short v1;
			unsigned short v2;
			unsigned short v3;
		};

		struct XSurfaceCollisionAabb
		{
			unsigned short mins[3];
			unsigned short maxs[3];
		};

		struct XSurfaceCollisionNode
		{
			XSurfaceCollisionAabb aabb;
			unsigned short childBeginIndex;
			unsigned short childCount;
		};

		struct XSurfaceCollisionLeaf
		{
			unsigned short triangleBeginIndex;
		};

		struct XSurfaceCollisionTree
		{
			float trans[3];
			float scale[3];
			unsigned int nodeCount;
			std::uint64_t nodes;
			unsigned int leafCount;
			std::uint64_t leafs;
		};

		struct XRigidVertList
		{
			unsigned short boneOffset;
			unsigned short vertCount;
			unsigned short triOffset;
			unsigned short triCount;
			std::uint64_t collisionTree;
		};

		struct UnknownXSurface0
		{
			float xyz[3];
			PackedUnitVec normal;
		};

		struct BlendVertsUnknown
		{
			unsigned short b[15];
			unsigned short blendVertCountIndex; // 30
		}; static_assert(sizeof(BlendVertsUnknown) == 32);

		struct XSubdivRigidVertList
		{
			unsigned int firstFace;
			unsigned int faceCount;
			unsigned int firstRegularPatch;
			unsigned int regularPatchCount;
		};

		struct XSurfaceSubdivLevel
		{
			std::uint64_t rigidVertLists;
			unsigned int faceCount;
			unsigned int regularPatchCount;
			unsigned int regularPatchOffset;
			unsigned int facePointCount;
			unsigned int facePointValence4Count;
			unsigned int facePointBufferSize;
			unsigned int edgePointCount;
			unsigned int edgePointSmoothEnd;
			unsigned int edgePointUVBorderEnd;
			unsigned int vertexPointCount;
			unsigned int vertexPointValence4Count;
			unsigned int vertexPointBufferSize;
			unsigned int normalCount;
			unsigned int normalBufferSize;
			unsigned int transitionPointCount;
			unsigned int vertCount;
			unsigned int vertOffset;
			std::uint64_t faceIndices;
			std::uint64_t regularPatchIndices;
			std::uint64_t regularPatchFlags;
			std::uint64_t facePoints;
			std::uint64_t edgePoints;
			std::uint64_t vertexPoints;
			std::uint64_t normals;
			std::uint64_t transitionPoints;
			std::uint64_t regularPatchCones;
			std::uint64_t regularPatchIndexBuffer;
			std::uint64_t faceIndexBuffer;
			std::uint64_t regularPatchIndexBufferView;
			std::uint64_t regularPatchFlagsView;
			std::uint64_t facePointsView;
			std::uint64_t edgePointsView;
			std::uint64_t vertexPointsView;
			std::uint64_t normalsView;
			std::uint64_t transitionPointsView;
			std::uint64_t regularPatchConesView;
		}; static_assert(sizeof(XSurfaceSubdivLevel) == 0xE8);

		struct GfxSubdivCache
		{
			unsigned int size;
			std::uint64_t subdivCacheBuffer;
			std::uint64_t subdivCacheView;
		}; static_assert(sizeof(GfxSubdivCache) == 0x18);

		struct XSurfaceSubdivInfo
		{
			std::uint64_t levels;
			char __pad0[24];
			GfxSubdivCache cache;
		}; static_assert(sizeof(XSurfaceSubdivInfo) == 0x38);

		struct BlendShapeVert
		{
			char __pad0[32];
		};

		struct BlendShape
		{
			unsigned int vertCount;
			std::uint64_t verts;
			std::uint64_t blendShapeVertsBuffer;
			std::uint64_t blendShapeVertsView;
		};

		typedef char alignCompBufByte_t;
		typedef unsigned short alignVertBufFloat16Vec2_t[2];
		typedef unsigned short alignCompBufUShort_t;
		typedef float alignCompBufFloat_t;
		typedef unsigned short XBlendInfo;

		struct XSurface
		{
			unsigned short flags;
			unsigned short vertCount;
			unsigned short triCount;
			unsigned char rigidVertListCount;
			unsigned char subdivLevelCount;
			short blendVertCounts[8];
			GfxVertexUnion0 verts0;
			std::uint64_t triIndices;
			std::uint64_t triIndices2;
			std::uint64_t vb0;
			std::uint64_t vb0View;
			std::uint64_t indexBuffer;
			std::uint64_t rigidVertLists;
			std::uint64_t unknown0;
			std::uint64_t blendVerts;
			std::uint64_t blendVertsTable;
			std::uint64_t blendVertsBuffer;
			std::uint64_t blendVertsView;
			std::uint64_t lmapUnwrap;
			std::uint64_t vblmapBuffer;
			std::uint64_t vblmapView;
			std::uint64_t subdiv;
			std::uint64_t tensionData;
			std::uint64_t tensionAccumTable;
			std::uint64_t tensionAccumTableBuffer;
			std::uint64_t tensionAccumTableView;
			std::uint64_t tensionDataBuffer;
			std::uint64_t tensionDataView;
			std::uint64_t indexBufferView;
			std::uint64_t blendShapes;
			unsigned int blendShapesCount;
			unsigned int vertexLightingIndex;
			char __pad0[4];
			int partBits[8];
			char __pad1[4];
		}; static_assert(sizeof(XSurface) == 0x108);

		struct XModelSurfs
		{
			const std::uint64_t name;
			std::uint64_t surfs;
			unsigned short numsurfs;
			int partBits[8];
		}; static_assert(sizeof(XModelSurfs) == 0x38);

		struct XUnknown1
		{
			char __pad0[32];
		}; static_assert(sizeof(XUnknown1) == 32);

		struct XModelLodInfo
		{
			float dist; // 0
			unsigned short numsurfs; // 4
			unsigned short surfIndex; // 6
			std::uint64_t modelSurfs; // 8
			int partBits[8]; // 16 20 24 28 32 36 40 44
			std::uint64_t surfs; // 48
			std::uint64_t reactiveMotionParts; // 56 (sizeof struct = 32) (reactiveMotionParts?)
			char __pad0[5]; // 64 (something must be here)
			char numReactiveMotionParts; // 69 (numReactiveMotionParts?)
			char __pad1[2]; // 70 (padding?)
		}; static_assert(sizeof(XModelLodInfo) == 72);

		struct XModelAngle
		{
			short x;
			short y;
			short z;
			short base;
		};

		struct XModelTagPos
		{
			float x;
			float y;
			float z;
		};

		struct DObjAnimMat
		{
			float quat[4];
			float trans[3];
			float transWeight;
		};

		struct ReactiveMotionModelPart
		{
			float center[3];
			float stiffness;
		};

		struct ReactiveMotionModelTweaks
		{
			float scale[4];
		};

		struct XModelCollSurf_s
		{
			Bounds bounds;
			int boneIdx;
			int contents;
			int surfFlags;
		};

		struct XBoneInfo
		{
			Bounds bounds;
			union
			{
				float radiusSquared;
				unsigned int radiusSquaredAsInt;
			};
		};

		struct BlendShapeWeightMap
		{
			unsigned short weightIndex;
			unsigned short targetIndex;
			float fullWeight;
		};

		struct ExtentBounds
		{
			vec3_t mins;
			vec3_t maxs;
		};

		struct MdaoVolume
		{
			ExtentBounds bounds;
			unsigned __int16 cellCount[3];
			unsigned __int16 parentBoneIndex;
			std::uint64_t volumeData;
		}; static_assert(sizeof(MdaoVolume) == 0x28);

		struct XPhysBoneInfo
		{
			std::uint64_t physPreset;
			std::uint64_t physContraint;
			std::uint64_t physCollmap;
			char __pad0[8];
		}; static_assert(sizeof(XPhysBoneInfo) == 0x20);

		enum XModelFlags : std::uint16_t
		{
			XMODEL_FLAG_COMPOSITE = 0x400,
		};

		struct XModel
		{
			const std::uint64_t name; // 0
			unsigned char numBones; // 8
			unsigned char numRootBones; // 9
			unsigned char numsurfs; // 10
			unsigned char lodRampType; // 11
			unsigned char numBonePhysics; // 12
			unsigned char numCompositeModels; // 13
			char __pad0[2]; // 14-16
			float scale; // 16
			unsigned int noScalePartBits[8]; // 20
			std::uint64_t boneNames; // 56
			std::uint64_t parentList; // 64
			std::uint64_t tagAngles; // 72
			std::uint64_t tagPositions; // 80
			std::uint64_t partClassification; // 88
			std::uint64_t baseMat; // 96
			std::uint64_t reactiveMotionTweaks; // 104
			std::uint64_t materialHandles; // 112
			XModelLodInfo lodInfo[6]; // 120
			char numLods; // 552
			char collLod; // 553
			char __pad1[2]; // 554-556
			short flags; // 556
			short numCollSurfs; // 558
			std::uint64_t collSurfs; // 560
			std::uint64_t boneInfo; // 568
			int contents;
			float radius;
			Bounds bounds;
			std::uint64_t invHighMipRadius; // 608
			std::uint64_t mdaoVolumes; // 616
			unsigned short mdaoVolumeCount; // 624
			unsigned short targetCount; // 626
			unsigned short numberOfWeights; // 628
			unsigned short numberOfWeightMaps; // 630
			std::uint64_t weightNames; // 632
			std::uint64_t blendShapeWeightMap; // 640
			std::uint64_t physPreset; // 648
			std::uint64_t physCollmap; // 656
			float quantization;
			int memUsage;
			std::uint64_t skeletonScript; // 672
			std::uint64_t compositeModels; // 680
			std::uint64_t bonePhysics; // 688
		};  static_assert(sizeof(XModel) == 0x2B8);
	}
}
