#version 450

layout (location = 0) in vec3 position;

out vec3 TexCoord;

uniform mat4 projection;
uniform mat4 view;

void main()
{
	TexCoord = position;
	vec4 Position = projection * view  * vec4(position, 1.0f);
	gl_Position = Position.xyww;
}