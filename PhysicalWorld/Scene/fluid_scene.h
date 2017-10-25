#pragma once

#include "scene.h"
#include "..\Models\Camera\favorite_camera.h"

class FluidScene : public Scene
{
	size_t m_sphCount;
	glm::vec4 m_gravity;
public:
	FluidScene(int sphCount)
	{
		m_sphCount = sphCount;
	}

	void addSPHFluids(std::vector<std::unique_ptr<SPHFluid>>& fluids, physics_engine::PhysicsEngine& pEngine)
	{
		auto fluid = std::unique_ptr<SPHFluid>(new SPHFluid(pEngine));
		unsigned int x = (unsigned int)glm::pow(m_sphCount, 1.f / 3.f);
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
					p.mass = 10.0f;
					p.radius = 1.8f;
					p.viscosity = .00f;
					p.rest_density = 3.f;

					particles[t++] = p;
				}
			}
		}
		fluid->setSurfaceTensionCoef(1.5f);
		fluid->addParticles(particles);

		fluids.push_back(std::move(fluid));
	}

	std::vector<std::shared_ptr<Camera>> getCameras(glm::vec2 size)
	{
		std::shared_ptr<Camera> cam = std::shared_ptr<FavoriteCamera>(new FavoriteCamera(size));
		cam->setCenter(glm::vec3(0.f, 0.f, 2.f));
		cam->setLookAt(glm::vec3(0.f, 0.f, 0.f));
		cam->setUp(glm::vec3(0.f, 1.f, 0.f));
		cam->updateProjection();
		cam->updateView();

		return {cam};
	}

	glm::vec3 getGravity()
	{
		return glm::vec3(0, -15.8, 0);
	}
};