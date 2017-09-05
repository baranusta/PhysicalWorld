#include "scene.h"



Scene::Scene()
{
}


Scene::~Scene()
{
}

std::vector<Particle> Scene::getSPHParticles()
{
	return std::vector<Particle>();
}

std::vector<int> Scene::getStaticObjects()
{
	return std::vector<int>();
}

std::vector<int> Scene::getMovingObjects()
{
	return std::vector<int>();
}

std::vector<int> Scene::getLights()
{
	return std::vector<int>();
}

Camera Scene::getCamera()
{
	return Camera();
}
