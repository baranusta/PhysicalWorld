#pragma once

namespace physics_engine
{
	class SolidObject
	{
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
}