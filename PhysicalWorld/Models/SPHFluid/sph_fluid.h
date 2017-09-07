#pragma once

#include "..\Particle\particle.h"
#include "..\..\Physics\physics_engine.h"
#include "..\..\Physics\Models\sph_fluid.h"
#include "..\..\Render\render_engine.h"
#include "..\..\Render\Renderers\fluid_renderer.h"



class SPHFluid
{
private:
	//ssbo
	enum SSBO_TYPES {
		POSITIONS,
		VELOCITY,
		FORCE,
		REST_DENSITY,
		COLOR_DIFFUSE,
		COLOR_AMBIENT,
		COLOR_SPECULAR,
		MASS,
		RADIUS,
		VISCOSITY,
		SSBO_TYPES_SIZE
	};

	//item ID's
	int m_rendererId;
	int m_physicsId;

	GLuint ssbo[SSBO_TYPES_SIZE];
	std::shared_ptr<physics_engine::SPHFluid> m_physics_ssbo;
	
	//values
	std::vector<glm::vec4> m_vec_positions;
	std::vector<glm::vec4> m_vec_velocity;
	std::vector<glm::vec4> m_vec_force;
	std::vector<float> m_vec_rest_density;
	
	std::vector<glm::vec4> m_vec_color_diffuse;
	std::vector<glm::vec4> m_vec_color_ambient;
	std::vector<float> m_vec_color_specular;

	std::vector<float> m_vec_mass;
	std::vector<float> m_vec_radius;
	std::vector<float> m_vec_viscosity;

	int m_particle_count = 0;
private:

	template<class T>
	void updateSSBO(GLuint ssbo, std::vector<T> data);
	void updateSSBOs();
	void setFluidSSBOs();
	void setRenderer();
	
	void resizeVectors(int more_size);
	void addParticle(Particle particle);


public:
	SPHFluid(physics_engine::ParticleSystemTypes type = physics_engine::ParticleSystemTypes::PBF_MULLER_2003);
	~SPHFluid();

	
	//getter
	int getParticleCount();

	void addParticles(const std::vector<Particle>&);
	void setSurfaceTensionCoef(float coef);
};