#include "sph_default.h"

int physics_engine::SPHDefault::addParticles(Particle * particles)
{
	if (SPHFluid* fluidParticles = dynamic_cast<SPHFluid*>(particles))
	{
		m_fluids[addedSystemCount] = (fluidParticles);
		return addedSystemCount++;
	}
	else
	{
		throw std::invalid_argument("Invalid particle system and particles.");
	}
}

int physics_engine::SPHDefault::removeParticles(int id)
{
	if (m_fluids.size() == 0 || m_fluids.find(id) == m_fluids.end())
	{
		return 0;
	}
	m_fluids.erase(id);
	return m_fluids.size();
}

void physics_engine::SPHDefault::computeForces()
{

	glUseProgram(m_shader.getProgId());
	for (auto pair : m_fluids)
	{
		auto fluid = pair.second;
		//data
		glUniform1ui(size_index, fluid->getSize());
		glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, fluid->getPositions());
		glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, fluid->getVelocities());
		glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 2, fluid->getAccelerations());
		glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 3, fluid->getForces());
		glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 4, fluid->getRadius());
		glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 5, fluid->getViscosities());
		glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 6, fluid->getMass());

		GLuint err;
		while ((err = glGetError()) != GL_NO_ERROR) {
			std::cout << __FILE__ << " " << __LINE__ << " " << "OpenGL error: " << err << gluErrorString(err) << std::endl;
		}
		m_shader.dispatch((fluid->getSize() + 7) / 8, 1, 1);
	}
}