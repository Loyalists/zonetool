#pragma once
namespace ZoneTool
{
	namespace T6
	{

		class IZBarrierDef : public IAsset
		{
		private:

		public:
			static Json dumpboards(ZBarrierDef* asset);
			static void dump(ZBarrierDef* asset);
		};
	}
}