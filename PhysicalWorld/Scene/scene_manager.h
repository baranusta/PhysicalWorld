#pragma once

#include <functional>

#include "scene.h"

#include "..\Models\SPHFluid\sph_fluid.h"

#include "..\Render\render_engine.h"
#include "..\Physics\physics_engine.h"

class SceneManager
{
private:
	std::vector<std::unique_ptr<SPHFluid>> m_fluids;

	glm::vec2 m_size;
	std::vector<std::shared_ptr<Camera>> m_cameras;

public:
	SceneManager(glm::vec2 size);

	//takes a scene pointer and deletes after it is resolved	
	void resolveScene(Scene* scene);
	void clean();

	void update();

	std::vector<std::shared_ptr<Camera>> getCameras();

};

