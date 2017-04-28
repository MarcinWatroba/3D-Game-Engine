#version 330

in vec2 TexCoord;
in vec3 Normal;
in vec3 VertPos;

out vec4 colour;
uniform vec2 tiling;

struct Material
{
	sampler2D diffuse;
	sampler2D specular;
	float shininess;
};

struct Directional_Light
{
	vec3 direction;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

struct Point_Light
{
	vec3 position;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	float constant;
	float linear;
	float quadratic;
};


uniform Directional_Light directional_Light;
uniform Point_Light point_Light[20];
uniform vec3 viewPos;
uniform Material material;
uniform int numOfLights;

vec3 point_Lights[20];

vec3 create_DirectionalLight(Directional_Light light, vec3 normal, vec3 viewDir);
vec3 create_PointLight(Point_Light light, vec3 normal, vec3 VertPos, vec3 viewDir);

void main()
{
	vec3 norm = normalize(Normal);
	vec3 viewDir = normalize(viewPos - VertPos);

	vec3 result;
	for (int i = 0; i < numOfLights; i++) point_Lights[i] = create_PointLight(point_Light[i], norm, VertPos, viewDir);
	result = point_Lights[0] + point_Lights[1];
	colour = vec4(result, 1.f);
}

vec3 create_DirectionalLight(Directional_Light light, vec3 normal, vec3 viewDir)
{
	vec3 lightDir = normalize(-light.direction);
	float diff = max(dot(normal, lightDir), 0);
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0), material.shininess);

	vec3 ambient = light.ambient * vec3(texture(material.diffuse, vec2(TexCoord.x * tiling.x, (1 - TexCoord.y) * tiling.y)));
	vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, vec2(TexCoord.x * tiling.x, (1 - TexCoord.y) * tiling.y)));
	vec3 specular = light.specular * spec * vec3(texture(material.specular, vec2(TexCoord.x * tiling.x, (1 - TexCoord.y) * tiling.y)));
	return (ambient + diffuse + specular);
}

vec3 create_PointLight(Point_Light light, vec3 normal, vec3 vertPos, vec3 viewDir)
{
	vec3 lightDir = normalize(light.position - vertPos);
	float diff = max(dot(normal, lightDir), 0.f);

	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.f), material.shininess);

	float distance = length(light.position - vertPos);
	float attenuation = 1.f / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

	vec3 ambient = light.ambient * vec3(texture(material.diffuse, vec2(TexCoord.x * tiling.x, (1 - TexCoord.y) * tiling.y)));
	vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, vec2(TexCoord.x * tiling.x, (1 - TexCoord.y) * tiling.y)));
	vec3 specular = light.specular * spec * vec3(texture(material.specular, vec2(TexCoord.x * tiling.x, (1 - TexCoord.y) * tiling.y)));

	ambient *= attenuation;
	diffuse *= attenuation;
	specular *= attenuation;

	return (ambient + diffuse + specular);
}