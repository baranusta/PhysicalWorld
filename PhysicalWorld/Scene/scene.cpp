#include "scene.h"



Scene::Scene()
{
}


Scene::~Scene()
{
}

std::vector<Particle> Scene::getSPHParticles()
{
	return {};
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

std::vector<Camera*> Scene::getCameras(glm::vec2 size)
{
	return {};
}
