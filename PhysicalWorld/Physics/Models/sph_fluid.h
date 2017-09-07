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
		GLuint m_surface_normal;

		float m_tension_coef;
	public:
		SPHFluid()
		{
			glGenBuffers(1, &m_density);
			glGenBuffers(1, &m_pressure);
			glGenBuffers(1, &m_surface_normal);
		}

		~SPHFluid()
		{
			glDeleteBuffers(1, &m_density);
			glDeleteBuffers(1, &m_pressure);
			glDeleteBuffers(1, &m_surface_normal);
		}

		void setViscosities(GLuint viscosity)
		{
			m_viscosity = viscosity;
		}

		GLuint getViscosities() const
		{
			return m_viscosity;
		}

		void setRestDensities(GLuint restDensity)
		{
			m_rest_density = restDensity;
		}

		GLuint getRestDensities()const
		{
			return m_rest_density;
		}

		GLuint getDensities()const
		{
			return m_density;
		}

		GLuint getPressures()const
		{
			return m_pressure;
		}


		GLuint getSurfaceNormals()const
		{
			return m_surface_normal;
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

			glBindBuffer(GL_SHADER_STORAGE_BUFFER, m_surface_normal);
			glBufferData(GL_SHADER_STORAGE_BUFFER, size *
				sizeof(glm::vec4), NULL, GL_STATIC_DRAW);
			
			glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
		}

		void setTensionCoef(float tension_coef)
		{
			m_tension_coef = tension_coef;
		}

		float getTensionCoef()const
		{
			return m_tension_coef;
		}
	};
}