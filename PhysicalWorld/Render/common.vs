#version 430


// Per-vertex attributes
layout(location = 0) in vec4 pos; // World-space position
layout(location = 1) in vec4 normal; // World-space normal

layout(location = 3) in float radius; // World-space radius

uniform mat4 mat_projView;
out vec4 fragPos;
out vec3 fragNormal;
out float radi;

void main(void) {
    fragNormal;
	gl_PointSize = 30;
    gl_Position = mat_projView * pos;
	fragPos = gl_Position;
	radi = radius * 0.001 / fragPos.w;
}