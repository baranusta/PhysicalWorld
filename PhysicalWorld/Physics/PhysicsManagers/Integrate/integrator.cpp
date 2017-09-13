#include "integrator.h"



void physics_engine::Integrator::updateShaderController(IntegratorTypes type, float timeStep)
{
	if (m_used_integrator == type || INTEGRATOR_SIZE <= type)
		return;
	if (m_used_integrator != INTEGRATOR_SIZE)
	{
		_convertDataToNormal(timeStep);
		delete m_shader;

	}

	m_used_integrator = type;
	m_shader = new ComputeShaderController(integratorShaderSources[type]);

	m_size_index = glGetUniformLocation(m_shader->getProgId(), "size");
	m_timeStep = glGetUniformLocation(m_shader->getProgId(), "timeStep");
	m_gravity = glGetUniformLocation(m_shader->getProgId(), "gravity");

	_converDataToRequiredForm(timeStep);
}

void physics_engine::Integrator::_convertDataToNormal(float timeStep)
{
	m_shader->setMacro("LAST_RUN", "");
	integrate(timeStep);
	m_shader->unsetMacro("LAST_RUN");
}

void physics_engine::Integrator::_converDataToRequiredForm(float timeStep)
{
	m_shader->setMacro("FIRST_RUN", "");
	integrate(timeStep);
	m_shader->unsetMacro("FIRST_RUN");
}

physics_engine::Integrator::Integrator()
{
	updateShaderController(FORWARD_EULER);
}


physics_engine::Integrator::~Integrator()
{
}

void physics_engine::Integrator::integrate(float timeStep)
{

	glUseProgram(m_shader->getProgId());
	glUniform1f(m_timeStep, timeStep);
	glUniform4f(m_gravity, gravity.x, gravity.y, gravity.z, 0);
	for (auto obj : integrables)
	{
		auto integrable = obj.second;
		//data
		glUniform1ui(m_size_index, integrable->getSize());
		glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, integrable->getPositions());
		glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, integrable->getVelocities());
		glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 2, integrable->getForces());
		glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 3, integrable->getMass());
		m_shader->dispatch((integrable->getSize() + 7) / 8, 1, 1);
	}

	GLuint err;
	while ((err = glGetError()) != GL_NO_ERROR) {
		std::cout << __FILE__ << " " << __LINE__ << " " << "OpenGL error: " << err << gluErrorString(err) << std::endl;
	}

	for (auto obj : integrableRotatings)
	{
		auto integrable = obj.second;
		//data
		glUniform1ui(m_size_index, integrable->getSize());
		glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, integrable->getPositions());
		glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, integrable->getAngularVelocities());
		glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 2, integrable->getTorques());
		glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 3, integrable->getMass());
		m_shader->dispatch((integrable->getSize() + 7) / 8, 1, 1);
	}
}

void physics_engine::Integrator::setIntegrator(IntegratorTypes integratorType, float timeStep)
{
	updateShaderController(integratorType, timeStep);
}

void physics_engine::Integrator::setGravity(glm::vec3 gravity)
{
	this->gravity = gravity;
}

int physics_engine::Integrator::addIntegrable(IntegrableType type, std::shared_ptr<Object> obj)
{
	if (type == NON_ROTATING)
	{
		std::shared_ptr<Integrable> o = std::dynamic_pointer_cast<Integrable>(obj);
		integrables[integrableInd++] = o;
		return integrableInd;
	}

	std::shared_ptr<IntegrableRotating> o = std::dynamic_pointer_cast<IntegrableRotating>(obj);
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
