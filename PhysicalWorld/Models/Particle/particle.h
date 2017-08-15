#pragma once

#include "..\..\glm\glm.hpp"
#include <vector>


class Particle
{
public:
	glm::vec3 position;
	glm::vec3 velocity;
	glm::vec3 acceleration;
	glm::vec3 force;

	glm::vec3 color_diffuse;
	glm::vec3 color_ambient;
	float color_specular;

	float mass;
	float radius;
	float viscosity;
};