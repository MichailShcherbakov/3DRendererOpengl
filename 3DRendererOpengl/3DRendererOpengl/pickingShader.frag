#version 450

#extension GL_EXT_gpu_shader4 : enable

out uvec3 FragColor;

uniform uint objectIndex;
uniform uint drawIndex;

void main()
{
	FragColor = uvec3(objectIndex, drawIndex, gl_PrimitiveID + 1);
}