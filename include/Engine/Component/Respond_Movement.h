#pragma once
#include <Engine\Component\Component.h>

class GameObject_3D;

class Respond_Movement : public Component
{
public:
	Respond_Movement() {};
	void move(GameObject_3D* po_GameObject_In, glm::vec3 v3_Direction_In, float f_Speed_In);
	void turn(GameObject_3D* po_GameObject_In, float f_Angle_In, glm::vec3 v3_TurnAxis_In);
};