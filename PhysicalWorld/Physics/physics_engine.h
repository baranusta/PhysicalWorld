#pragma once

#include "..\Models\Particle\particle.h"

namespace physics_engine
{
	class PhysicsEngine
	{
	private:

		struct solid_objects {
			int vertices;
			//object to vertices. similar to Compressed Row Structure
			int mapping;

			int mobility;
			int positions;
			int velocity;
			int acceleration;
			int force;

			int rotations;
			int angular_velocity;
			int angular_acceleration;
			int torque;
		};

		struct SPHParticles {
		};


		PhysicsEngine() = default;

	public:
		PhysicsEngine(PhysicsEngine&) = delete;
		void operator=(PhysicsEngine&) = delete;

		static PhysicsEngine& getInstance()
		{
			static PhysicsEngine engine;

			return engine;
		}

		void update();
		unsigned int addFluid(std::vector<Particle> particles);
		unsigned int addFluid(std::vector<Particle> particles, unsigned int index);
	};
}