#include "scene.h"



Scene::Scene()
{
}


Scene::~Scene()
{
}

void Scene::addSPHFluids(std::vector<std::unique_ptr<SPHFluid>>& fluids)
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
