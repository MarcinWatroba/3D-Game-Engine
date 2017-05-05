#include <Engine\Lighting\Light.h>

Light::Light(glm::vec3 v3_Ambient_In, glm::vec3 v3_Diffuse_In, glm::vec3 v3_Specular_In)
{
	v3_Ambient = v3_Ambient_In;
	v3_Diffuse = v3_Diffuse_In;
	v3_Specular = v3_Specular_In;
}

Light::Light(const Light & light) : GameObject_3D(light)
{
	v3_Ambient = light.v3_Ambient;
	v3_Diffuse = light.v3_Diffuse;
	v3_Specular = light.v3_Specular;
}

void Light::set_Ambient(glm::vec3 v3_Ambient_In)
{
	v3_Ambient = v3_Ambient_In;
}

void Light::set_Diffuse(glm::vec3 v3_Diffuse_In)
{
	v3_Diffuse = v3_Diffuse_In;
}

void Light::set_Specular(glm::vec3 v3_Specular_In)
{
	v3_Specular = v3_Specular_In;
}

glm::vec3 Light::get_Ambient()
{
	return v3_Ambient;
}

glm::vec3 Light::get_Diffuse()
{
	return v3_Diffuse;
}

glm::vec3 Light::get_Specular()
{
	return v3_Specular;
}
