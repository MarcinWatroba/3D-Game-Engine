#include <Game\Scene\Game_Scene.h>
#include <GLFW\glfw3.h>
#include <Engine/Mesh/Mesh_3D.h>
#include <Engine\Game_Objects\GameObject_3D.h>
#include <Engine\Loaders\SceneLoader.h>
#include <Engine/Component/RenderComp_3D.h>
#include <Engine\Component\Transform_3D.h>
#include <Engine\Lighting\Light.h>
#include <Game\AIController\AIController.h>
#include <Game\Misc\Bullet.h>

#include <iostream>

//Initialize everything once
void Game_Scene::init()
{
	//Initialize
	lock_mouse(true);
	b_Init = false;

	camera_3D = new Camera_3D(45.f, 800.f / 600, 0.1f, 1000.f);
	camera_3D->set_CameraPos(glm::vec3(0.f, -20.f, 0.f));

	//Load the scene
	o_SceneLoader = new SceneLoader("assets/scenes/Robot_Scene.xml", po_Loader, mspo_Objects);
	b_Init = true;
	player = static_cast<GameObject_3D*>(mspo_Objects.find("Robot")->second);
}

//Do something with keyboard input
void Game_Scene::keyboard_Input(GLfloat f_Delta_In, GLboolean* pab_KeyArray_In, GLboolean* pab_LockedKeys_In)
{
	if (!b_Init) { return; }
	float f_Speed = 20 * f_Delta_In;
	float f_MagicNumber = 0.7071f;
	float moveSpeed = .3f;

	if (pab_KeyArray_In[GLFW_KEY_W])
	{
		camera_3D->set_Speed(f_Speed);
		camera_3D->move_Forward();
	}

	if (pab_KeyArray_In[GLFW_KEY_S])
	{
		camera_3D->set_Speed(f_Speed);
		camera_3D->move_Backward();
	}
		
	if (pab_KeyArray_In[GLFW_KEY_A])
	{
		camera_3D->set_Speed(f_Speed);
		camera_3D->move_Left();
	}

	if (pab_KeyArray_In[GLFW_KEY_D])
	{
		camera_3D->set_Speed(f_Speed);
		camera_3D->move_Right();
	}
		
	if (pab_KeyArray_In[GLFW_KEY_SPACE])
	{
		camera_3D->set_Speed(f_Speed);
		camera_3D->fly_Up();
	}

	if (pab_KeyArray_In[GLFW_KEY_LEFT_CONTROL])
	{
		camera_3D->set_Speed(f_Speed);
		camera_3D->fly_Down();
	}


	if (pab_KeyArray_In[GLFW_KEY_R] && !pab_LockedKeys_In[GLFW_KEY_R])
	{
		reload_Scene();

		pab_LockedKeys_In[GLFW_KEY_R] = true;

	}
	if (!pab_KeyArray_In[GLFW_KEY_R]) pab_LockedKeys_In[GLFW_KEY_R] = false;

	
	if (pab_KeyArray_In[GLFW_KEY_ESCAPE] && !pab_LockedKeys_In[GLFW_KEY_ESCAPE])
	{
		lock_mouse(false);
	}
	if (!pab_KeyArray_In[GLFW_KEY_ESCAPE]) pab_LockedKeys_In[GLFW_KEY_ESCAPE] = false;

	//player movement
	auto playerLookup = mspo_Objects.find("Robot");
	if (playerLookup == mspo_Objects.end()) { return; }
	player = static_cast<GameObject_3D*>(playerLookup->second);

	if (pab_KeyArray_In[GLFW_KEY_UP])
	{
		player->move(glm::vec3(0, 0, 1), moveSpeed * f_Delta_In);
		glm::vec3 tempVec = player->get_Position();
		std::cout << "(" << tempVec.x << ", " << tempVec.y << ", " << tempVec.z << " )" << std::endl;
		//mspo_Objects.find("Robot Left Arm")->second->animate(40.f, f_Delta_In);
		//mspo_Objects.find("Robot Right Arm")->second->animate(-40.f, f_Delta_In);
		//mspo_Objects.find("Robot Left Leg")->second->animate(-40.f, f_Delta_In);
		//mspo_Objects.find("Robot Right Leg")->second->animate(40.f, f_Delta_In);
	}
	if (pab_KeyArray_In[GLFW_KEY_DOWN])
	{
		player->move(glm::vec3(0, 0, 1), -moveSpeed * f_Delta_In);

		//mspo_Objects.find("Robot Left Arm")->second->animate(40.f, f_Delta_In);
		//mspo_Objects.find("Robot Right Arm")->second->animate(-40.f, f_Delta_In);
		//mspo_Objects.find("Robot Left Leg")->second->animate(-40.f, f_Delta_In);
		//mspo_Objects.find("Robot Right Leg")->second->animate(40.f, f_Delta_In);
	}

	if (pab_KeyArray_In[GLFW_KEY_F])
	{
		static_cast<RigidBody*>(player->get_Components().at("RigidBody"))->setJumpForce(0.13f);
		static_cast<RigidBody*>(player->get_Components().at("RigidBody"))->setGrounded(false);
	}

	if (pab_KeyArray_In[GLFW_KEY_LEFT]) player->turn(80.f * f_Delta_In, glm::vec3(0.f, 1.f, 0.f));
	if (pab_KeyArray_In[GLFW_KEY_RIGHT]) player->turn(-80.f * f_Delta_In, glm::vec3(0.f, 1.f, 0.f));
}

void Game_Scene::mouse_Input(GLboolean* pab_MouseArray_In, GLfloat f_Delta_In)
{
	if (!b_Init) { return; }

	//player shootsching
	auto playerLookup = mspo_Objects.find("Robot");
	if (playerLookup == mspo_Objects.end()) { return; }
	player = static_cast<GameObject_3D*>(playerLookup->second);

	if (pab_MouseArray_In[GLFW_MOUSE_BUTTON_1])
	{

		player->createBullet(new Bullet("Bullet", po_Loader->get_Mesh3D("7"), static_cast<GameObject_3D*>(mspo_Objects.find("Robot")->second), po_Loader->get_Texture("24"), po_Loader->get_Texture("7")));
		player->setFiring(true);
		shooting = true;
		//std::cout << "Shoosting time!!!" << std::endl;
		//glm::vec3 temp = static_cast<GameObject_3D*>(mspo_Objects.find("Bullet")->second)->get_Position();
		//std::cout << "(" << temp.x << ", " << temp.y << ", " << temp.z << ")" << std::endl << std::endl;
	}
	if (!pab_MouseArray_In[GLFW_MOUSE_BUTTON_1])
	{
		shooting = false;
	}
}

void Game_Scene::reload_Scene()
{
	clean_Up();
	b_Init = false;
}

//Update the scene
void Game_Scene::update_Scene(GLfloat f_Delta_In, glm::vec2 v2_MousePos_In)
{
	
	////Initialize
	if (!b_Init) init();

	auto playerLookup = mspo_Objects.find("Robot");
	if (playerLookup != mspo_Objects.end()) { player = static_cast<GameObject_3D*>(playerLookup->second); }
	else { player = nullptr; }

	if (b_Init)
	{
		for (auto const& pair : mspo_Objects)
		{
			GameObject_3D* po_GameObject = dynamic_cast<GameObject_3D*>(pair.second);
		
			//update game object
			po_GameObject->update();
		
			//update game components
			Component * po_Component;
		
			//Update AI character controller
			po_Component = po_GameObject->get_Component("Character_Controller");
			if (po_Component != nullptr) {
				//cast
				AIController* po_AIController = static_cast<AIController*>(po_Component);
				//set data
				AIController_Data* po_ccd = po_AIController->AccessData();
				po_ccd->deltaTime = f_Delta_In;
				po_ccd->player = player;
				po_ccd->loader = po_Loader;
				//update
				po_AIController->Update();
			}
		
			//Rigid Body
			po_Component = po_GameObject->get_Component("RigidBody");
			if (po_Component != nullptr) {
				//cast
				RigidBody* po_RigidBody = static_cast<RigidBody*>(po_Component);
				//update
				po_RigidBody->update(po_GameObject->get_Position());
			}
		}
		
		camera_3D->move_Keyboard(f_Delta_In);
		camera_3D->move_Mouse(f_Delta_In, v2_MousePos_In);
		camera_3D->update();
		camera_3D->reset();

		if (player != nullptr)
		{
			dynamic_cast<GameObject_3D*>(mspo_Objects.find("Robot")->second)->jump(glm::vec3(0, 1, 0));
			//shootBullet();
			if (!shooting)
			{
				static_cast<GameObject_3D*>(mspo_Objects.find("Robot")->second)->resetCount();
			}
		}

		//Check for Collisions between Game Objects
		colManage.collisionChecks(mspo_Objects);
		
		if (mspo_Objects.at("Robot")->get_ToDelete())
		{
			//Game over!
			clean_Up();
		}

		//delete objects that have deletion flag
		auto itr = mspo_Objects.begin();
		while (itr != mspo_Objects.end()) {
			if (itr->second->get_ToDelete()) {
				destroyGameObject(itr->second);
				itr = mspo_Objects.erase(itr++);
			}
			else { ++itr; }
		}
	}
}

//Render all scene objects
void Game_Scene::render()
{
	glClearColor(0.1f, 0.1f, 0.1f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	if (b_Init)
	{
		glUseProgram(po_Loader->get_Shader("0")->get_Program());
		camera_3D->update_Shader(po_Loader->get_Shader("0"));
		o_SceneLoader->set_LightAmount(po_Loader->get_Shader("0"));

		for (auto const& pair : mspo_Objects)
		{
			if (pair.second->get_Tag() == "Object" || pair.second->get_Tag() == "Enemy" || pair.second->get_Tag() == "Player" || pair.second->get_Tag() == "Floor" || pair.second->get_Tag() == "Ammo" ) pair.second->render(po_Loader->get_Shader("0"));
			else if (pair.second->get_Tag() == "Light")
			{
				static_cast<Light*>(pair.second)->update_Shader(po_Loader->get_Shader("0"));
				pair.second->render(po_Loader->get_Shader("0"));
			}
		}
	}
}


void Game_Scene::load_Scene(int i)
{
	if (levelList.count(i))
	{
		std::string sLevel = levelList.at(i);
		o_SceneLoader = new SceneLoader(sLevel.c_str(), po_Loader, mspo_Objects);
		b_Init = true;
		player = static_cast<GameObject_3D*>(mspo_Objects.find("Robot")->second);
	}

}

void Game_Scene::destroyGameObject(Game_Object* po_object)
{
	//Remove all components
	for (auto const& components : po_object->get_Components())
	{
		if (components.first != "Mesh_3D") delete components.second;
	}
	po_object->get_Components().clear();

	//destroy the game object
	delete po_object;
}

void Game_Scene::clean_Up()
{
	if (!mspo_Objects.empty())
	{
		//For each object
		for (auto const& pair : mspo_Objects)
		{
			destroyGameObject(pair.second);
		}

		mspo_Objects.clear();
	}

	delete o_SceneLoader;
	delete camera_3D;
}


