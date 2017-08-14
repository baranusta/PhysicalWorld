#include "sph_fluid.h"

void SPHFluid::addParticles(std::vector<Particle> p)
{
	particle_count += p.size();
	if (particle_start_index == unsigned int(-1))
		particle_start_index = physics_engine::PhysicsEngine::getInstance().addFluid(p);
	else
		physics_engine::PhysicsEngine::getInstance().addFluid(p, particle_start_index);
}

void SPHFluid::render()
{
	//get particle start
}

unsigned int SPHFluid::getParticleSIndex()
{
	return particle_start_index;
}