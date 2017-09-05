#pragma once

#include "..\..\stdafx.h"
#include "particle.h"

namespace physics_engine
{
	class SPHFluid : public Particle
	{
	private:
		GLuint m_viscosity;
		GLuint m_density;
		GLuint m_rest_density;
		GLuint m_pressure;
	public:
		SPHFluid()
		{
			glGenBuffers(1, &m_density);
			glGenBuffers(1, &m_pressure);
		}

		~SPHFluid()
		{
			glDeleteBuffers(1, &m_density);
			glDeleteBuffers(1, &m_pressure);
		}

		void setViscosities(GLuint viscosity)
		{
			m_viscosity = viscosity;
		}

		GLuint getViscosities()
		{
			return m_viscosity;
		}

		void setRestDensities(GLuint restDensity)
		{
			m_rest_density = restDensity;
		}

		GLuint getRestDensities()
		{
			return m_rest_density;
		}

		GLuint getDensities()
		{
			return m_density;
		}

		GLuint getPressures()
		{
			return m_pressure;
		}

		void setSize(unsigned int size)
		{
			Object::setSize(size);

			glBindBuffer(GL_SHADER_STORAGE_BUFFER, m_pressure);
			glBufferData(GL_SHADER_STORAGE_BUFFER, size *
				sizeof(float), NULL, GL_STATIC_DRAW);

			glBindBuffer(GL_SHADER_STORAGE_BUFFER, m_density);
			glBufferData(GL_SHADER_STORAGE_BUFFER, size *
				sizeof(float), NULL, GL_STATIC_DRAW);
			
			glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
		}
	};
}