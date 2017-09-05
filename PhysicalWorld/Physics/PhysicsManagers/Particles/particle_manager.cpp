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

int physics_engine::ParticleManager::addParticles(ParticleSystemTypes systemType, Particle * particles)
{
	if (m_systems.find(systemType) == m_systems.end())
	{
		m_systems[systemType] = createParticleSystem(systemType);
	}
	return m_systems[systemType]->addParticles(particles);
}

void physics_engine::ParticleManager::removeParticles(ParticleSystemTypes systemType, int id)
{
	if (m_systems.find(systemType) != m_systems.end())
	{
		if (m_systems[systemType]->removeParticles(id) == 0) 
		{
			delete m_systems[systemType];
			m_systems.erase(systemType);
		}
	}
}

void physics_engine::ParticleManager::computeForces()
{
	for (auto system_man : m_systems)
	{
		system_man.second->computeForces();
	}
}
