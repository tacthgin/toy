#version 330 core

struct Material
{
	sampler2D diffuse;
	sampler2D specular;
	float shininess;
};

struct DirectionLight
{
	vec3 direction;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
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

struct SpotLight
{
	vec3 position;
	vec3 direction;
	float cutOff;
	float outerCutOff;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float constant;
	float linear;
	float quaderatic;
};

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoords;

out vec4 color;

uniform vec3 viewPos;
uniform Material material;
uniform DirectionLight directionLight;
uniform PointLight pointLight;
uniform SpotLight spotLight;

void main()
{
	vec3 lightDir = normalize(spotLight.position - FragPos);

	float theta = dot(lightDir, normalize(-spotLight.direction));
	float epsilon = spotLight.cutOff - spotLight.outerCutOff;
	float intensity = clamp((theta - spotLight.outerCutOff) / epsilon, 0.0, 1.0);

	vec3 ambient = spotLight.ambient * vec3(texture(material.diffuse, TexCoords));
	
	vec3 norm = normalize(Normal);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = spotLight.diffuse * diff * vec3(texture(material.diffuse, TexCoords));
	diffuse *= intensity;

	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	vec3 specular = spotLight.specular * spec * vec3(texture(material.specular, TexCoords));
	specular *= intensity;

	float distance = length(spotLight.position - FragPos);
	float attenuation = 1.0f / (spotLight.constant + pointLight.linear * distance + pointLight.quaderatic * (distance * distance));

	//ambient *= attenuation;
	diffuse *= attenuation;
	specular *= attenuation;

	color = vec4(specular + ambient + diffuse, 1.0f);
};