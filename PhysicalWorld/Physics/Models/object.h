#pragma once
#include "..\..\stdafx.h"

namespace physics_engine
{
	class Object
	{
	private:
		unsigned int m_size;
		GLuint m_Positions;
		GLuint m_Rotations;
		GLuint m_mass;

	public:
		virtual ~Object() = 0;

		virtual void setSize(unsigned int size)
		{
			m_size = size;
		}

		void setMass(GLuint mass)
		{
			m_mass = mass;
		}
		
		void setPositions(GLuint positions)
		{
			m_Positions = positions;
		}
		
		void setRotations(GLuint rotations)
		{
			m_Rotations = rotations;
		}

		GLuint getPositions()const
		{
			return m_Positions;
		}

		GLuint getMass()const
		{
			return m_mass;
		}

		GLuint getRotations()const
		{
			return m_Rotations;
		}

		unsigned int getSize()const
		{
			return m_size;
		}

		bool operator<(const Object& rhs) const
		{
			return m_Positions < rhs.m_Positions;  
		}

	};
}