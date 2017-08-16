#pragma once

#include "sph_strategies.h"
#include "..\..\..\..\ShaderController\compute_shader_controller.h"
#include "..\..\..\..\glm\glm.hpp"


namespace physics_engine
{
	class DummySphStrategy: public SPHStrategies
	{
	private:
		ComputeShaderController m_shader;
		GLuint size_index;
	public:
		DummySphStrategy()
			: m_shader("Physics\\PhysicsManagers\\Fluid\\SPHStrategies\\dummy_sph_compute.glsl")
		{
			glUseProgram(m_shader.getProgId());
			
			size_index = glGetUniformLocation(m_shader.getProgId(), "size");
		}

		void update(SPHFluid fluid) {

			GLuint err;
			while ((err = glGetError()) != GL_NO_ERROR) {
				std::cout << __FILE__ << " " << __LINE__ << " " << "OpenGL error: " << err << gluErrorString(err) << std::endl;
			}

			glUseProgram(m_shader.getProgId());
			while ((err = glGetError()) != GL_NO_ERROR) {
				std::cout << __FILE__ << " " << __LINE__ << " " << "OpenGL error: " << err << gluErrorString(err) << std::endl;
			}
			//data
			glUniform1ui(size_index, fluid.size);
			glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, fluid.ssbo[fluid.POSITIONS]);
			glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, fluid.ssbo[fluid.VELOCITY]);
			glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 2, fluid.ssbo[fluid.ACCELERATION]);
			glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 3, fluid.ssbo[fluid.FORCE]);
			glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 4, fluid.ssbo[fluid.RADIUS]);
			glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 5, fluid.ssbo[fluid.VISCOSITY]);
			glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 6, fluid.ssbo[fluid.MASS]);

			while ((err = glGetError()) != GL_NO_ERROR) {
				std::cout << __FILE__ << " " << __LINE__ << " " << "OpenGL error: " << err << gluErrorString(err) << std::endl;
			}
			m_shader.dispatch((fluid.size + 7)/8,1,1);
			glMemoryBarrier(GL_VERTEX_ATTRIB_ARRAY_BARRIER_BIT);
		}
	};
}