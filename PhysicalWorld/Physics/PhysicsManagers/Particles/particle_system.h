#pragma once

#include "..\..\Models\particle.h"

namespace physics_engine
{
	enum ParticleSystemTypes
	{
		SPH_DEFAULT,
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