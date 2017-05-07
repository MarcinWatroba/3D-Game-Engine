#include <Engine\Component\Transform_Instanced.h>
#include <Engine\Creators\Shader.h>
#include <glad\glad.h>
#include <vector>

void Transform_Instanced::update()
{
	if (b_Update)
	{
		mat4_Model = glm::mat4();
		quat_Orientation = glm::normalize(quat_Orientation);
		mat4_Model = glm::translate(mat4_Model, v3_Position);
		mat4_Model = glm::translate(mat4_Model, -v3_Origin);
		mat4_Model *= glm::mat4_cast(quat_Orientation);
		mat4_Model = glm::translate(mat4_Model, v3_Origin);
		mat4_Model = glm::scale(mat4_Model, v3_Scale);

		b_Update = false;
	}
}

void Transform_Instanced::update(glm::mat4 parent_Matrix_In)
{
	if (b_Update)
	{
		mat4_Model = parent_Matrix_In;
		quat_Orientation = glm::normalize(quat_Orientation);
		mat4_Model = glm::translate(mat4_Model, v3_Position);
		mat4_Model = glm::translate(mat4_Model, -v3_Origin);
		mat4_Model *= glm::mat4_cast(quat_Orientation);
		mat4_Model = glm::translate(mat4_Model, v3_Origin);
		mat4_Model = glm::scale(mat4_Model, v3_Scale);

		b_Update = false;
	}
}

Transform_Instanced::Transform_Instanced(const Transform_Instanced & p_NewComp_In)
{
	v3_Position = p_NewComp_In.v3_Position;
	v3_Scale = p_NewComp_In.v3_Scale;
	quat_Orientation = p_NewComp_In.quat_Orientation;
	v3_Origin = p_NewComp_In.v3_Origin;
}

glm::mat4 Transform_Instanced::get_ModelMatrix()
{
	return mat4_Model;
}

void Transform_Instanced::update_Shader(Shader* p_Shader_In)
{
	//Uniform locations
	int modelLoc = glGetUniformLocation(p_Shader_In->get_Program(), "model");
	//Pass them to shaders
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(mat4_Model));
}

void Transform_Instanced::set_Position(glm::vec3 v3_Position_In)
{
	b_Update = true;
	v3_Position = v3_Position_In;
}

void Transform_Instanced::set_Origin(glm::vec3 v3_Origin_In)
{
	b_Update = true;
	v3_Origin = v3_Origin_In;
}

glm::vec3 Transform_Instanced::get_Position()
{
	return v3_Position;
}

void Transform_Instanced::set_Scale(glm::vec3 v3_Scale_In)
{
	b_Update = true;
	v3_Scale = v3_Scale_In;
}

glm::vec3& Transform_Instanced::get_Scale()
{
	return v3_Scale;
}

void Transform_Instanced::set_Rotation(glm::quat quat_Rot_In)
{
	b_Update = true;
	quat_Orientation = quat_Rot_In * quat_Orientation;

}

void Transform_Instanced::update_Rotation(glm::quat quat_Rot_In)
{
	b_Update = true;
	quat_Orientation = glm::slerp(quat_Orientation, quat_Rot_In, 0.5f);
}

glm::quat Transform_Instanced::get_Rotation()
{
	return quat_Orientation;
}

glm::vec3 Transform_Instanced::get_Origin()
{
	return v3_Origin;
}

void Transform_Instanced::set_Rotation(float f_Angle_In, glm::vec3 v3_RotAxis_In)
{
	b_Update = true;
	glm::quat quat_Temp = glm::angleAxis(glm::radians(f_Angle_In), v3_RotAxis_In);
	quat_Orientation = quat_Temp * quat_Orientation;
}

std::string Transform_Instanced::get_Type()
{
	return "Transform_Instanced";
}