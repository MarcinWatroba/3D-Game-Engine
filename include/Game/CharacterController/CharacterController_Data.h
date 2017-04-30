#pragma once

#include "Engine/Astar/Node_Graph.h"
#include "Engine/Game_objects/GameObject_3D.h"

namespace ccs//character controller states
{
	enum CharacterController_States
	{
		Idle,
		Patrol,
		Attack,
		Dialogue
	};
}

struct CharacterController_Data
{
	float deltaTime;
	Node_Graph * AI_Map;
	GameObject_3D * character;
};