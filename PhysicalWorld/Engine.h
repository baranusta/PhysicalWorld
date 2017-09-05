#pragma once

#include "stdafx.h"

#include "Models\SPHFluid\sph_fluid.h"
#include "Scene\scene_manager.h"
#include "input_controller.h"

class Engine
{
private:
	void initializeWindow();

	glm::vec2 m_size;

	GLFWwindow* window;

	//Components
	SceneManager m_scene_manager;

	float m_timeStep = 0.00001f;

public:
	Engine(glm::vec2 size = glm::vec2(800,600));
	~Engine();

	void setScene(Scene*);

	void startGame(std::function<void(void)> gameloop);


};