#pragma once
#include "..\..\stdafx.h"
#include "object.h"

namespace physics_engine
{
	class IntegrableRotating: public Object
	{
	private:
		GLuint m_angularVelocities;
		GLuint m_angularAccelerations;
		GLuint m_torques;

	public:

		virtual ~IntegrableRotating()
		{
		}

		void setAngularVelocities(GLuint angularVelocities)
		{
			m_angularVelocities = angularVelocities;
		}

		void setAngularAccelerations(GLuint angularAccelerations)
		{
			m_angularAccelerations = angularAccelerations;
		}

		void setTorques(GLuint torques)
		{
			m_torques = torques;
		}

		GLuint getAngularVelocities()
		{
			return m_angularVelocities;
		}

		GLuint getAngularAccelerations()
		{
			return m_angularAccelerations;
		}

		GLuint getTorques()
		{
			return m_torques;
		}
	};
}