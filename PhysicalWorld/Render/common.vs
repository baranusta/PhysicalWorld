#version 430

// Model/view/projection matrix
layout(location = 0) uniform mat4 mvp;
layout(location = 3) uniform float time;

// Per-vertex attributes
layout(location = 0) in vec4 pos; // World-space position
layout(location = 1) in vec4 normal; // World-space normal


out vec3 fragPos;
out vec3 fragNormal;


void main(void) {
    time;
	mvp;
    fragPos = vec3(pos.x,pos.y + cos(time * 5.)/4.,pos.z);
    fragNormal;
	gl_PointSize = 30.5;
    gl_Position = pos;
}