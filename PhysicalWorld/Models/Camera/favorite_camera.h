#pragma once

#include <iostream>

#include "camera.h"
#include "..\..\input_controller.h"


class FavoriteCamera : public Camera
{
public:
	bool dir[6] = {false,false, false, false, false, false};

	FavoriteCamera(glm::vec2 size) :
		Camera(size)
	{

		InputController::getInstance().registerMousePos("main_camera", [&](glm::vec2 pos) {
			std::cout << pos.x << " " << pos.y << std::endl;
		});


		InputController::getInstance().registerKey("main_camera", [&](int key, int action) {
			std::cout << key << " " << action << std::endl;
			if (key == GLFW_KEY_W)
				dir[0] = action != GLFW_RELEASE;
			if (key == GLFW_KEY_A)
				dir[1] = action != GLFW_RELEASE;
			if (key == GLFW_KEY_S)
				dir[2] = action != GLFW_RELEASE;
			if (key == GLFW_KEY_D)
				dir[3] = action != GLFW_RELEASE;

			if (key == GLFW_KEY_Q)
				dir[4] = action != GLFW_RELEASE;
			if (key == GLFW_KEY_E)
				dir[5] = action != GLFW_RELEASE;
		});
	}

	~FavoriteCamera()
	{
		InputController::getInstance().unregisterMousePos("main_camera");
		InputController::getInstance().unregisterKey("main_camera");
	}

	void update()
	{
		//std::cout << dir[3] << " " << dir[1] << std::endl;

		glm::vec3 t(0);
		t.x = dir[3] ? 0.001f : dir[1] ? -0.001f : 0;
		t.y = dir[0] ? 0.001f : dir[2] ? -0.001f : 0;
		t.z = dir[4] ? 0.001f : dir[5] ? -0.001f : 0;

		translate(t);
	}

};