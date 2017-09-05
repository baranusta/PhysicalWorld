#include "stdafx.h"

#include "Engine.h"
#include "Scene\fluid_scene.h"

int main()
{
	std::cout << "yo!\n";

	try {

		Engine x;
		x.setScene(new FluidScene(100));
		
		int s = 0;
		x.startGame([&](void) {
			s++;
			if (s == 10000)
			{
				physics_engine::PhysicsEngine::getInstance().setIntegrator(physics_engine::Integrator::LEAP_FROG, 0.001f);
			}
			else if (s % 1000 == 0)
			{
				//std::cout << s;
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