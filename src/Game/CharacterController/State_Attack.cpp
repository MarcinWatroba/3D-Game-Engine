#include "Game/CharacterController/State_Attack.h"
#include "Game/CharacterController/CharacterController_Data.h"
#include <iostream>

State_Attack::State_Attack(const int setStateID) :
	FSM_State<CharacterController_Data>(setStateID)
{}

void State_Attack::OnEnter()
{
	std::cout << "Attack_enter\n";
}

fsm::FSM_Command State_Attack::OnRun()
{
	std::cout << "Attack_run\n";
	//

	//
	return fsm::Continue;
}

void State_Attack::OnExit()
{
	std::cout << "Attack_exit\n";
}