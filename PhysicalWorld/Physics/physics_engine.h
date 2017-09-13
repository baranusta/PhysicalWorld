#pragma once

#include "PhysicsManagers\Particles\particle_system.h"
#include "PhysicsManagers\Particles\particle_system_factory.h"
#include "PhysicsManagers\Integrate\integrator.h"


#define PHYSICS_UNSET_INDEX -1


namespace physics_engine
{
	class PhysicsEngine
	{
	private:

		struct PhysicalObject
		{
			bool isSet;
			int integratorNonRotatingId = PHYSICS_UNSET_INDEX;
			int integratorRotatingId = PHYSICS_UNSET_INDEX;
		};

		//These are for cleanups. If any of the object is removed,
		//it will be removed from all the corresponding handlers.
		std::vector<std::unordered_map<int, PhysicalObject>> registeredSystems;

		//These are vectors. Because there may be different levels for objects. eg. They will not be compared for collision detection 
		std::unordered_map<int, std::unique_ptr<ParticleSystem>> m_pSystems;

		Integrator integrator;


		void unregister(PhysicalObject object);

	public:
		PhysicsEngine();
		enum PhysicalSystems { FLUID, NON_ROTATING, ROTATING, STATIC, KNOWN_SYSTEM_SIZE };

	public:
		void setParticleSystem(ParticleSystemTypes type, std::shared_ptr<Particle>& p, int level = 0);
		void remove(PhysicalSystems systemType, int level = 0);

		void setIntegrator(Integrator::IntegratorTypes integratorType, float timeStep);
		void setGravity(glm::vec3 gravity);

		void update(float timeStep);

	};
}