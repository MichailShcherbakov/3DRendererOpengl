#version 450

smooth in vec2 TexCoord;

uniform vec4 lineColor;

void main()
{
	float thickness = 0.01f;
	float frequency = 0.01f;

	if(fract(TexCoord.x / thickness) < frequency || fract(TexCoord.y / thickness) < frequency)
        gl_FragColor =  vec4(1);
    else
        gl_FragColor = vec4(0);
}