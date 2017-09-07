#include "scene_manager.h"

SceneManager::SceneManager(glm::vec2 size)
{
	m_size = size;
}

void SceneManager::resolveScene(Scene * scene)
{
	scene->addSPHFluids(m_fluids);
	m_cameras = std::move(scene->getCameras(m_size));


	delete scene;
}

void SceneManager::clean()
{
	m_fluids.clear();
	m_cameras.clear();
}

std::vector<std::shared_ptr<Camera>> SceneManager::getCameras()
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
