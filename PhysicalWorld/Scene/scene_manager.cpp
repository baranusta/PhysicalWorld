#include "scene_manager.h"

#define DELETE(x) {if(x != nullptr) delete x;}

void SceneManager::destroyScene()
{
	DELETE(m_fluid);
}

void SceneManager::addFluid(const std::vector<Particle>& data)
{
	if (data.size() == 0)
		return;
	if (m_fluid == nullptr)
		m_fluid = new SPHFluid();
	m_fluid->addParticles(data);
}

SceneManager::SceneManager()
{
	m_fluid = nullptr;
}


SceneManager::~SceneManager()
{
}

void SceneManager::resolveScene(Scene * scene)
{
	addFluid(scene->getSPHParticles());

	delete scene;
}

void SceneManager::clean()
{
	destroyScene();
}
