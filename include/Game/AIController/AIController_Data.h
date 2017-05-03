#pragma once

#include "Engine/Astar/Node_Graph.h"
#include "Engine/Game_objects/GameObject_3D.h"

namespace ccs//character controller states
{
	enum AIController_States
	{
		Idle,
		Patrol,
		Attack,
		Dialogue
	};
}

struct AIController_Data
{
	//maximum distance to begin switch to chasing and attacking the player
	const float startChaseDistance = 15.0f;
	//distance to stop chasing the player
	const float stopChaseDistance = 10.0f;
	//maximum distance to use character attack
	const float attackRange = 5.0f;
	//character turn speed, degrees per seconds
	const float dps = 360.0f;
	//time step
	float deltaTime;
	//AI map
	Node_Graph * AI_Map;
	//pointer to this AI character
	GameObject_3D * character;
	//pointer to the player character
	GameObject_3D * player;
};