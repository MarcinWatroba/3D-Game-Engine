#pragma once

#include "Engine/FSM/FSM.h"
#include "Engine/Scene/Scene.h"
#include "Engine/Component/Component.h"
#include "Engine/Game_Objects/GameObject_3D.h"
#include "Game/CharacterController/CharacterController_Data.h"

class CharacterController : public FSM<CharacterController_Data>, public Component
{
private:
	static const std::vector<FSM_State<CharacterController_Data>*> stateList;
public:
	void Update(Scene* po_Scene_in);
	CharacterController(GameObject_3D * character);
};