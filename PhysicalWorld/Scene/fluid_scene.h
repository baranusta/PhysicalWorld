#pragma once

#include "scene.h"

class FluidScene : public Scene
{
	size_t m_sphCount;
public:
	FluidScene(int sphCount)
	{
		m_sphCount = sphCount;
	}

	std::vector<Particle> getSPHParticles()
	{
		std::vector<Particle> particles(m_sphCount);
		for (unsigned int i = 0; i < m_sphCount; i++)
		{
			Particle p = Particle();
			p.position = glm::vec4(0.01 * i, 0., 0., 1.);
			p.mass = 0.1f;
			p.radius = 10;

			particles[i] = p;
		}
		return particles;
	}
};