#version 450

in vec2 TexCoord;
in vec3 FragPos;
in vec3 Normal;
in mat3 TBN;

uniform sampler2D diffuseMap;
uniform sampler2D normalMap;

uniform vec3 viewPos;
uniform vec3 lightPos;

uniform struct Material
{
	vec3 ambientColor;
	vec3 diffuseColor;
	vec3 specularColor;
	float shininess;
} material;

void main()
{
	/*vec3 normal = texture(normalMap, TexCoord).rgb;
	normal = normalize(normal * 2.0f - 1.0f);
	normal = normalize(TBN * normal);*/
	vec3 normal = normalize(Normal);

	vec3 lightDir = normalize(lightPos - FragPos);
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 halfwayDir = normalize(lightDir + viewDir); 

	/* MAIN COLOR */
	vec3 color = vec3(texture(diffuseMap, TexCoord));

	/* LIGHT COLOR */
	vec3 lightColor = vec3(0.5f);

	/* AMBIENT */
	vec3 ambient = lightColor * material.ambientColor;

	/* DIFFUSE */
	float diff = max(dot(lightDir, normal), 0.0f);
	vec3 diffuse = lightColor * diff * material.diffuseColor;

	/* SPECULAR */
	float spec = pow(max(dot(viewDir, halfwayDir), 0.0f), material.shininess);
	vec3 specular = lightColor * spec * material.specularColor;

	gl_FragColor = vec4((ambient + diffuse + specular) * color, 1.0f);
}