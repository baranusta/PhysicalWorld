#pragma once

#include "..\..\Models\particle.h"

namespace physics_engine
{
	enum ParticleSystemTypes
	{
		PBF_MULLER_2003,
		PARTICLE_SYSTEM_TYPES_SIZE
	};

	class ParticleSystem
	{
	public:
		virtual int addParticles(Particle* particles) = 0;
		virtual int removeParticles(int id) = 0;

		virtual void computeForces() = 0;
	};
}