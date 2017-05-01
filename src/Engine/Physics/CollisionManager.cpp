#include <Engine\Physics\CollisionManager.h>


CollisionManager::CollisionManager()
{

}

CollisionManager::~CollisionManager()
{

}

void CollisionManager::collisionChecks(std::map<std::string, Game_Object*> &gameObjects)
{
	std::map<Game_Object*, Game_Object*> colChecks; // Body part of Robot, Thing it's colliding with
	for (auto const& pair : gameObjects)
	{
		Game_Object* currentObject = pair.second;
		if (currentObject->get_Components().count("BoxCollider_3D"))
		{
			BoxCollider_3D* tempCol = dynamic_cast<BoxCollider_3D*>(currentObject->get_Components().at("BoxCollider_3D"));
			for (auto const& pair : gameObjects)
			{
				if (currentObject != pair.second)
				{
					if (pair.second->get_Components().count("BoxCollider_3D"))
					{
						BoxCollider_3D* secondCol = dynamic_cast<BoxCollider_3D*>(pair.second->get_Components().at("BoxCollider_3D"));
						bool check = tempCol->intersects(*secondCol);
						if (check)
						{
							
							//Collision with immov
							if (currentObject->get_Parent())
							{
								std::cout << "Toppus Kekkus" << std::endl;
								if (pair.second->get_Components().count("RigidBody") && currentObject->get_Parent()->get_Components().count("RigidBody"))
								{
									RigidBody* tempBody = dynamic_cast<RigidBody*>(pair.second->get_Components().at("RigidBody"));
									if (!tempBody->get_Moveable())
									{
										//Stop the object moving in the current direction
										colChecks.insert(std::make_pair(currentObject, pair.second));

									}
								}
							}
						}
					}
				}
			}
		}

	}
	if (colChecks.size() != 0)
	{
		for (auto const& pair : colChecks)
		{
			dynamic_cast<BoxCollider_3D*>(pair.first->get_Components().at("BoxCollider_3D"))->setCollisionCheck(true);
		}
	}
	else
	{
		for (auto const& pair : gameObjects.at("Robot")->get_Children())
		{
			if (pair.second->get_Components().count("BoxCollider_3D"))
			{
				dynamic_cast<BoxCollider_3D*>(pair.second->get_Components().at("BoxCollider_3D"))->setCollisionCheck(false);
			}
		}
	}
}