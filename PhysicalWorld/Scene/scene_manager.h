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

	glm::vec2 m_size;
	std::vector<Camera*> m_cameras;

	void destroyScene();

	void addFluid(const std::vector<Particle>&);
public:
	SceneManager(glm::vec2 size);
	~SceneManager();

	//takes a scene pointer and deletes after it is resolved	
	void resolveScene(Scene* scene);
	void clean();

	void update();

	std::vector<Camera*> getCameras();

};

