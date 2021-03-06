#include "sph_fluid.h"


SPHFluid::SPHFluid(physics_engine::PhysicsEngine& pEngine, physics_engine::ParticleSystemTypes type)
	:m_physicsEngine(pEngine)
{
	m_physics_ssbo = std::make_shared<physics_engine::SPHFluid>();

	m_physicsEngine.setParticleSystem(type, std::static_pointer_cast<physics_engine::Particle> (m_physics_ssbo));

	//image allocation
	glGenBuffers(SSBO_TYPES_SIZE, ssbo);
	setFluidSSBOs();
	setRenderer();
}

SPHFluid::~SPHFluid()
{
	glDeleteBuffers(SSBO_TYPES_SIZE, ssbo);
	render_engine::RenderEngine::getInstance().removeRenderer(m_rendererId);
	m_physicsEngine.remove(physics_engine::PhysicsEngine::FLUID);
}

void SPHFluid::setFluidSSBOs()
{
	m_physics_ssbo->setPositions(ssbo[POSITIONS]);
	m_physics_ssbo->setVelocities(ssbo[VELOCITY]);
	m_physics_ssbo->setForces(ssbo[FORCE]);
	m_physics_ssbo->setRestDensities(ssbo[REST_DENSITY]);
	m_physics_ssbo->setRadius(ssbo[RADIUS]);
	m_physics_ssbo->setMass(ssbo[MASS]);
	m_physics_ssbo->setViscosities(ssbo[VISCOSITY]);
}

void SPHFluid::setRenderer()
{
	auto renderer = std::unique_ptr<render_engine::FluidRenderer>(new render_engine::FluidRenderer);

	renderer->setBuffer<glm::vec4>(BUF_POSITION, ssbo[POSITIONS]);
	renderer->setBuffer<float>(BUF_RADIUS, ssbo[RADIUS]);
	renderer->setBuffer<float>(BUF_C_SPECULAR, ssbo[COLOR_SPECULAR]);
	renderer->setBuffer<glm::vec4>(BUF_C_AMBIENT, ssbo[COLOR_AMBIENT]);
	renderer->setBuffer<glm::vec4>(BUF_C_DIFFUSE, ssbo[COLOR_DIFFUSE]);

#ifdef _DEBUG
	renderer->setBuffer<float>(BUF_MASS, ssbo[MASS]);
	renderer->setBuffer<float>(BUF_FORCE, ssbo[FORCE]);
	renderer->setBuffer<float>(BUF_VISCOSITY, ssbo[VISCOSITY]);
#endif
	renderer->setCount(m_particle_count);
	m_rendererId = render_engine::RenderEngine::getInstance().addRenderer(std::move(renderer));
}

template<class T>
void SPHFluid::updateSSBO(GLuint ssbo, std::vector<T> data)
{
	void* dataIndex = data.size() > 0 ? &data[0] : NULL;
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, ssbo);
	glBufferData(GL_SHADER_STORAGE_BUFFER, data.size() *
		sizeof(T), dataIndex, GL_STATIC_DRAW);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
}

void SPHFluid::updateSSBOs()
{
	m_physics_ssbo->setSize(m_particle_count);

	updateSSBO(ssbo[POSITIONS],m_vec_positions);
	updateSSBO(ssbo[VELOCITY], m_vec_velocity);
	updateSSBO(ssbo[FORCE],m_vec_force);
	updateSSBO(ssbo[REST_DENSITY], m_vec_rest_density);
	updateSSBO(ssbo[COLOR_DIFFUSE], m_vec_color_diffuse);
	updateSSBO(ssbo[COLOR_AMBIENT], m_vec_color_ambient);
	updateSSBO(ssbo[COLOR_SPECULAR], m_vec_color_specular);
	updateSSBO(ssbo[MASS], m_vec_mass);
	updateSSBO(ssbo[VISCOSITY], m_vec_viscosity);
	updateSSBO(ssbo[RADIUS], m_vec_radius);
	
}

void SPHFluid::resizeVectors(int more_size)
{
	m_vec_positions.reserve(more_size);
	m_vec_velocity.reserve(more_size);
	m_vec_force.reserve(more_size);
	m_vec_rest_density.reserve(more_size);
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
	m_vec_force.push_back(particle.force);
	m_vec_rest_density.push_back(particle.rest_density);
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

void SPHFluid::addParticles(const std::vector<Particle>& p)
{
	resizeVectors(p.size());
	for (Particle particle : p)
	{
		addParticle(particle);
	}
	m_particle_count += p.size();
	updateSSBOs();
	render_engine::RenderEngine::getInstance().setRendererVertexCount(m_rendererId, m_particle_count);
}

void SPHFluid::setSurfaceTensionCoef(float coef)
{
	m_physics_ssbo->setTensionCoef(coef);
}
