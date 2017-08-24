#pragma once

#include "integrable.h"

namespace physics_engine
{
	class Particle : public Integrable
	{
		GLuint m_radius;
	public:

		void setRadius(GLuint radius)
		{
			m_radius = radius;
		}


		GLuint getRadius()
		{
			return m_radius;
		}
	};
}