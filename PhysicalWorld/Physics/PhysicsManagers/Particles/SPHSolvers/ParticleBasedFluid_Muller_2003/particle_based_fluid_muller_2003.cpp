#include "particle_based_fluid_muller_2003.h"
#include "..\..\..\..\..\input_controller.h"


int threadCountDensityX = 8;
int threadCountPressureX = 8;
int threadCount_f_PressureX = 8;
int threadCount_f_ViscosityX = 8;

bool a = false;
void physics_engine::PBF2003::computeDensity()
{
	m_shader_density.setMacro("THREAD_COUNT_X", threadCountDensityX);
	glUseProgram(m_shader_density.getProgId());

	//data
	glUniform1ui(index_size_density, m_fluid->getSize());
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, m_fluid->getPositions());
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, m_fluid->getRadius());
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 2, m_fluid->getMass());
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 3, m_fluid->getDensities());



	GLuint err;
	while ((err = glGetError()) != GL_NO_ERROR) {
		std::cout << __FILE__ << " " << __LINE__ << " " << "OpenGL error: " << err << gluErrorString(err) << std::endl;
	}
	m_shader_density.dispatch(DIV_CEIL(m_fluid->getSize(), threadCountDensityX), 1, 1);

}

void physics_engine::PBF2003::computePressure()
{
	m_shader_pressure.setMacro("THREAD_COUNT_X", threadCountPressureX);
	glUseProgram(m_shader_pressure.getProgId());

	//data
	glUniform1ui(index_size_pressure, m_fluid->getSize());
	glUniform1f(index_k_gas_factor, K_GAS_FACTOR);

	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, m_fluid->getRestDensities());
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, m_fluid->getDensities());
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 2, m_fluid->getPressures());

	GLuint err;
	while ((err = glGetError()) != GL_NO_ERROR) {
		std::cout << __FILE__ << " " << __LINE__ << " " << "OpenGL error: " << err << gluErrorString(err) << std::endl;
	}
	m_shader_pressure.dispatch(DIV_CEIL(m_fluid->getSize(), threadCountDensityX), 1, 1);

}

void physics_engine::PBF2003::computeForcePressure_Viscosity()
{
	m_shader_force.setMacro("THREAD_COUNT_X", threadCount_f_PressureX);
	glUseProgram(m_shader_force.getProgId());

	//data
	glUniform1ui(index_size_f, m_fluid->getSize());

	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, m_fluid->getPositions());
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, m_fluid->getVelocities());
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 2, m_fluid->getDensities());
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 3, m_fluid->getPressures());
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 4, m_fluid->getViscosities());
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 5, m_fluid->getRadius());
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 6, m_fluid->getMass());
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 7, m_fluid->getForces());

	GLuint err;
	while ((err = glGetError()) != GL_NO_ERROR) {
		std::cout << __FILE__ << " " << __LINE__ << " " << "OpenGL error: " << err << gluErrorString(err) << std::endl;
	}

	glUniform1ui(index_type_f, 0);
	m_shader_force.dispatch(DIV_CEIL(m_fluid->getSize(), threadCountDensityX), 1, 1);


	glUniform1ui(index_type_f, 1);
	m_shader_force.dispatch(DIV_CEIL(m_fluid->getSize(), threadCountDensityX), 1, 1);

}

void physics_engine::PBF2003::computeSurfaceTensionForce()
{
	m_f_tension_solver.computeSurfaceTensionForce(*m_fluid);
}

void physics_engine::PBF2003::setParticles(std::shared_ptr<Particle> particles)
{

	if (auto fluidParticles = std::dynamic_pointer_cast<SPHFluid>(particles))
	{
		m_fluid = fluidParticles;
	}
	else
	{
		throw std::invalid_argument("Invalid particle system and particles.");
	}

	InputController::getInstance().registerKey("debug", [&](int key, int action) {
		if (key == GLFW_KEY_A)
			a = action == GLFW_PRESS;
	});
}

void physics_engine::PBF2003::computeInternalForces()
{
	computeDensity();
	computePressure();

	//if (a)
	//{
	//	std::vector<glm::vec4> pos(m_fluid->getSize());
	//	glBindBuffer(GL_SHADER_STORAGE_BUFFER, m_fluid->getPositions()); // 
	//	GLvoid* s = glMapBuffer(GL_SHADER_STORAGE_BUFFER, GL_READ_ONLY);

	//	memcpy(&pos[0], s, sizeof(glm::vec4) * m_fluid->getSize());
	//	glUnmapBuffer(GL_SHADER_STORAGE_BUFFER);
	//}
	//computeSurfaceTensionForce();
	computeForcePressure_Viscosity();

}


void physics_engine::PBF2003::computeExternalForces(glm::vec3 gravity)
{
	m_shader_force.setMacro("THREAD_COUNT_X", threadCount_f_PressureX);
	glUseProgram(m_shader_force.getProgId());

	//data
	glUniform1ui(index_size_f, m_fluid->getSize());
	//glUniform3f(index_gravity_f, gravity.x, gravity.y, gravity.z);

	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, m_fluid->getPositions());
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, m_fluid->getVelocities());
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 2, m_fluid->getDensities());
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 3, m_fluid->getPressures());
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 4, m_fluid->getViscosities());
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 5, m_fluid->getRadius());
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 6, m_fluid->getMass());
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 7, m_fluid->getForces());

	GLuint err;
	while ((err = glGetError()) != GL_NO_ERROR) {
		std::cout << __FILE__ << " " << __LINE__ << " " << "OpenGL error: " << err << gluErrorString(err) << std::endl;
	}
	
	glUniform1ui(index_type_f, 2);
	m_shader_force.dispatch(DIV_CEIL(m_fluid->getSize(), threadCountDensityX), 1, 1);

}
