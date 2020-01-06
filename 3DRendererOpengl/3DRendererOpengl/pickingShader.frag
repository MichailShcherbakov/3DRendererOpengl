#version 450

#extension GL_EXT_gpu_shader4 : enable

out uvec3 FragColor;

uniform uint objectID;
uniform uint drawID;

void main()
{
	FragColor = uvec3(objectID, drawID, gl_PrimitiveID + 1);
}