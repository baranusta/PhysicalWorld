#pragma once
#include "..\particle_system.h"
#include "..\..\..\Models\sph_fluid.h"

#include "..\..\..\..\ShaderController\compute_shader_controller.h"
#include "..\..\..\..\glm\glm.hpp"



namespace physics_engine
{
	class SPHDefault: public ParticleSystem
	{
	private:
		ComputeShaderController m_shader;
		std::unordered_map<int, SPHFluid*> m_fluids;

		GLuint size_index;
		unsigned int addedSystemCount;
	public:
		SPHDefault()
			: m_shader("Physics\\PhysicsManagers\\Particles\\SPHDefault\\sph_default.comp")
		{
			addedSystemCount = 0;

			glUseProgram(m_shader.getProgId());
			size_index = glGetUniformLocation(m_shader.getProgId(), "size");
		}

		int addParticles(Particle* particles);

		int removeParticles(int id);

		void computeForces();
	};
}