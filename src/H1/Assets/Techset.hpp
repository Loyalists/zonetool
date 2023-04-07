#pragma once

namespace ZoneTool
{
	namespace H1
	{
		class ITechset : public IAsset
		{
		public:
			static void dump_stateinfo(const std::string& techset, Material* mat);
			static void dump_statebits(const std::string& techset, unsigned char* statebits);
			static void dump_statebits_map(const std::string& techset, GfxStateBits* map, unsigned char count);
			static void dump_constant_buffer_indexes(const std::string& techset, unsigned char* cbi);
			static void dump_constant_buffer_def_array(const std::string& techset, unsigned char count, MaterialConstantBufferDef* def);
			static void dump_technique(MaterialTechnique* asset);
			static void dump(MaterialTechniqueSet* asset);
		};
	}
}