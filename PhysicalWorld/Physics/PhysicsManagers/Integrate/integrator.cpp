#include "integrator.h"



void physics_engine::Integrator::updateShaderController(IntegratorTypes type)
{
	if (m_used_integrator == type || INTEGRATOR_SIZE <= type)
		return;
	if(m_used_integrator != INTEGRATOR_SIZE)
		delete m_shader;
	
	m_used_integrator = type;
	m_shader = new ComputeShaderController(integratorShaderSources[type]);

	m_size_index = glGetUniformLocation(m_shader->getProgId(), "size");
	m_timeStep = glGetUniformLocation(m_shader->getProgId(), "timeStep");
}

physics_engine::Integrator::Integrator()
{
	updateShaderController(EULER);
}


physics_engine::Integrator::~Integrator()
{
}

void physics_engine::Integrator::integrate(float timeStep)
{

	glUseProgram(m_shader->getProgId());
	for (auto obj : integrables)
	{
		auto integrable = obj.second;
		//data
		glUniform1ui(m_size_index, integrable->getSize());
		glUniform1f(m_timeStep, timeStep);
		glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, integrable->getPositions());
		glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, integrable->getVelocities());
		glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 2, integrable->getAccelerations());
		glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 3, integrable->getForces());
		glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 4, integrable->getMass());
		m_shader->dispatch((integrable->getSize() + 7) / 8, 1, 1);
	}

	for (auto obj : integrableRotatings)
	{
		auto integrable = obj.second;
		//data
		glUniform1ui(m_size_index, integrable->getSize());
		glUniform1f(m_timeStep, timeStep);
		glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, integrable->getPositions());
		glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, integrable->getAngularVelocities());
		glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 2, integrable->getAngularAccelerations());
		glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 3, integrable->getTorques());
		glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 4, integrable->getMass());
		m_shader->dispatch((integrable->getSize() + 7) / 8, 1, 1);
	}
}

int physics_engine::Integrator::addIntegrable(IntegrableType type, Object * obj)
{
	if (type == NON_ROTATING)
	{
		Integrable* o = dynamic_cast<Integrable*>(obj);
		integrables[integrableInd++] = o;
		return integrableInd;
	}

	IntegrableRotating* o = dynamic_cast<IntegrableRotating*>(obj);
	integrableRotatings[integrableRotInd++] = o;
	return integrableRotInd;
}

void physics_engine::Integrator::removeIntegrable(IntegrableType type, int id)
{
	if (type == NON_ROTATING)
	{
		integrables.erase(id);
	}
	else
	{
		integrableRotatings.erase(id);
	}
}
