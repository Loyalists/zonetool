// ======================= ZoneTool =======================
// zonetool, a fastfile linker for various
// Call of Duty titles. 
//
// Project: https://github.com/ZoneTool/zonetool
// Author: RektInator (https://github.com/RektInator)
// License: GNU GPL v3.0
// ========================================================
#include "stdafx.hpp"
#include "PixelShader.hpp"

namespace ZoneTool
{
	namespace T6
	{
		MaterialPixelShader* IPixelShader::parse(const std::string& name, ZoneMemory* mem, bool preferLocal)
		{
			return nullptr;
		}

		void IPixelShader::init(void* asset, ZoneMemory* mem)
		{

		}

		void IPixelShader::init(const std::string& name, ZoneMemory* mem)
		{

		}

		void IPixelShader::prepare(ZoneBuffer* buf, ZoneMemory* mem)
		{
		}

		void IPixelShader::load_depending(IZone* zone)
		{
		}

		std::string IPixelShader::name()
		{
			return this->name_;
		}

		std::int32_t IPixelShader::type()
		{
			return 0;
		}

		void IPixelShader::write(IZone* zone, ZoneBuffer* buf)
		{

		}

		void IPixelShader::dump(MaterialPixelShader* asset)
		{
			AssetDumper write;
			const auto path = "techsets\\"s + asset->name + ".pixelshader"s;
			if (!write.open(path))
			{
				return;
			}

			write.dump_array(asset, 1);
			write.dump_string(asset->name);
			write.dump_array(asset->prog.loadDef.program, asset->prog.loadDef.programSize);
			write.close();
		}
	}
}
