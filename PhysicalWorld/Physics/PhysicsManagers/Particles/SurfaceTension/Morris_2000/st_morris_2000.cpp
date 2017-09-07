#include "st_morris_2000.h"

physics_engine::ST_Morris_2000::ST_Morris_2000()
	:m_shader("Physics\\PhysicsManagers\\Particles\\SurfaceTension\\Morris_2000\\morris_2000.comp")
{
	m_index_size = glGetUniformLocation(m_shader.getProgId(), "size");
	m_index_type = glGetUniformLocation(m_shader.getProgId(), "type");
	m_index_tension_coef = glGetUniformLocation(m_shader.getProgId(), "tension_coef");
}

void physics_engine::ST_Morris_2000::computeSurfaceTensionForce(const SPHFluid & fluid)
{
	m_shader.setMacro("THREAD_COUNT_X", 8);
	glUseProgram(m_shader.getProgId());

	//data
	glUniform1ui(m_index_size, fluid.getSize());

	////
	////Calculate n
	////
	glUniform1f(m_index_tension_coef, fluid.getTensionCoef());
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, fluid.getPositions());
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, fluid.getSurfaceNormals());
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 2, fluid.getDensities());
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 3, fluid.getRadius());
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 4, fluid.getMass());
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 5, fluid.getForces());

	glUniform1ui(m_index_type, 0);
	m_shader.dispatch(DIV_CEIL(fluid.getSize(), 8), 1, 1);
	std::vector<glm::vec4> positions(fluid.getSize());
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, fluid.getSurfaceNormals()); // 
	GLvoid* s = glMapBuffer(GL_SHADER_STORAGE_BUFFER, GL_READ_ONLY);

	memcpy(&positions[0], s, sizeof(glm::vec4) * fluid.getSize());
	glUnmapBuffer(GL_SHADER_STORAGE_BUFFER);

	////
	////Calculate ro * k * n
	////
	glUniform1ui(m_index_type, 1);
	m_shader.dispatch(DIV_CEIL(fluid.getSize(), 8), 1, 1);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, fluid.getForces()); // 
	GLvoid* a = glMapBuffer(GL_SHADER_STORAGE_BUFFER, GL_READ_ONLY);

	memcpy(&positions[0], a, sizeof(glm::vec4) * fluid.getSize());
	glUnmapBuffer(GL_SHADER_STORAGE_BUFFER);
}
