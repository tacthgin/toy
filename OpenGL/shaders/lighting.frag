#version 330 core
out vec4 color;

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoords;

struct Material
{
	sampler2D diffuse;
	sampler2D specular;
	float shininess;
};
uniform Material material;

struct DirectionLight
{
	vec3 direction;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};
uniform DirectionLight directionLight;

struct SpotLight
{
	vec3 position;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float constant;
	float linear;
	float quaderatic;
};
uniform SpotLight spotLight;

uniform vec3 viewPos;

void main()
{
	vec3 ambient = spotLight.ambient * vec3(texture(material.diffuse, TexCoords));
	
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(spotLight.position - FragPos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = spotLight.diffuse * (diff * vec3(texture(material.diffuse, TexCoords)));
	
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	vec3 specular = spotLight.specular * (spec * vec3(texture(material.specular, TexCoords)));

	float distance = length(spotLight.position - FragPos);
	float attenuation = 1.0f / (spotLight.constant + spotLight.linear * distance + spotLight.quaderatic * (distance * distance));

	vec3 result = specular + ambient + diffuse;
	result *= attenuation;
	color = vec4(result, 1.0f);
};