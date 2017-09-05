#pragma once

#include "stdafx.h"

#include "Models\SPHFluid\sph_fluid.h"
#include "Scene\scene_manager.h"

class Engine
{
private:
	void initializeWindow();

	int m_height;
	int m_width;

	GLFWwindow* window;

	//Components
	SceneManager m_scene_resolver;

	float m_timeStep = 0.00001f;

public:
	Engine(int height = 600, int width = 800);
	~Engine();

	void setScene(Scene*);
	//add bisiler gelcek buraya

	void startGame(std::function<void(void)> gameloop);


};