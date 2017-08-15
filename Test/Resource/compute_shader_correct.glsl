#version 430 core

layout (local_size_x = 8, local_size_y = 8) in;

layout(std430, binding = 0) buffer pos
{ 
	vec4 position[]; 
};

void main(void)
{

}