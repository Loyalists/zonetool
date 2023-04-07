#pragma once

namespace ZoneTool::H1
{
	class IPixelShader : public IAsset
	{
	public:
		static void dump(MaterialPixelShader* asset);
	};
}