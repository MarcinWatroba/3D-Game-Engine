#include "Game/CharacterController/State_Patrol.h"
#include "Game/CharacterController/CharacterController_Data.h"
#include <iostream>
#include <glm/gtx/norm.hpp>

State_Patrol::State_Patrol(const int setStateID) :
	FSM_State<CharacterController_Data>(setStateID)
{}

void State_Patrol::OnEnter()
{
	std::cout << "Patrol_enter\n";
	pathStep = 0;
	timer = 0.0f;
	//set patrol path and wait times
	path.push_back(glm::vec3(0.0f, 0.0f, 0.0f));
	path.push_back(glm::vec3(10.0f, 10.0f, 10.0f));
	wait.push_back(1.0f);
	wait.push_back(1.0f);
}

fsm::FSM_Command State_Patrol::OnRun()
{
	std::cout << "Patrol_run\n";
	//

	//character not yet at the point
	if (glm::length2(data->character->get_Position() - path[pathStep]) > atPointDistance)
	{
		///move character to position, need character movement implementation
	}
	//character is at the point
	else
	{
		//wait for the given time
		timer += data->deltaTime;
		if (timer > wait[pathStep])
		{
			//reset timer and increment path step
			timer = 0.0f;
			pathStep++;
			if (pathStep == path.size()) { pathStep = 0; }
		}
	}

	//
	return fsm::Continue;
}

void State_Patrol::OnExit()
{
	std::cout << "Patrol_exit\n";
}