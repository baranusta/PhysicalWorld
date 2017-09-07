#pragma once
#include "..\..\stdafx.h"
#include "object.h"

namespace physics_engine
{
	class Integrable: public Object
	{
	private:
		GLuint m_velocities;
		GLuint m_forces;
	public:

		virtual ~Integrable()
		{
		}
		
		void setVelocities(GLuint velocities)
		{
			m_velocities = velocities;
		}

		void setForces(GLuint forces)
		{
			m_forces = forces;
		}

		GLuint getVelocities()const
		{
			return m_velocities;
		}

		GLuint getForces()const
		{
			return m_forces;
		}
	};
}