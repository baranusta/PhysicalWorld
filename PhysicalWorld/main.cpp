#include "stdafx.h"

#include "Engine.h"

int main()
{
	std::cout << "yo!\n";

	try {

		Engine x;
		x.addSPHFluid();

		auto f = x.getSPHFluid();
		f->addParticles({ Particle() });
		std::cout << f->getParticleCount();
		physics_engine::PhysicsEngine::getInstance().update();
	}
	catch (const char* t)
	{
		std::cout << t;
	}
	return 0;
}