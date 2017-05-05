#pragma once
#include <Engine\Component\Transform.h>


class Transform_2D : public Transform
{
public:
	//Update
	void update();
	void update(glm::mat4 mat4_ParentMatrix_In);
	void update_Shader(Shader* p_Shader_In);
	void set_Position(glm::vec2 v2_Position_In);
	void set_Origin(glm::vec2 v2_Origin_In);
	void set_Size(glm::vec2 v2_Size_In);

	glm::vec2 get_Size();
};