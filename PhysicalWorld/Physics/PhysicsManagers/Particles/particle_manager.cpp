#include "particle_manager.h"

physics_engine::ParticleSystem * physics_engine::ParticleManager::createParticleSystem(ParticleSystemTypes type)
{
	switch (type)
	{
	case ParticleSystemTypes::PBF_MULLER_2003:
		return new PBF2003();
		break;
	}
	return nullptr;
}

void physics_engine::ParticleManager::setParticles(ParticleSystemTypes systemType, std::shared_ptr<Particle> particles)
{
	if (m_systems.find(systemType) == m_systems.end())
	{
		m_systems[systemType] = createParticleSystem(systemType);
	}
	m_systems[systemType]->setParticles(particles);
}

void physics_engine::ParticleManager::removeParticles(ParticleSystemTypes systemType, int id)
{
	if (m_systems.find(systemType) != m_systems.end())
	{
		delete m_systems[systemType];
		m_systems.erase(systemType);
	}
}

void physics_engine::ParticleManager::computeInternalForces()
{
	for (auto system_man : m_systems)
	{
		system_man.second->computeForces();
	}
}
