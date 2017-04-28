#pragma once

#include <Engine/Game_Objects/GameObject_3D.h>

class Light : public GameObject_3D
{
protected:
	//Ambient intensity
	glm::vec3 v3_Ambient;

	//Diffuse intensity
	glm::vec3 v3_Diffuse;

	//Speculat intensity
	glm::vec3 v3_Specular;
public:
	Light() {};

	//Main constructor
	Light(glm::vec3 v3_Ambient_In, glm::vec3 v3_Diffuse_In, glm::vec3 v3_Specular_In);

	//Set ambient intensity
	virtual void set_Ambient(glm::vec3 v3_Ambient_In);

	//Set diffuse intensity
	virtual void set_Diffuse(glm::vec3 v3_Diffuse_In);

	//Set specular intensity
	virtual void set_Specular(glm::vec3 v3_Specular_In);

	//Update light
	virtual void update_Shader(Shader* p_Shader_In) = 0;
};