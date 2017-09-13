#pragma once
#include "..\..\particle_system.h"
#include "..\..\..\..\Models\sph_fluid.h"

#include "..\..\..\..\..\ShaderController\compute_shader_controller.h"
#include "..\..\SurfaceTension\Morris_2000\st_morris_2000.h"

#define PBF2003_DIR "Physics\\PhysicsManagers\\Particles\\SPHSolvers\\"
#define K_GAS_FACTOR 0.5f

namespace physics_engine
{
	class PBF2003: public ParticleSystem
	{
	private:
		ComputeShaderController m_shader_density;
		ComputeShaderController m_shader_pressure;
		ComputeShaderController m_shader_force;

		std::shared_ptr<SPHFluid> m_fluid;

		GLuint index_size_density;
		
		GLuint index_size_pressure;
		GLuint index_k_gas_factor;

		GLuint index_size_f;
		GLuint index_type_f;

		unsigned int addedSystemCount;

		void computeDensity();
		void computePressure();
		void computeForcePressure_Viscosity();
		void computeSurfaceTensionForce();

		ST_Morris_2000 m_f_tension_solver;
	public:
		PBF2003()
			: m_shader_density(PBF2003_DIR "mass_density.comp"),
			m_shader_pressure(PBF2003_DIR "desbrun_pressure.comp"),
			m_shader_force(PBF2003_DIR "ParticleBasedFluid_Muller_2003\\force_pressure_viscosity.comp")
		{
			addedSystemCount = 0;

			glUseProgram(m_shader_density.getProgId());
			index_size_density = glGetUniformLocation(m_shader_density.getProgId(), "size");

			glUseProgram(m_shader_pressure.getProgId());
			index_size_pressure = glGetUniformLocation(m_shader_pressure.getProgId(), "size");
			index_k_gas_factor = glGetUniformLocation(m_shader_pressure.getProgId(), "k_gas_const");

			glUseProgram(m_shader_force.getProgId());
			index_size_f = glGetUniformLocation(m_shader_force.getProgId(), "size");
			index_type_f = glGetUniformLocation(m_shader_force.getProgId(), "type");

		}

		void setParticles(std::shared_ptr<Particle> particles);

		void computeInternalForces();
	};
}