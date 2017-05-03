#include "Game/AIController/State_Attack.h"
#include "Game/AIController/AIController_Data.h"
#include <Engine/Component/Transform_3D.h>
#include <Engine/Component/RigidBody.h>
#include <iostream>
#include <glm/gtx/norm.hpp>
#include <Engine/Component/Respond_Movement.h>

State_Attack::State_Attack(const int setStateID) :
	FSM_State<AIController_Data>(setStateID)
{}

void State_Attack::OnEnter()
{
	std::cout << "Attack_enter\n";
}

fsm::FSM_Command State_Attack::OnRun()
{
	std::cout << "Attack_run\n";
	//
	Respond_Movement* movement = static_cast<Respond_Movement*>(data->character->get_Component("Respond_Movement"));
	glm::vec3 toPoint = data->player->get_Position() - data->character->get_Position();

	//check if player has gone too far away
	if (glm::length2(toPoint) > data->stopChaseDistance*data->stopChaseDistance)
	{
		return fsm::Finish;
	}

	//if too far away move close enough to attack
	if (glm::length2(toPoint) > data->attackRange*data->attackRange)
	{
		movement->moveToPoint(data->character, data->player->get_Position(), 10.0f * data->deltaTime, data->dps * data->deltaTime);
	}

	//in attack range
	else
	{
		bool facingTarget = movement->facePoint(data->character, data->player->get_Position(), data->dps * data->deltaTime);
		if (facingTarget)
		{
			std::cout << "pew pew" << std::endl;
		}
	}

	//
	return fsm::Continue;
}

void State_Attack::OnExit()
{
	std::cout << "Attack_exit\n";
}