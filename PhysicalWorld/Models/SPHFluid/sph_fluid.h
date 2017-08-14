#pragma once

#include "..\Particle\particle.h"
#include "..\..\Physics\physics_engine.h"

class SPHFluid
{
private:
	unsigned int particle_count = 0;
	unsigned int particle_start_index = -1;

	glm::vec3 position;
	glm::vec3 rotation;
	
public:

	void addParticles(std::vector<Particle>);

	void render();

	unsigned int getParticleSIndex();
	int get()
	{
		return 2;
	}
};