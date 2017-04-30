#pragma once

#include "Game/CharacterController/CharacterController_Data.h"
#include "Engine/FSM/FSM_State.h"

class State_Idle : public FSM_State<CharacterController_Data>
{
protected:
	void OnEnter();
	fsm::FSM_Command OnRun();
	void OnExit();
public:
	State_Idle(const int setStateID);
};