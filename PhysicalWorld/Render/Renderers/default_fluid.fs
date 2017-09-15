#version 430

layout(location = 0) out vec4 outColor;

in vec4 fragPos;
in float radi;
uniform vec2 screenSize;

void main()
{
	vec2 center = fragPos.xy / fragPos.w;
	vec2 a = 2.0 * (gl_FragCoord.xy/screenSize) - 1 ;
	vec2 dif = a - center;
	dif.x *= screenSize.x / screenSize.y;
	if(dot(dif,dif) < radi)
		outColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);
	else
		discard;
}