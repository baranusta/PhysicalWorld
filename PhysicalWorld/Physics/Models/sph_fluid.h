#pragma once

#include "..\..\stdafx.h"

namespace physics_engine
{
	class SPHFluid
	{
	public:

		enum SSBO_TYPES {
			POSITIONS,
			VELOCITY,
			ACCELERATION,
			FORCE,
			MASS,
			RADIUS,
			VISCOSITY,
			SSBO_TYPES_SIZE
		};

		GLuint ssbo[SSBO_TYPES_SIZE];
	};
}