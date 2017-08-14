#pragma once

namespace physics_engine
{
	class Fluid
	{
		private:
		struct gpu_fluid {

			int positions;
			int velocity;
			int acceleration;
			int force;
			
			int mass;
			int radius;
			int viscosity;
		};

	};
}