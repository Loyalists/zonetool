#pragma once

namespace ZoneTool::H1
{
	class IVertexShader : public IAsset
	{
	public:
		static void dump(MaterialVertexShader* asset);
	};
}