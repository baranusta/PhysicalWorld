#include "physics_engine.h"


physics_engine::PhysicsEngine::PhysicsEngine()
{
	m_sphStrategy = new DummySphStrategy();
}

physics_engine::SPHFluid * physics_engine::PhysicsEngine::getFluid()
{
	return &m_fluid;
}

void physics_engine::PhysicsEngine::update()
{
	//collision detection between objects
	//collision detection between objects and particles
	//update
	m_sphStrategy->update(m_fluid);
}
