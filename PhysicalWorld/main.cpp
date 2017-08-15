#include "stdafx.h"

#include "Engine.h"

int main()
{
	std::cout << "yo!\n";

	Engine x;
	x.addSPHFluid();

	auto f = x.getSPHFluid();
	f->addParticles({ Particle() });
	std::cout << f->getParticleCount();
	return 0;
}