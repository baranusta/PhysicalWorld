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