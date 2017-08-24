#include "physics_engine.h"


physics_engine::PhysicsEngine::PhysicsEngine()
{
}

void physics_engine::PhysicsEngine::unregister(PhysicalObject object)
{
	if (object.integratorNonRotatingId != PHYSICS_UNSET_INDEX)
	{
		integrator.removeIntegrable(Integrator::IntegrableType::NON_ROTATING, object.integratorNonRotatingId);
	}
	if (object.integratorRotatingId != PHYSICS_UNSET_INDEX)
	{

	}
	if (object.particleSystemId != PHYSICS_UNSET_INDEX)
	{
		m_pManager.removeParticles(static_cast<ParticleSystemTypes>(object.particleSystemType), object.particleSystemId);
	}
}

int physics_engine::PhysicsEngine::addFluid(ParticleSystemTypes type, Particle * p)
{
	PhysicalObject o;
	o.particleSystemId = m_pManager.addParticles(type, p);
	o.particleSystemType = type;
	o.integratorNonRotatingId = integrator.addIntegrable(Integrator::IntegrableType::NON_ROTATING, p);
	registeredObjects[objectCount++] = o;
	return objectCount;
}

void physics_engine::PhysicsEngine::remove(int id)
{
	unregister(registeredObjects[id]);
	registeredObjects.erase(id);
}

void physics_engine::PhysicsEngine::update(float timeStep)
{
	//collision detection between objects
	//collision detection between objects and particles
	m_pManager.computeForces();
	//integrate new values
	integrator.integrate(timeStep);
	glMemoryBarrier(GL_VERTEX_ATTRIB_ARRAY_BARRIER_BIT);
}
