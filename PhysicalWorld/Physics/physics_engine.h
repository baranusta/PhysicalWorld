#pragma once

#include "PhysicsManagers\Fluid\SPHStrategies\dummy_sph_strategy.h"

namespace physics_engine
{
	class PhysicsEngine
	{
	private:

		SPHFluid m_fluid;
		SPHStrategies* m_sphStrategy;
		
		PhysicsEngine();

	public:
		PhysicsEngine(PhysicsEngine&) = delete;
		void operator=(PhysicsEngine&) = delete;

		static PhysicsEngine& getInstance()
		{
			static PhysicsEngine engine;
			return engine;
		}

	public:
		SPHFluid* getFluid();

		void update();
		
	};
}