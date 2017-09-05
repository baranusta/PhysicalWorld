#include "scene_manager.h"

#ifndef DELETE_PTR(x)
#define DELETE_PTR(x) {if(x != nullptr) delete x;}
#endif

void SceneManager::destroyScene()
{
	DELETE_PTR(m_fluid);
	for (auto& cam : m_cameras)
		delete cam;
}

void SceneManager::addFluid(const std::vector<Particle>& data)
{
	if (data.size() == 0)
		return;
	if (m_fluid == nullptr)
		m_fluid = new SPHFluid();
	m_fluid->addParticles(data);
}

SceneManager::SceneManager(glm::vec2 size)
{
	m_size = size;
	m_fluid = nullptr;
}


SceneManager::~SceneManager()
{
	destroyScene();
}

void SceneManager::resolveScene(Scene * scene)
{
	addFluid(scene->getSPHParticles());
	m_cameras = scene->getCameras(m_size);


	delete scene;
}

void SceneManager::clean()
{
	destroyScene();
}

std::vector<Camera*> SceneManager::getCameras()
{
	return m_cameras;
}

void SceneManager::update()
{
	for (auto& cam : m_cameras)
	{
		cam->update();
	}
}
