#include "physics_engine.h"


physics_engine::PhysicsEngine::PhysicsEngine()
	:registeredSystems(KNOWN_SYSTEM_SIZE)
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
}

void physics_engine::PhysicsEngine::setParticleSystem(ParticleSystemTypes type, std::shared_ptr<Particle>& p, int level)
{
	m_pSystems[level] = std::move(ParticleSystemFactory::getSystem(type));
	m_pSystems[level]->setParticles(p);
	registeredSystems[FLUID][level].isSet = true;
	registeredSystems[FLUID][level].integratorNonRotatingId = integrator.addIntegrable(Integrator::IntegrableType::NON_ROTATING, p);
}

void physics_engine::PhysicsEngine::remove(PhysicalSystems systemType, int level)
{
	if (!registeredSystems[systemType][level].isSet)
		throw std::string("already unset...");

	unregister(registeredSystems[systemType][level]);
	registeredSystems[systemType][level].isSet = false;
}

void physics_engine::PhysicsEngine::setIntegrator(Integrator::IntegratorTypes integratorType, float timeStep)
{
	integrator.setIntegrator(integratorType, timeStep);
}

void physics_engine::PhysicsEngine::setGravity(glm::vec3 gravity)
{
	integrator.setGravity(gravity);
}

void physics_engine::PhysicsEngine::update(float timeStep)
{
	//collision detection between objects
	//collision detection between objects and particles
	for (auto&& pSystem : m_pSystems)
	{
		pSystem.second->computeInternalForces();
	}
	//integrate new values
	integrator.integrate(timeStep);
	glMemoryBarrier(GL_VERTEX_ATTRIB_ARRAY_BARRIER_BIT);
}
