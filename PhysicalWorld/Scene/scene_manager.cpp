#include "scene_manager.h"

SceneManager::SceneManager(glm::vec2 size, physics_engine::PhysicsEngine& pEngine)
	:m_physicsEngine(pEngine)
{
	m_size = size;
}

void SceneManager::resolveScene(Scene * scene)
{
	scene->addSPHFluids(m_fluids, m_physicsEngine);
	m_cameras = std::move(scene->getCameras(m_size));

	m_physicsEngine.setGravity(scene->getGravity());


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
