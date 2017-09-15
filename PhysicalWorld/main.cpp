#include "stdafx.h"

#include "Engine.h"
#include "Scene\fluid_scene.h"

extern "C" {
	_declspec(dllexport) DWORD NvOptimusEnablement = 0x00000001;
}


int main()
{
	std::cout << "yo!\n";
	InputController::getInstance().registerKey("shader compile - main", [](int key, int action) {
		if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
			ShaderController::markAllDirty();
	});

	try {

		Engine x;
		x.setScene(new FluidScene(1000));
		
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