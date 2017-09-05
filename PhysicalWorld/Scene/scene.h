#pragma once

#include "..\Models\Particle\particle.h"
#include "..\Models\Camera\camera.h"

class Scene
{
public:
	Scene();
	virtual ~Scene();

	virtual std::vector<Particle> getSPHParticles();
	virtual std::vector<int> getStaticObjects();
	virtual std::vector<int> getMovingObjects();
	virtual std::vector<int> getLights();
	//
	//get other scene spesific info
	//

	virtual Camera getCamera();
	
};

