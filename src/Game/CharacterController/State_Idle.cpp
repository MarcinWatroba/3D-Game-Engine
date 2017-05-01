#include "Game/CharacterController/State_Idle.h"
#include <iostream>

State_Idle::State_Idle(const int setStateID) :
	FSM_State<CharacterController_Data>(setStateID)
{}

void State_Idle::OnEnter()
{
	//std::cout << "Idle_enter\n";
}

fsm::FSM_Command State_Idle::OnRun()
{
	//std::cout << "Idle_run\n";
	//

	//
	return fsm::Continue;
}

void State_Idle::OnExit()
{
	//std::cout << "Idle_exit\n";
}