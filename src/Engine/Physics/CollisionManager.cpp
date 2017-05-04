#include <Engine\Physics\CollisionManager.h>


CollisionManager::CollisionManager()
{

}

CollisionManager::~CollisionManager()
{

}

void CollisionManager::collision(Game_Object* objectA, Game_Object* objectB, std::map<Game_Object*, Game_Object*>& collisions)
{
	//Collision with immov
	if (objectA->get_Parent())
	{
		if (!objectB->get_Components().count("RigidBody") || !objectA->get_Parent()->get_Components().count("RigidBody"))
		{
			//no rigid body attached to one of the input game objects
			return;
		}

		//std::cout << "Toppus Kekkus" << std::endl;
		if (objectB->get_Components().count("RigidBody") && objectA->get_Parent()->get_Components().count("RigidBody"))
		{
			//character collectables
			Character* character = dynamic_cast<Character*>(objectA->get_Parent()->get_Component("Character"));
			if (character != nullptr)
			{
				if (objectB->get_Tag() == "Ammo")
				{
					character->gainBullets(30);
					objectB->set_ToDelete();
				}
				else if (objectB->get_Tag() == "HealthPack")
				{
					character->gainLife(1);
					objectB->set_ToDelete();
				}
			}

			//other interactions
			RigidBody* tempBody = dynamic_cast<RigidBody*>(objectB->get_Components().at("RigidBody"));
			if (objectB->get_Tag() == "Enemy")
			{

			}
			else if (objectB->get_Tag() == "Floor")
			{
				std::cout << "Dab" << std::endl;
				dynamic_cast<RigidBody*>(objectA->get_Components().at("RigidBody"))->setGrounded(true);
			}
			else if (!tempBody->get_Moveable())
			{
				//Stop the object moving in the current direction
				collisions.insert(std::make_pair(objectA, objectB));
			}
		}
	}
}

void CollisionManager::collisionChecks(std::map<std::string, Game_Object*> &gameObjects)
{
	std::map<Game_Object*, Game_Object*> colChecks; // Body part of Robot, Thing it's colliding with


	//iterate over list of game objects
	for (auto const& pair : gameObjects)
	{
		//get collider if exists
		Game_Object* currentObject = pair.second;
		//skip if object is pending deletion
		if (currentObject->get_ToDelete()) { continue; }

		if (currentObject->get_Components().count("BoxCollider_3D"))
		{
			BoxCollider_3D* firstCollider = dynamic_cast<BoxCollider_3D*>(currentObject->get_Components().at("BoxCollider_3D"));

			//for every collidable object iterate over list of objects again to check for collisions
			for (auto const& pair : gameObjects)
			{
				//skip if second object is same as first or if second object is pending deletion
				if (currentObject == pair.second || pair.second->get_ToDelete()) 
				{ 
					continue; 
				}

				BoxCollider_3D* secondCollider = dynamic_cast<BoxCollider_3D*>(pair.second->get_Component("BoxCollider_3D"));
				if (secondCollider != nullptr)
				{
					//check if colliding
					if (firstCollider->intersects(*secondCollider))
					{
						collision(currentObject, pair.second, colChecks);
					}
				}
			}
		}

		if (static_cast<GameObject_3D*>(currentObject)->get_BulletList().size() != 0)
		{
			for (int i = 0; i < static_cast<GameObject_3D*>(currentObject)->get_BulletList().size(); i++)
			{
				Game_Object* bullet = static_cast<GameObject_3D*>(currentObject)->get_BulletList()[i];
				if (bullet->get_Components().count("BoxCollider_3D"))//bullets always have boxcollider
				{
					BoxCollider_3D* tempCol = dynamic_cast<BoxCollider_3D*>(bullet->get_Components().at("BoxCollider_3D"));
					for (auto const& pair2 : gameObjects)
					{
						if (pair == pair2) { continue; }//ignore object that bullet belongs to

						BoxCollider_3D* secondCol = dynamic_cast<BoxCollider_3D*>(pair2.second->get_Component("BoxCollider_3D"));

						//'hack' to fix hitting robot:
						//if (secondCol == nullptr && pair2.second->get_Children().size() != 0)
						//{
						//	for (auto const& pair3 : pair2.second->get_Children())
						//	{
						//		//if child has a BoxCollider set collider to that and break out of the loop
						//		secondCol = dynamic_cast<BoxCollider_3D*>(pair3.second->get_Component("BoxCollider_3D"));
						//		if (secondCol != nullptr) { break; }
						//	}
						//}


						if (secondCol != nullptr)
						{
							if (pair2.second->get_Name() == "Robot Body")//so I was wrong about child components not being in the list 
							{
								bool a = 1;//junk code just so a breakpoint can be placed here, gets here
							}

							bool check = tempCol->intersects(*secondCol);//always false without hack, but hack works...
							if (check)
							{

								if (pair2.second->get_Name() == "Robot Body")
								{
									bool a = 1;//junk code just so a breakpoint can be placed here, never gets here
								}

								//std::cout << "Toppus Kekkus" << std::endl;
								if ((pair2.second->get_Components().count("RigidBody") && bullet->get_Components().count("RigidBody")))
								{
									RigidBody* tempBody;
									if (pair2.second->get_Parent())
									{
										tempBody = dynamic_cast<RigidBody*>(pair2.second->get_Parent()->get_Components().at("RigidBody"));
									}
									else
									{
										tempBody = dynamic_cast<RigidBody*>(pair2.second->get_Components().at("RigidBody"));
									}
									
									//enemy shot by player
									if (currentObject->get_Name() == "Robot")
									{
										if (pair2.second->get_Tag() == "Enemy")
										{
											colChecks.insert(std::make_pair(bullet, pair2.second));
											dynamic_cast<Character*>(pair2.second->get_Components().at("Character"))->loseLife();
											if (dynamic_cast<Character*>(pair2.second->get_Components().at("Character"))->getHealth() == 0)
											{
												pair2.second->set_ToDelete();
											}
										}
										else if (!tempBody->get_Moveable())
										{
											//Stop the object moving in the current direction
											colChecks.insert(std::make_pair(bullet, pair2.second));
										}
									}
									else
									{
										//player shot by enemy
										if (pair2.second->get_Name() == "Robot")
										{
											if (currentObject->get_Tag() == "Enemy")
											{
												//... exact code as enemy shot player
												colChecks.insert(std::make_pair(bullet, pair2.second));
												dynamic_cast<Character*>(pair2.second->get_Components().at("Character"))->loseLife();
												if (dynamic_cast<Character*>(pair2.second->get_Components().at("Character"))->getHealth() == 0)
												{
													pair2.second->set_ToDelete();
												}
											}
										}
										colChecks.insert(std::make_pair(bullet, pair2.second));
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
		if (gameObjects.count("Robot"))
		{
			for (auto const& pair : gameObjects.at("Robot")->get_Children())
			{
				if (pair.second->get_Components().count("BoxCollider_3D"))
				{
					dynamic_cast<BoxCollider_3D*>(pair.second->get_Components().at("BoxCollider_3D"))->setCollisionCheck(false);
				}
			}
		}
		
		for (auto const& pair : gameObjects)
		{
			if (static_cast<GameObject_3D*>(pair.second)->get_BulletList().size() != 0)
			{
				for (int i = 0; i < static_cast<GameObject_3D*>(pair.second)->get_BulletList().size(); i++)
				{
					static_cast<BoxCollider_3D*>(static_cast<GameObject_3D*>(pair.second)->get_BulletList()[i]->get_Components().at("BoxCollider_3D"))->setCollisionCheck(false);
				}
			}
		}
	}
}