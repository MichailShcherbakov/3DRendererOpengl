#version 450

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;

out vec3 Position;
out vec3 Normal;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

void main()
{
	Position = vec3(model * vec4(position, 1.0f));
	Normal = mat3(transpose(inverse(model))) * (normal);
	gl_Position = projection * view  * vec4(position, 1.0f);
}