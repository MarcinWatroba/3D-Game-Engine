#include <Engine\Component\Respond_Movement.h>
#include <Engine\Game_Objects\GameObject_3D.h>

void Respond_Movement::move(GameObject_3D* po_GameObject_In, glm::vec3 v3_Direction_In, float f_Speed_In)
{
	//Create a rotation point
	glm::quat quat_RotationPoint = glm::quat(0, v3_Direction_In) * f_Speed_In;

	//Create a pure quaterion
	glm::quat quat_Pure = po_GameObject_In->get_Rotation() * quat_RotationPoint * glm::conjugate(po_GameObject_In->get_Rotation());
	po_GameObject_In->set_Position(po_GameObject_In->get_Position() + glm::vec3(quat_Pure.x, quat_Pure.y, quat_Pure.z));

	//Force update children if it's a container
	if (po_GameObject_In->is_Container()) for (auto const& pair : po_GameObject_In->get_Children()) pair.second->force_Update();
}

void Respond_Movement::turn(GameObject_3D* po_GameObject_In, float f_Angle_In, glm::vec3 v3_TurnAxis_In)
{
	//Calculate new rotation
	glm::quat quat_Rot = glm::normalize(glm::angleAxis(glm::radians(f_Angle_In), glm::vec3(0, 1, 0)) * po_GameObject_In->get_Rotation());
	po_GameObject_In->update_Rotation(quat_Rot);

	//Force update children if it's a container
	if (po_GameObject_In->is_Container()) for (auto const& pair : po_GameObject_In->get_Children()) pair.second->force_Update();
}