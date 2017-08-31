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
		p.mass = 1;
		Particle c = Particle();
		c.mass = 1;
		c.position = glm::vec4(0., 0.7, 0., 1.);
		f->addParticles({ p,c });
		x.startGame([](void) {

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