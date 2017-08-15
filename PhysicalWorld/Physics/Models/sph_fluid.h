#pragma once

namespace physics_engine
{
	class SPHFluid
	{
	public:
		int positions;
		int velocity;
		int acceleration;
		int force;

		int color_diffuse;
		int ambient_diffuse;
		int specular_diffuse;

		int mass;
		int radius;
		int viscosity;
	};
}