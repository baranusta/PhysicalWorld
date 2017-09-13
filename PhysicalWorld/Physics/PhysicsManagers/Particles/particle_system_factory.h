#pragma once

#include "..\..\PhysicsManagers\Particles\SPHSolvers\ParticleBasedFluid_Muller_2003\particle_based_fluid_muller_2003.h"

namespace physics_engine
{
	class ParticleSystemFactory
	{
	public:
		static std::unique_ptr<ParticleSystem> getSystem(ParticleSystemTypes type)
		{
			std::unique_ptr<ParticleSystem> sys;
			switch (type)
			{
			case ParticleSystemTypes::PBF_MULLER_2003:
				sys = std::unique_ptr<ParticleSystem>(std::make_unique<PBF2003>());
				break;
			}
			return std::move(sys);
		}
	};
}