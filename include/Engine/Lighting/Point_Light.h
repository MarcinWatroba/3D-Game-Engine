#pragma once

#include <Engine\Lighting\Light.h>

class Point_Light : public Light
{
private:
	//Attenutation constant
	float f_Constant;

	//Attenuation linear
	float f_Linear;

	//Attenuation quadratic
	float f_Quadratic;

	unsigned int i_ID; // ID of the point light

public:
	//Constructor
	Point_Light() {};

	//Main constructor
	Point_Light(glm::vec3 v3_Ambient_In, glm::vec3 v3_Diffuse_In, glm::vec3 v3_Specular_In, float f_Constant_In, float f_Linear_In, float f_Quadratic_In, unsigned int i_ID_In);

	//Set attenutation constant
	void set_Constant(float f_Constant_In);

	//Set attenutation linear
	void set_Linear(float f_Linear_In);

	//Set attenuation quadratic
	void set_Quadratic(float f_Quadratic_In);

	//Update light
	void update_Shader(Shader* p_Shader_In);
};