#include "sph_fluid.h"

SPHFluid::SPHFluid() 
{
	//image allocation
	physics_engine::SPHFluid fluid_images;

	fluid_images.positions = 0;
	fluid_images.velocity = 0;
	fluid_images.acceleration = 0;
	fluid_images.force = 0;

	fluid_images.color_diffuse = 0;
	fluid_images.ambient_diffuse = 0;
	fluid_images.specular_diffuse = 0;

	fluid_images.mass = 0;
	fluid_images.radius = 0;
	fluid_images.viscosity = 0;
	physics_engine::PhysicsEngine::getInstance().setFluid(fluid_images);
}

void SPHFluid::updateImages(int startIndex, int length)
{

}

void SPHFluid::resizeVectors(int more_size)
{
	m_vec_positions.reserve(more_size);
	m_vec_velocity.reserve(more_size);
	m_vec_acceleration.reserve(more_size);
	m_vec_force.reserve(more_size);
	m_vec_color_diffuse.reserve(more_size);
	m_vec_color_ambient.reserve(more_size);
	m_vec_color_specular.reserve(more_size);
	m_vec_mass.reserve(more_size);
	m_vec_radius.reserve(more_size);
	m_vec_viscosity.reserve(more_size);
}

void SPHFluid::addParticle(Particle particle)
{
	m_vec_positions.push_back(particle.position);
	m_vec_velocity.push_back(particle.velocity);
	m_vec_acceleration.push_back(particle.acceleration);
	m_vec_force.push_back(particle.force);
	m_vec_color_diffuse.push_back(particle.color_diffuse);
	m_vec_color_ambient.push_back(particle.color_ambient);
	m_vec_color_specular.push_back(particle.color_specular);
	m_vec_mass.push_back(particle.mass);
	m_vec_radius.push_back(particle.radius);
	m_vec_viscosity.push_back(particle.viscosity);
}

int SPHFluid::getParticleCount()
{
	return m_particle_count;
}

void SPHFluid::addParticles(std::vector<Particle> p)
{
	resizeVectors(p.size());
	for (Particle particle : p)
	{
		addParticle(particle);
	}
	updateImages(m_vec_positions.size() - p.size(), p.size());
	m_particle_count += p.size();
}

void SPHFluid::render()
{
	//get particle start
}