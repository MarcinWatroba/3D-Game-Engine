#include <Engine\Component\Transform_2D.h>
#include <Engine\Creators\Shader.h>
#include <glad\glad.h>

void Transform_2D::update()
{
	if (b_Update)
	{
		mat4_Model = glm::mat4();
		mat4_Model = glm::translate(mat4_Model, glm::vec3(v3_Position.x + (v3_Scale.x / 2.f), v3_Position.y + (v3_Scale.y / 2.f), v3_Position.z));
		mat4_Model = glm::scale(mat4_Model, glm::vec3(v3_Scale.x / 2.f, v3_Scale.y / 2.f, 1.f));
		b_Update = false;
	}
}

void Transform_2D::update(glm::mat4 mat4_ParentMatrix_In)
{
	if (b_Update)
	{
		mat4_Model = mat4_ParentMatrix_In;
		mat4_Model = glm::translate(mat4_Model, glm::vec3(v3_Position.x + (v3_Scale.x / 2.f), v3_Position.y + (v3_Scale.y / 2.f), v3_Position.z));
		mat4_Model = glm::scale(mat4_Model, glm::vec3(v3_Scale.x / 2.f, v3_Scale.y / 2.f, 1.f));
		b_Update = false;
	}
}

void Transform_2D::update_Shader(Shader* p_Shader_In)
{
	//Uniform locations
	int modelLoc = glGetUniformLocation(p_Shader_In->get_Program(), "model");
	//Pass them to shaders
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(mat4_Model));
}

void Transform_2D::set_Position(glm::vec2 v2_Position_In)
{
	b_Update = true;
	v3_Position = glm::vec3(v2_Position_In.x, v2_Position_In.y, 0.f);
}

void Transform_2D::set_Origin(glm::vec2 v2_Origin_In)
{
	b_Update = true;
	v3_Origin = glm::vec3(v2_Origin_In.x, v2_Origin_In.y, 0.f);
}

void Transform_2D::set_Size(glm::vec2 v2_Size_In)
{
	b_Update = true;
	v3_Scale = glm::vec3(v2_Size_In.x, v2_Size_In.y, 0.f);
}

glm::vec2 Transform_2D::get_Size()
{
	return glm::vec2(v3_Scale.x, v3_Scale.y);
}

