#pragma once

#include "Game/CharacterController/CharacterController_Data.h"
#include "Engine/FSM/FSM_State.h"
#include <vector>
#include <glm/glm.hpp>

class State_Patrol : public FSM_State<CharacterController_Data>
{
private:
	const float atPointDistance = 0.1f;//minimum distance that is considered to be at the point
	std::vector<glm::vec3> path;//patrol path points
	std::vector<float> wait;//time to wait at each point
	unsigned int pathStep;//current step along patrol path
	float timer;//
protected:
	void OnEnter();
	fsm::FSM_Command OnRun();
	void OnExit();
public:
	State_Patrol(const int setStateID);
};