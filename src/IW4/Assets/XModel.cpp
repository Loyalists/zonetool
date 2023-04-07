#include "stdafx.hpp"
#include "H1/Assets/XModel.hpp"
#include "IW5/Structs.hpp"

#include "IW5/Assets/XModel.hpp"

namespace ZoneTool
{
	namespace IW4
	{
		void IXModel::dump(XModel* asset, ZoneMemory* mem)
		{
			auto* iw5_model = mem->Alloc<IW5::XModel>();
			memcpy(iw5_model, asset, sizeof(XModel));
			iw5_model->unk = 0;

			// dump model
			IW5::IXModel::dump(iw5_model, mem, SL_ConvertToString);
		}
	}
}