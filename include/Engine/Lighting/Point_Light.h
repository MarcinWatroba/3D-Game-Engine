#pragma once

#include <Engine\Lighting\Light.h>

class Point_Light : public Light
{
private:

	float f_radius;
	//Attenutation constant


	int i_ID; // ID of the point light

public:
	//Constructor
	Point_Light() {};

	//Main constructor
	Point_Light(glm::vec3 v3_Ambient_In, glm::vec3 v3_Diffuse_In, glm::vec3 v3_Specular_In, float f_Radius_In, unsigned int i_ID_In);

	void set_Radius(float f_Radius_In);
	float get_Radius();
	Point_Light(const Point_Light &point_Light);

	//Set attenutation constant
	void set_Constant(float f_Constant_In);

	//Set attenutation constant

	void set_ID(int i_ID_In);

	//Update light
	void update_Shader(Shader* p_Shader_In);

	std::string get_Type();

	int get_ID();

	float get_Constant();
	float get_Linear();
	float get_Quadratic();
};