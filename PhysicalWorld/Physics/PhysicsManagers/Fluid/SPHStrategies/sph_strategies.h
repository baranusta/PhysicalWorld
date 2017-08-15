#pragma once

#include "..\..\..\Models\sph_fluid.h"


namespace physics_engine
{
	class SPHStrategies
	{
	public:
		virtual void update(SPHFluid) = 0;
	};
}