#include "particle_based_fluid_muller_2003.h"


#define DIV_CEIL(X,Y) ((X + Y - 1) / Y)
int threadCountDensityX = 8;
int threadCountPressureX = 8;
int threadCount_f_PressureX = 8;
int threadCount_f_ViscosityX = 8;

void physics_engine::PBF2003::computeDensity()
{
	m_shader_density.setMacro("THREAD_COUNT_X", threadCountDensityX);
	glUseProgram(m_shader_density.getProgId());

	for (auto pair : m_fluids)
	{
		auto fluid = pair.second;
		//data
		glUniform1ui(index_size_density, fluid->getSize());
		glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, fluid->getPositions());
		glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, fluid->getRadius());
		glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 2, fluid->getMass());
		glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 3, fluid->getDensities());



		GLuint err;
		while ((err = glGetError()) != GL_NO_ERROR) {
			std::cout << __FILE__ << " " << __LINE__ << " " << "OpenGL error: " << err << gluErrorString(err) << std::endl;
		}
		m_shader_density.dispatch(DIV_CEIL(fluid->getSize(), threadCountDensityX), 1, 1);
	}
}

void physics_engine::PBF2003::computePressure()
{
	m_shader_pressure.setMacro("THREAD_COUNT_X", threadCountPressureX);
	glUseProgram(m_shader_pressure.getProgId());

	for (auto pair : m_fluids)
	{
		auto fluid = pair.second;
		//data
		glUniform1ui(index_size_pressure, fluid->getSize());
		glUniform1f(index_k_gas_factor, K_GAS_FACTOR);

		glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, fluid->getRestDensities());
		glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, fluid->getDensities());
		glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 2, fluid->getPressures());

		GLuint err;
		while ((err = glGetError()) != GL_NO_ERROR) {
			std::cout << __FILE__ << " " << __LINE__ << " " << "OpenGL error: " << err << gluErrorString(err) << std::endl;
		}
		m_shader_pressure.dispatch(DIV_CEIL(fluid->getSize(), threadCountDensityX), 1, 1);
	}
}

void physics_engine::PBF2003::computePressureForce()
{
	m_shader_f_pressure.setMacro("THREAD_COUNT_X", threadCount_f_PressureX);
	glUseProgram(m_shader_f_pressure.getProgId());

	for (auto pair : m_fluids)
	{
		auto fluid = pair.second;
		//data
		glUniform1ui(index_size_f_pressure, fluid->getSize());
		glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, fluid->getPositions());
		glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, fluid->getDensities());
		glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 2, fluid->getPressures());
		glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 3, fluid->getRadius());
		glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 4, fluid->getMass());
		glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 5, fluid->getForces());

		GLuint err;
		while ((err = glGetError()) != GL_NO_ERROR) {
			std::cout << __FILE__ << " " << __LINE__ << " " << "OpenGL error: " << err << gluErrorString(err) << std::endl;
		}
		m_shader_f_pressure.dispatch(DIV_CEIL(fluid->getSize(), threadCountDensityX), 1, 1);
	}
}

void physics_engine::PBF2003::computeViscosityForce()
{
	m_shader_f_viscosity.setMacro("THREAD_COUNT_X", threadCount_f_ViscosityX);
	glUseProgram(m_shader_f_viscosity.getProgId());

	for (auto pair : m_fluids)
	{
		auto fluid = pair.second;
		//data
		glUniform1ui(index_size_f_viscosity, fluid->getSize());
		glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, fluid->getPositions());
		glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, fluid->getVelocities());
		glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 2, fluid->getDensities());
		glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 3, fluid->getViscosities());
		glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 4, fluid->getRadius());
		glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 5, fluid->getMass());
		glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 5, fluid->getForces());

		GLuint err;
		while ((err = glGetError()) != GL_NO_ERROR) {
			std::cout << __FILE__ << " " << __LINE__ << " " << "OpenGL error: " << err << gluErrorString(err) << std::endl;
		}
		m_shader_f_viscosity.dispatch(DIV_CEIL(fluid->getSize(), threadCountDensityX), 1, 1);
	}

}

int physics_engine::PBF2003::addParticles(Particle * particles)
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

int physics_engine::PBF2003::removeParticles(int id)
{
	if (m_fluids.size() == 0 || m_fluids.find(id) == m_fluids.end())
	{
		return 0;
	}
	m_fluids.erase(id);
	return m_fluids.size();
}

void physics_engine::PBF2003::computeForces()
{
	computeDensity();
	computePressure();
	computePressureForce();
	//glBindBuffer(GL_SHADER_STORAGE_BUFFER, m_fluids[0]->getPositions()); // 
	//GLvoid* s = glMapBuffer(GL_SHADER_STORAGE_BUFFER, GL_READ_ONLY);

	//std::vector<glm::vec4> positions(m_fluids[0]->getSize());
	//memcpy(&positions[0], s, sizeof(glm::vec4) * m_fluids[0]->getSize());
	//glUnmapBuffer(GL_SHADER_STORAGE_BUFFER);

// 	computeViscosityForce();
}