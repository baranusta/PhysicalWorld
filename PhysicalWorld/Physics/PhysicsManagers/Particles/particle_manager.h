#pragma once
#include "..\..\Models\particle.h"


#include "SPHDefault\sph_default.h"

#include <unordered_map>

namespace physics_engine
{
	class ParticleManager
	{
	private:
		ParticleSystem* createParticleSystem(ParticleSystemTypes type);

		std::unordered_map<int, ParticleSystem*> m_systems;
	public:
		int addParticles(ParticleSystemTypes systemType, Particle* particles);
		void removeParticles(ParticleSystemTypes systemType, int id);

		void computeForces();
	};
}