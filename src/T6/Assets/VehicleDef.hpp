// ======================= ZoneTool =======================
// zonetool, a fastfile linker for various
// Call of Duty titles. 
//
// Project: https://github.com/ZoneTool/zonetool
// Author: RektInator (https://github.com/RektInator)
// License: GNU GPL v3.0
// ========================================================
#pragma once

namespace ZoneTool
{
	namespace T6
	{
		class IVehicleDef : public IAsset
		{
		private:

		public:
			static Json dump_vehicle_parameters(VehicleDef* asset);
			static Json dump_vehicle_engine(VehicleDef* asset);
			static void dump(VehicleDef* asset);
		};
	}
}
