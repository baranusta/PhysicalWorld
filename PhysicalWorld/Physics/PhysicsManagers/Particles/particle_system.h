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
		virtual void setParticles(std::shared_ptr<Particle> particles) = 0;

		virtual void computeForces() = 0;
	};
}