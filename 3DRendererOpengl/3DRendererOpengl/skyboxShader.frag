#version 450

in vec3 TexCoord;

uniform samplerCube diffuseMap;

void main()
{
	gl_FragColor = texture(diffuseMap, TexCoord);
}