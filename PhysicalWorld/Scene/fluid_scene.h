#pragma once

#include "scene.h"
#include "..\Models\Camera\favorite_camera.h"

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
		int x = glm::pow(m_sphCount, 1.f / 3.f);
		std::vector<Particle> particles(x * x * x);
		int t = 0;
		for (unsigned int i = 0; i < x; i++)
		{
			for (unsigned int j = 0; j < x; j++)
			{
				for (unsigned int k = 0; k < x; k++)
				{
					Particle p = Particle();
					p.position = glm::vec4( - 0.5 + 0.1 * k, -0.5 + 0.1 * j, -0.5 + 0.1 * i, 1.);
					p.mass = 0.1f;
					p.radius = 10;

					particles[t++] = p;
				}
			}
		}
		return particles;
	}

	std::vector<Camera*> getCameras(glm::vec2 size)
	{
		FavoriteCamera* cam = new FavoriteCamera(size);
		cam->setCenter(glm::vec3(0.f, 0.f, 1.2f));
		cam->setLookAt(glm::vec3(0.f, 0.f, 0.f));
		cam->setUp(glm::vec3(0.f, 1.f, 0.f));
		cam->updateProjection();
		cam->updateView();

		return {cam};
	}
};