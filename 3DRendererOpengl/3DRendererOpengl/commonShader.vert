#version 450

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoord;
layout (location = 3) in vec3 tangent;
layout (location = 4) in vec3 bitangent; 

out vec2 TexCoord;
out vec3 FragPos;
out vec3 Normal;
out mat3 TBN;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

void main()
{
	gl_Position = projection * view * model * vec4(position, 1.0f);
	TexCoord = texCoord;
	Normal = mat3(transpose(inverse(model))) * normal;
	FragPos = vec3(model * vec4(position, 1.0f));

	vec3 T = normalize(vec3(model * vec4(tangent,   0.0f)));
	vec3 B = normalize(vec3(model * vec4(bitangent, 0.0f)));
	vec3 N = normalize(vec3(model * vec4(normal,    0.0f)));
	TBN = mat3(T, B, N);
}