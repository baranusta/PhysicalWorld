#version 430 core

layout (local_size_x = 8, local_size_y = 1) in;

layout(std430, binding = 0) buffer position_ssbo{ vec4 position[]; };

layout(std430, binding = 1) buffer velocity_ssbo{ vec4 velocity[]; };

layout(std430, binding = 2) buffer acceleration_ssbo{ vec4 acceleration[]; };

layout(std430, binding = 3) buffer force_ssbo{ vec4 force[]; };

layout(std430, binding = 4) buffer radius_ssbo{ float radius[];};

layout(std430, binding = 5) buffer viscosity_ssbo{ float viscosity[]; };

layout(std430, binding = 6) buffer mass_ssbo{ float mass[]; };

uniform uint size;

void main(void)
{
	uint id = gl_WorkGroupID.x * gl_WorkGroupSize.x + gl_LocalInvocationID.x;
	if(id < size)
	{
		force[id] = position[id]; 
	}
}