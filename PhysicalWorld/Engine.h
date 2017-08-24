#pragma once

#include "stdafx.h"

#include "Models\SPHFluid\sph_fluid.h"

class Engine
{
private:
	void initializeWindow();

	int m_height;
	int m_width;

	GLFWwindow* window;

	//Components
	SPHFluid* m_sphfluid;

	float m_timeStep = 0.00001;

public:
	Engine(int height = 600, int width = 800);
	~Engine();

	SPHFluid* getSPHFluid();

	void addSPHFluid();
	void removeSPHFluid();

	void startGame(std::function<void(void)> gameloop);


};