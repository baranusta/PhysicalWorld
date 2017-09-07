#pragma once
#include "..\..\Models\particle.h"


#include "particle_system.h"
#include "SPHSolvers\ParticleBasedFluid_Muller_2003\particle_based_fluid_muller_2003.h"

#include <unordered_map>

namespace physics_engine
{
	class ParticleManager
	{
	private:
		ParticleSystem* createParticleSystem(ParticleSystemTypes type);

		
		std::unordered_map<int, ParticleSystem*> m_systems;
	public:

		void setParticles(ParticleSystemTypes systemType, std::shared_ptr<Particle> particles);
		void removeParticles(ParticleSystemTypes systemType, int id);

		void computeForces();
	};
}