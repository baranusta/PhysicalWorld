#pragma once

#include "..\..\glm\glm.hpp"
#include <vector>


class Particle
{
public:
	glm::vec4 position;
	glm::vec4 velocity;
	glm::vec4 force;
	float rest_density;

	glm::vec4 color_diffuse;
	glm::vec4 color_ambient;
	float color_specular;

	float mass;
	float radius;
	float viscosity;
};