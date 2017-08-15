#pragma once

#include "sph_strategies.h"


namespace physics_engine
{
	class DummySphStrategy: public SPHStrategies
	{
		void update(SPHFluid fluid) {

		}
	};
}