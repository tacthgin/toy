#version 330 core

struct Material
{
	sampler2D texture_diffuse;
	sampler2D texture_specular;
	float shininess;
};

struct PointLight
{
	vec3 position;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float constant;
	float linear;
	float quaderatic;
};

in vec3 Normal;
in vec2 TexCoords;
in vec3 FragPos;

out vec4 color;

uniform Material material;
uniform PointLight light;
uniform vec3 viewPos;

vec3 calcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
	vec3 lightDir = normalize(light.position - fragPos);
	float diff = max(dot(normal, lightDir), 0.0);
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

	vec3 ambient = light.ambient * vec3(texture(material.texture_diffuse, TexCoords));
	vec3 diffuse = light.diffuse * diff * vec3(texture(material.texture_diffuse, TexCoords));
	vec3 specular = light.specular * spec * vec3(texture(material.texture_specular, TexCoords));

	float distance = length(light.position - fragPos);
	float attenuation = 1.0f / (light.constant + light.linear * distance + light.quaderatic * (distance * distance));

	ambient *= attenuation;
	diffuse *= attenuation;
	specular *= attenuation;

	return ambient + diffuse + specular;
}

void main()
{
	vec3 result = calcPointLight(light, normalize(Normal), FragPos, normalize(viewPos - FragPos));
	color = vec4(result, 1.0f);
};