#include "stdafx.h"

#include "Engine.h"

int main()
{
	std::cout << "yo!\n";

	try {

		Engine x;
		x.addSPHFluid();
		auto f = x.getSPHFluid();
		Particle p = Particle();
		p.position = glm::vec4(0., 0., 0., 1.);
		p.mass = 0.1;
		Particle c = Particle();
		c.mass = 0.1;
		c.position = glm::vec4(0., 0.7, 0., 1.);
		f->addParticles({ p,c });
		int s = 0;
		x.startGame([&](void) {
			s++;
			if (s == 10000)
			{
				physics_engine::PhysicsEngine::getInstance().setIntegrator(physics_engine::Integrator::LEAP_FROG, 0.001);
			}
			else if (s % 1000 == 0)
			{
				std::cout << s;
			}
		});
	}
	catch (const char* t)
	{
		std::cout << t << std::endl;
	}
	catch (std::string t)
	{
		std::cout << t << std::endl;
	}
	return 0;
}