#pragma once

namespace ZoneTool::H1
{
	class IVertexDecl : public IAsset
	{
	public:
		static void dump(MaterialVertexDeclaration* asset);
	};
}