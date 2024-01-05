#pragma once

namespace ZoneTool::H1
{
	class ISoundCurve
	{
	public:
		static void dump(SndCurve* asset, const std::string& type);
		static void dump(SndCurve* asset);
	};
}