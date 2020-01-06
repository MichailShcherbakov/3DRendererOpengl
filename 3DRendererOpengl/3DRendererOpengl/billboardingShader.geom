#version 450

layout (points) in;
layout (triangle_strip, max_vertices = 4) out;

uniform mat4 view;
uniform mat4 projection;
uniform vec3 viewPos;
uniform vec2 size;

out vec2 TexCoord;

void main()
{
	vec3 position = gl_in[0].gl_Position.xyz;

	vec3 up = vec3(view[0][1], view[1][1], view[2][1]);
	vec3 right = vec3(view[0][0], view[1][0], view[2][0]);

	position -= (right * 0.5f * size.x);
	position.y -= size.y * 0.5f;
    gl_Position = projection * view * vec4(position, 1.0f);
    TexCoord = vec2(0.0f, 0.0f);
    EmitVertex();
 
    position.y += size.y * 1.0f;
    gl_Position = projection * view * vec4(position, 1.0f);
    TexCoord = vec2(0.0f, 1.0f);
    EmitVertex();
 
    position.y -= size.y * 1.0f;
    position += right * size.x;
    gl_Position = projection * view * vec4(position, 1.0f);
    TexCoord = vec2(1.0f, 0.0f);
    EmitVertex();
 
    position.y += size.y * 1.0f;
    gl_Position = projection * view * vec4(position, 1.0f);
    TexCoord = vec2(1.0f, 1.0f);
    EmitVertex();
 
    EndPrimitive();
}