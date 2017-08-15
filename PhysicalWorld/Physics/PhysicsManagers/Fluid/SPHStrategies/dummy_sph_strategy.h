#pragma once

#include "sph_strategies.h"
#include "..\..\..\..\ShaderController\compute_shader_controller.h"



namespace physics_engine
{
	class DummySphStrategy: public SPHStrategies
	{
	private:
		ComputeShaderController m_shader;
		SPHFluid fluid_block_indexes;
	public:
		DummySphStrategy()
			: m_shader("Physics\\PhysicsManagers\\Fluid\\SPHStrategies\\dummy_sph_compute.glsl")
		{
			fluid_block_indexes.ssbo[fluid_block_indexes.POSITIONS] = glGetProgramResourceIndex(m_shader.getProgId(), GL_SHADER_STORAGE_BLOCK, "position_ssbo");
			fluid_block_indexes.ssbo[fluid_block_indexes.VELOCITY] = glGetProgramResourceIndex(m_shader.getProgId(), GL_SHADER_STORAGE_BLOCK, "velocity_ssbo");
			fluid_block_indexes.ssbo[fluid_block_indexes.ACCELERATION] = glGetProgramResourceIndex(m_shader.getProgId(), GL_SHADER_STORAGE_BLOCK, "acceleration_ssbo");
			fluid_block_indexes.ssbo[fluid_block_indexes.FORCE] = glGetProgramResourceIndex(m_shader.getProgId(), GL_SHADER_STORAGE_BLOCK, "force_ssbo");
			fluid_block_indexes.ssbo[fluid_block_indexes.RADIUS] = glGetProgramResourceIndex(m_shader.getProgId(), GL_SHADER_STORAGE_BLOCK, "radius_ssbo");
			fluid_block_indexes.ssbo[fluid_block_indexes.VISCOSITY] = glGetProgramResourceIndex(m_shader.getProgId(), GL_SHADER_STORAGE_BLOCK, "viscosity_ssbo");
			fluid_block_indexes.ssbo[fluid_block_indexes.MASS] = glGetProgramResourceIndex(m_shader.getProgId(), GL_SHADER_STORAGE_BLOCK, "mass_ssbo");

		}

		void update(SPHFluid fluid) {
			glUseProgram(m_shader.getProgId());
			//data
			glShaderStorageBlockBinding(m_shader.getProgId(), fluid_block_indexes.ssbo[fluid_block_indexes.POSITIONS], 0);
			glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, fluid.ssbo[fluid.POSITIONS]);

			glShaderStorageBlockBinding(m_shader.getProgId(), fluid_block_indexes.ssbo[fluid_block_indexes.VELOCITY], 1);
			glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, fluid.ssbo[fluid.VELOCITY]);

			glShaderStorageBlockBinding(m_shader.getProgId(), fluid_block_indexes.ssbo[fluid_block_indexes.ACCELERATION], 2);
			glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, fluid.ssbo[fluid.ACCELERATION]);

			glShaderStorageBlockBinding(m_shader.getProgId(), fluid_block_indexes.ssbo[fluid_block_indexes.FORCE], 3);
			glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, fluid.ssbo[fluid.FORCE]);

			glShaderStorageBlockBinding(m_shader.getProgId(), fluid_block_indexes.ssbo[fluid_block_indexes.RADIUS], 4);
			glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, fluid.ssbo[fluid.RADIUS]);

			glShaderStorageBlockBinding(m_shader.getProgId(), fluid_block_indexes.ssbo[fluid_block_indexes.VISCOSITY], 5);
			glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, fluid.ssbo[fluid.VISCOSITY]);

			glShaderStorageBlockBinding(m_shader.getProgId(), fluid_block_indexes.ssbo[fluid_block_indexes.MASS], 6);
			glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, fluid.ssbo[fluid.MASS]);

			m_shader.dispatch(8,8,1);
		}
	};
}