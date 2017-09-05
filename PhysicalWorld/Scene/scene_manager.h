#pragma once

#include <functional>

#include "scene.h"

#include "..\Models\SPHFluid\sph_fluid.h"

#include "..\Render\render_engine.h"
#include "..\Physics\physics_engine.h"

class SceneManager
{
private:
	SPHFluid* m_fluid;

	void destroyScene();

	void addFluid(const std::vector<Particle>&);
public:
	SceneManager();
	~SceneManager();

	//takes a scene pointer and deletes after it is resolved	
	void resolveScene(Scene* scene);
	void clean();

};

