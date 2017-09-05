#version 430


layout(location = 3) uniform float time;

// Per-vertex attributes
layout(location = 0) in vec4 pos; // World-space position
layout(location = 1) in vec4 normal; // World-space normal

uniform mat4 mat_projView;
out vec3 fragPos;
out vec3 fragNormal;


void main(void) {
    time;
    fragNormal;
	gl_PointSize = 30.5;
    gl_Position = mat_projView * pos;
}