#include "scene.h"



Scene::Scene()
{
}


Scene::~Scene()
{
}

glm::vec3 Scene::getGravity()
{
	return glm::vec3();
}

void Scene::addSPHFluids(std::vector<std::unique_ptr<SPHFluid>>& fluids, physics_engine::PhysicsEngine&)
{
}

std::vector<int> Scene::getStaticObjects()
{
	return {};
}

std::vector<int> Scene::getMovingObjects()
{
	return {};
}

std::vector<int> Scene::getLights()
{
	return {};
}

std::vector<std::shared_ptr<Camera>> Scene::getCameras(glm::vec2 size)
{
	return {};
}
