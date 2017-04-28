#include <Engine\Component\Transform.h>

Transform::Transform()
{
	b_Update = false;
	v3_Position = glm::vec3(0.f, 0.f, 0.f);
	quat_Orientation = glm::quat(1.f, 0.f, 0.f, 0.f);
	v3_Origin = glm::vec3(0.f, 0.f, 0.f);
	v3_Scale = glm::vec3(1.f, 1.f, 1.f);
}

glm::mat4* Transform::get_ModelMatrix()
{
	return &mat4_Model;
}

void Transform::force_Update()
{
	b_Update = true;
}