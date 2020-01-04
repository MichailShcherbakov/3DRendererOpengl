#version 450

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texCoord;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

smooth out vec2 TexCoord;

void main()
{
    gl_Position = projection * view * model * vec4(position, 1.0f);

    TexCoord = texCoord;
}