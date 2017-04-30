#include "Game/CharacterController/CharacterController.h"
#include "Game/CharacterController/State_Idle.h"
#include "Game/CharacterController/State_Patrol.h"

const std::vector<FSM_State<CharacterController_Data>*> CharacterController::stateList({ new State_Idle(ccs::Idle), new State_Patrol(ccs::Patrol) });

CharacterController::CharacterController(GameObject_3D * character) :
	FSM(&stateList, ccs::Idle)
{
	data.character = character;
}

void CharacterController::Update(Scene* po_Scene_in)
{
	Run();
}
