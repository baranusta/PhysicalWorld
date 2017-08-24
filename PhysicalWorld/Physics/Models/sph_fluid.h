#pragma once

#include "..\..\stdafx.h"
#include "particle.h"

namespace physics_engine
{
	class SPHFluid : public Particle
	{
	private:
		GLuint m_viscosity;
	public:

		void setViscosities(GLuint viscosity)
		{
			m_viscosity = viscosity;
		}

		GLuint getViscosities()
		{
			return 0;
		}
	};
}