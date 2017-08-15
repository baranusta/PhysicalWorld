#pragma once

#include "..\Particle\particle.h"
#include "..\..\Physics\physics_engine.h"



class SPHFluid
{
private:
	//ssbo
	enum SSBO_TYPES {
		POSITIONS,
		VELOCITY,
		ACCELERATION,
		FORCE,
		COLOR_DIFFUSE,
		COLOR_AMBIENT,
		COLOR_SPECULAR,
		MASS,
		RADIUS,
		VISCOSITY,
		SSBO_TYPES_SIZE
	};

	GLuint ssbo[SSBO_TYPES_SIZE];
	
	//values
	std::vector<glm::vec3> m_vec_positions;
	std::vector<glm::vec3> m_vec_velocity;
	std::vector<glm::vec3> m_vec_acceleration;
	std::vector<glm::vec3> m_vec_force;
	
	std::vector<glm::vec3> m_vec_color_diffuse;
	std::vector<glm::vec3> m_vec_color_ambient;
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
	
	void resizeVectors(int more_size);
	void addParticle(Particle particle);


public:
	SPHFluid();
	~SPHFluid();
	
	//getter
	int getParticleCount();

	void addParticles(std::vector<Particle>);
	void render();
};