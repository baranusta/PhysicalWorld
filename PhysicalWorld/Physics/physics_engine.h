#pragma once

#include "PhysicsManagers\Fluid\SPHStrategies\sph_strategies.h"

namespace physics_engine
{
	class PhysicsEngine
	{
	private:

		SPHFluid m_fluid;
		SPHStrategies* m_sphStrategy;
		
		PhysicsEngine() = default;

	public:
		PhysicsEngine(PhysicsEngine&) = delete;
		void operator=(PhysicsEngine&) = delete;

		static PhysicsEngine& getInstance()
		{
			static PhysicsEngine engine;
			return engine;
		}

		void setFluid(SPHFluid);

		void update();
	};
}