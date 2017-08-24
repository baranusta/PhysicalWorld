#pragma once
#include "..\..\stdafx.h"
#include "object.h"

namespace physics_engine
{
	class Integrable: public Object
	{
	private:
		GLuint m_velocities;
		GLuint m_accelerations;
		GLuint m_forces;
	public:

		virtual ~Integrable()
		{
		}
		
		void setVelocities(GLuint velocities)
		{
			m_velocities = velocities;
		}
		
		void setAccelerations(GLuint accelerations)
		{
			m_accelerations = accelerations;
		}

		void setForces(GLuint forces)
		{
			m_forces = forces;
		}

		GLuint getVelocities()
		{
			return m_velocities;
		}

		GLuint getAccelerations()
		{
			return m_accelerations;
		}

		GLuint getForces()
		{
			return m_forces;
		}
	};
}