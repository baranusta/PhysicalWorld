#pragma once

#include "..\Particle\particle.h"
#include "..\..\Physics\physics_engine.h"

class SPHFluid
{
private:
	//images
	int m_img_positions;
	int m_img_velocity;
	int m_img_acceleration;
	int m_img_force;

	int m_img_color_diffuse;
	int m_img_color_ambient;
	int m_img_color_specular;

	int m_img_mass;
	int m_img_radius;
	int m_img_viscosity;
	
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
	void updateImages(int startIndex, int length);
	void resizeVectors(int more_size);
	void addParticle(Particle particle);

public:
	SPHFluid();
	//getter
	int getParticleCount();

	void addParticles(std::vector<Particle>);
	void render();
};