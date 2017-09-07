#pragma once

#include "..\..\..\..\Models\sph_fluid.h"

#include "..\..\..\..\..\ShaderController\compute_shader_controller.h"

namespace physics_engine
{

	class ST_Morris_2000
	{
	private:
		ComputeShaderController m_shader;
		GLuint m_index_type;
		GLuint m_index_size;
		GLuint m_index_tension_coef;
	public:
		ST_Morris_2000();
		void computeSurfaceTensionForce(const SPHFluid & fluid);
	};
}