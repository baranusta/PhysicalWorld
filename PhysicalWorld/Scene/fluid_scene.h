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
		std::vector<Particle> particles(m_sphCount);
		for (unsigned int i = 0; i < m_sphCount; i++)
		{
			Particle p = Particle();
			p.position = glm::vec4(0.1 * i, 0., 0., 1.);
			p.mass = 0.1f;
			p.radius = 10;

			particles[i] = p;
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