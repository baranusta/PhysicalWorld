#version 430

layout(location = 0) out vec4 outColor;

in vec4 fragPos;
in vec3 ws_position;
in float ws_radius;

uniform vec2 screenSize;
uniform vec2 camNearFar;
uniform mat4 mat_projView;
uniform mat4 mat_inv_projView;


vec4 diffuseColor(vec3 light, vec3 pos, vec3 normal)
{
	
	vec3 toLight = light - pos;
	if(dot(toLight,normal) > 0)
	{
		float t = dot(normalize(toLight),normalize(normal));
		return vec4(1,1,1,1) * t;
	}
	else
		return vec4(0,0,0,1);
}

float linearDepthValue(float nonLinearDepth)
{
    float z_n = 2.0 * nonLinearDepth - 1.0;
    return 2.0 * camNearFar.x * camNearFar.y / (camNearFar.y + camNearFar.x - z_n * (camNearFar.y - camNearFar.x));
}

float nonLinearDepthValue(float linearDepth)
{
    float A = mat_projView[2].z;
    float B = mat_projView[3].z;
    return 0.5*(-A*linearDepth + B) / linearDepth + 0.5;
}

void main()
{
	vec3 center = fragPos.xyz;
	vec2 a = 2.0 * (gl_FragCoord.xy/screenSize) - 1;
	vec2 dif = a - center.xy;
	dif.x *= screenSize.x / screenSize.y;
	float radius2 =  ws_radius * ws_radius;
	float dif2 = dot(dif,dif);
	if(dif2 < radius2)
	{	
		float depthDif = sqrt(radius2 - dif2);
		vec3 normal = normalize(vec3(dif.xy, depthDif));
		vec3 lightDir = vec3(1,1,0);
        float intensity = max(dot(normalize(lightDir),normal), 0.0);
        outColor = vec4(1)*intensity;
		
		//gl_FragDepth = 0.0; set correctly.
	}
	else
		discard;
}