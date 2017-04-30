#include <Engine\Lighting\Light.h>

Light::Light(glm::vec3 v3_Ambient_In, glm::vec3 v3_Diffuse_In, glm::vec3 v3_Specular_In)
{
	v3_Ambient = v3_Ambient_In;
	v3_Diffuse = v3_Diffuse_In;
	v3_Specular = v3_Specular_In;
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

void Light::set_Depth_Texture(glm::uvec2 ui_Depth_In)
{
	ui_Depth_Texture = ui_Depth_In;
}

glm::uvec2 Light::get_Depth_Texture()
{
	return ui_Depth_Texture;
}
