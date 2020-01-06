#version 450

in vec2 TexCoord;

uniform sampler2D diffuseMap;

void main()
{
	vec4 color = texture(diffuseMap, TexCoord);

	if (color.a < 0.5f)
	{
		discard;
	}

	gl_FragColor = color;

	/*if (gl_FragColor.r == 0 && 
		gl_FragColor.g == 0 && 
		gl_FragColor.b == 0) 
	{
        discard;
    }*/
}