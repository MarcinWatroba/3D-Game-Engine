#ifndef COLLISIONMANAGER_H
#define COLLISIONMANAGER_H

#include <Engine\Game_Objects\GameObject_3D.h>
#include <Engine\Game_Objects\Game_Object.h>
#include <Engine\Component\BoxCollider_3D.h>
#include <Engine\Component\RigidBody.h>

class CollisionManager
{

private:

public:
	CollisionManager();
	~CollisionManager();
	void collisionChecks(std::map<std::string, Game_Object*> &gameObjects);
};

#endif