#pragma once

#include "stdafx.h"

#include "Models\SPHFluid\sph_fluid.h"

class Engine
{
private:
	void initializeWindow();

	int m_height;
	int m_width;

	int m_contextHandle;

	//Components
	SPHFluid* m_sphfluid;

public:
	Engine(int height = 600, int width = 800);
	~Engine();

	SPHFluid* getSPHFluid();

	void addSPHFluid();
	void removeSPHFluid();


};