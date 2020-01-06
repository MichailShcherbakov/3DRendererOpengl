#version 450

in vec3 Position;
in vec3 Normal;

uniform samplerCube skybox;
uniform vec3 viewPos;

void main()
{
	/* Reflect */
	/*
	vec3 I = normalize(Position - viewPos);
	vec3 R = reflect(I, normalize(Normal));
	gl_FragColor = vec4(texture(skybox, R).rgb, 1.0f);
	*/

	/* Refract */
	float k = 1.52; // glass
	float ratio = 1.0f / k;
	vec3 I = normalize(Position - viewPos);
	vec3 R = refract(I, normalize(Normal), ratio);
	gl_FragColor = vec4(texture(skybox, R).rgb, 1.0f);
}