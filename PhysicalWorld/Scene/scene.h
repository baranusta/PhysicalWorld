#pragma once

#include "..\Models\SPHFluid\sph_fluid.h"
#include "..\Models\Camera\camera.h"

class Scene
{
public:
	Scene();
	virtual ~Scene();

	virtual glm::vec3 getGravity();

	virtual void addSPHFluids(std::vector<std::unique_ptr<SPHFluid>>& fluids, physics_engine::PhysicsEngine&);
	virtual std::vector<int> getStaticObjects();
	virtual std::vector<int> getMovingObjects();
	virtual std::vector<int> getLights();
	//
	//get other scene spesific info
	//

	virtual std::vector<std::shared_ptr<Camera>> getCameras(glm::vec2 size);
	
};

