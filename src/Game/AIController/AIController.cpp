#include "Game/AIController/AIController.h"
#include "Game/AIController/State_Idle.h"
#include "Game/AIController/State_Patrol.h"
#include "Game/AIController/State_Attack.h"

const std::vector<FSM_State<AIController_Data>*> AIController::stateList({ new State_Idle(ccs::Idle), new State_Patrol(ccs::Patrol), new State_Attack(ccs::Attack) });

AIController::AIController(GameObject_3D * character) :
	FSM(&stateList, ccs::Idle)
{
	data.character = character;
}

void AIController::Update()
{
	Run();
}
