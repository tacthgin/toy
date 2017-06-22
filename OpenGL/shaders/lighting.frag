#version 330 core

in vec3 Normal;
in vec3 FragPos;

out vec4 color;

uniform vec3 lightPos;

uniform vec3 objectColor;
uniform vec3 lightColor;

void main()
{
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(lightPos - FragPos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * lightColor;
	float ambientStrength = 0.1f;
	vec3 ambient = ambientStrength * lightColor;
	color = vec4((ambient + diff) * objectColor, 1.0f);
};