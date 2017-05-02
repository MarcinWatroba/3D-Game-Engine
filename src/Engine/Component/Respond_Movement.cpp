#include <Engine\Component\Respond_Movement.h>
#include <Engine\Game_Objects\GameObject_3D.h>
#include <Engine\Component\Transform_3D.h>
#include <glm/gtx/norm.hpp>

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

#include <iostream>
bool Respond_Movement::facePoint(GameObject_3D* po_GameObject_In, glm::vec3 v3_Target_In, float f_rotation)
{
	if (po_GameObject_In->get_Position() == v3_Target_In) { return false; }
	glm::vec3 toPoint = v3_Target_In - po_GameObject_In->get_Position();
	toPoint.y = 0;
	if (toPoint == glm::vec3(0,0,0)) { return false; }

	Transform_3D* transform = static_cast<Transform_3D*>(po_GameObject_In->get_Component("Transform_3D"));
	glm::vec3 forward = transform->get_Forward();
	glm::vec3 up = transform->get_Up();
	glm::vec3 aim = glm::normalize(toPoint);

	//dot product of the aim vector and the left direction vector gives
	//positive values for left turns and negative values for right turns
	float cosTheta = glm::dot(aim, -transform->get_Right());
	std::cout << cosTheta << std::endl;
	//get the desired rotation angle using the dot product
	float angle = glm::degrees(glm::acos(glm::dot(aim, forward)));
	if (cosTheta < 0) { angle = -angle; }
	std::cout << angle << std::endl;

	//rotate toward point by the given rotation amount
	if (angle > f_rotation)
	{
		po_GameObject_In->turn(-f_rotation, up);
	}
	else if (angle < -f_rotation)
	{
		po_GameObject_In->turn(f_rotation, up);
	}
	//rotation will overshoot angle to target, move by smaller amount to face toward point
	else
	{
		po_GameObject_In->turn(angle, up);
		return true;
	}

	//
	return false;
}

bool Respond_Movement::atPoint(GameObject_3D* po_GameObject_In, glm::vec3 v3_Target_In, float f_tolerance)
{
	glm::vec3 dist = v3_Target_In - po_GameObject_In->get_Position();
	//avoid square root by comparing the sqaured distances
	return (glm::length2(dist) < f_tolerance*f_tolerance);
}

bool Respond_Movement::withinRange(GameObject_3D* po_GameObject_In, glm::vec3 v3_Target_In, float f_range)
{
	return atPoint(po_GameObject_In, v3_Target_In, f_range);
}

bool Respond_Movement::moveToPoint(GameObject_3D* po_GameObject_In, glm::vec3 v3_Target_In, float f_Speed_In, float f_rotation, float f_tolerance)
{
	//at the point already
	if (atPoint(po_GameObject_In, v3_Target_In, f_tolerance)) { return true; }

	//turn to face the point
	bool facingPoint = facePoint(po_GameObject_In, v3_Target_In, f_rotation);

	//if facing point move forward
	if (facingPoint)
	{
		float dist = glm::length(po_GameObject_In->get_Position() - v3_Target_In);
		move(po_GameObject_In, glm::vec3(0, 0, 1), dist);
		return true;
		////move toward the point by the given move speed
		//if (dist > f_Speed_In)
		//{
		//	move(po_GameObject_In, glm::vec3(0, 0, 1), f_Speed_In);
		//}
		////move step would overshoot target, move exactly to point
		//else
		//{
		//	move(po_GameObject_In, glm::vec3(0, 0, 1), dist);
		//	return true;
		//}
	}
	return false;
}