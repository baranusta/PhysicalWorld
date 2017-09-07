#pragma once

#include "PhysicsManagers\Particles\particle_manager.h"
#include "PhysicsManagers\Integrate\integrator.h"

#define PHYSICS_UNSET_INDEX -1


namespace physics_engine
{
	class PhysicsEngine
	{
	private:

		struct PhysicalObject 
		{
			int integratorNonRotatingId = PHYSICS_UNSET_INDEX;
			int integratorRotatingId = PHYSICS_UNSET_INDEX;
			
			int particleSystemType = PHYSICS_UNSET_INDEX;
			int particleSystemId = PHYSICS_UNSET_INDEX;

		};
		//These are for cleanups. If any of the object is removed,
		//it will be removed from all the corresponding handlers.
		std::unordered_map<int, PhysicalObject> registeredObjects;

		ParticleManager m_pManager;
		Integrator integrator;

		int objectCount = 0;
		PhysicsEngine();

		void unregister(PhysicalObject object);

	public:
		PhysicsEngine(PhysicsEngine&) = delete;
		void operator=(PhysicsEngine&) = delete;

		static PhysicsEngine& getInstance()
		{
			static PhysicsEngine engine;
			return engine;
		}

	public:
		int addFluid(ParticleSystemTypes type, std::shared_ptr<Particle>& p);
		void remove(int id);

		void setIntegrator(Integrator::IntegratorTypes integratorType, float timeStep);

		void update(float timeStep);
		
	};
}