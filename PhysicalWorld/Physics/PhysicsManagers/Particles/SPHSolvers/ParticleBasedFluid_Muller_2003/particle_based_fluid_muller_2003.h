#pragma once
#include "..\..\particle_system.h"
#include "..\..\..\..\Models\sph_fluid.h"

#include "..\..\..\..\..\ShaderController\compute_shader_controller.h"
#include "..\..\..\..\..\glm\glm.hpp"

#define PBF2003_DIR "Physics\\PhysicsManagers\\Particles\\SPHSolvers\\"
#define K_GAS_FACTOR 0.1f

namespace physics_engine
{
	class PBF2003: public ParticleSystem
	{
	private:
		ComputeShaderController m_shader_density;
		ComputeShaderController m_shader_pressure;
		ComputeShaderController m_shader_f_pressure;
		ComputeShaderController m_shader_f_viscosity;

		std::unordered_map<int, SPHFluid*> m_fluids;

		GLuint index_size_density;
		
		GLuint index_size_pressure;
		GLuint index_k_gas_factor;

		GLuint index_size_f_pressure;
		GLuint index_size_f_viscosity;

		unsigned int addedSystemCount;

		void computeDensity();
		void computePressure();
		void computePressureForce();
		void computeViscosityForce();
	public:
		PBF2003()
			: m_shader_density(PBF2003_DIR "mass_density.comp"),
			m_shader_pressure(PBF2003_DIR "desbrun_pressure.comp"),
			m_shader_f_pressure(PBF2003_DIR "ParticleBasedFluid_Muller_2003\\pressure.comp"),
			m_shader_f_viscosity(PBF2003_DIR "ParticleBasedFluid_Muller_2003\\viscosity.comp")
		{
			addedSystemCount = 0;

			glUseProgram(m_shader_density.getProgId());
			index_size_density = glGetUniformLocation(m_shader_density.getProgId(), "size");

			glUseProgram(m_shader_pressure.getProgId());
			index_size_pressure = glGetUniformLocation(m_shader_pressure.getProgId(), "size");
			index_k_gas_factor = glGetUniformLocation(m_shader_pressure.getProgId(), "k_gas_const");

			glUseProgram(m_shader_f_pressure.getProgId());
			index_size_f_pressure = glGetUniformLocation(m_shader_f_pressure.getProgId(), "size");
			
			glUseProgram(m_shader_f_viscosity.getProgId());
			index_size_f_viscosity = glGetUniformLocation(m_shader_f_viscosity.getProgId(), "size");
		}

		int addParticles(Particle* particles);

		int removeParticles(int id);

		void computeForces();
	};
}