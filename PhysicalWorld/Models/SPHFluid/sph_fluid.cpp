#include "sph_fluid.h"

SPHFluid::SPHFluid()
{
	//image allocation
	glGenBuffers(SSBO_TYPES_SIZE, ssbo);

	setFluidSSBOs();
}

SPHFluid::~SPHFluid()
{
	glDeleteBuffers(SSBO_TYPES_SIZE, ssbo);
}

void SPHFluid::setFluidSSBOs()
{
	physics_engine::SPHFluid fluid_images;
	fluid_images.ssbo[fluid_images.POSITIONS]= ssbo[POSITIONS];
	fluid_images.ssbo[fluid_images.VELOCITY] = ssbo[VELOCITY];
	fluid_images.ssbo[fluid_images.ACCELERATION] = ssbo[ACCELERATION];
	fluid_images.ssbo[fluid_images.FORCE] = ssbo[FORCE];
	fluid_images.ssbo[fluid_images.RADIUS] = ssbo[RADIUS];
	fluid_images.ssbo[fluid_images.MASS] = ssbo[MASS];
	fluid_images.ssbo[fluid_images.VISCOSITY] = ssbo[VISCOSITY];
	physics_engine::PhysicsEngine::getInstance().setFluid(fluid_images);
}

template<class T>
void SPHFluid::updateSSBO(GLuint ssbo, std::vector<T> data)
{
	void* pos = data.size() > 0 ? &data[0] : NULL;
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, ssbo);
	glBufferData(GL_SHADER_STORAGE_BUFFER, data.size() *
		sizeof(T), pos, GL_DYNAMIC_DRAW);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
}

void SPHFluid::updateSSBOs()
{	
	updateSSBO(ssbo[POSITIONS],m_vec_positions);
	updateSSBO(ssbo[VELOCITY], m_vec_velocity);
	updateSSBO(ssbo[ACCELERATION],m_vec_acceleration);
	updateSSBO(ssbo[FORCE],m_vec_force);
	updateSSBO(ssbo[COLOR_DIFFUSE], m_vec_color_diffuse);
	updateSSBO(ssbo[COLOR_AMBIENT], m_vec_color_ambient);
	updateSSBO(ssbo[COLOR_SPECULAR], m_vec_color_specular);
	updateSSBO(ssbo[MASS], m_vec_mass);
	updateSSBO(ssbo[VISCOSITY], m_vec_radius);
	updateSSBO(ssbo[RADIUS], m_vec_viscosity);
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
	updateSSBOs();
	m_particle_count += p.size();
}

void SPHFluid::render()
{
	//get particle start
}