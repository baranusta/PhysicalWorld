#version 430


// Per-vertex attributes
layout(location = 0) in vec4 pos; // World-space position
layout(location = 3) in float radius; // World-space radius

uniform mat4 mat_projView;
uniform mat4 mat_inv_projView;
uniform vec2 camNearFar;
uniform vec2 screenSize;
out vec4 fragPos;

out vec3 ws_position;
out float ws_radius;


float linearDepthValue(float nonLinearDepth)
{
    float z_n = 2.0 * nonLinearDepth - 1.0;
    return 2.0 * camNearFar.x * camNearFar.y / (camNearFar.y + camNearFar.x - z_n * (camNearFar.y - camNearFar.x));
}

float t(float nonLinearDepth)
{
	return 1 - (linearDepthValue(nonLinearDepth) - camNearFar.x) / (camNearFar.y - camNearFar.x);
}

void main(void) {
	mat_inv_projView;
	ws_position = pos.xyz;
    gl_Position = mat_projView * pos;
	ws_radius = radius * camNearFar.x / linearDepthValue(gl_Position.z/gl_Position.w);
	gl_PointSize = ws_radius * max(screenSize.x,screenSize.y);
	fragPos = gl_Position / gl_Position.w;
}