#include <Game\Scene\Game_Scene.h>
#include <GLFW\glfw3.h>
#include <Engine/Mesh/Mesh_3D.h>
#include <Engine\Game_Objects\GameObject_3D.h>
#include <Engine\Loaders\SceneLoader.h>
#include <Engine/Component/RenderComp_3D.h>
#include <Engine\Component\Transform_3D.h>
#include <Engine\Lighting\Light.h>
#include <Game\CharacterController\CharacterController.h>

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
}

//Do something with keyboard input
void Game_Scene::keyboard_Input(GLfloat f_Delta_In, GLboolean* pab_KeyArray_In, GLboolean* pab_LockedKeys_In)
{
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
	if (pab_KeyArray_In[GLFW_KEY_UP])
	{
		static_cast<GameObject_3D*>(mspo_Objects.find("Robot")->second)->move(glm::vec3(0, 0, 1), -moveSpeed * f_Delta_In);
		glm::vec3 tempVec = static_cast<GameObject_3D*>(mspo_Objects.find("Robot")->second)->get_Position();
		//mspo_Objects.find("Robot Left Arm")->second->animate(40.f, f_Delta_In);
		//mspo_Objects.find("Robot Right Arm")->second->animate(-40.f, f_Delta_In);
		//mspo_Objects.find("Robot Left Leg")->second->animate(-40.f, f_Delta_In);
		//mspo_Objects.find("Robot Right Leg")->second->animate(40.f, f_Delta_In);
	}
	if (pab_KeyArray_In[GLFW_KEY_DOWN])
	{
		static_cast<GameObject_3D*>(mspo_Objects.find("Robot")->second)->move(glm::vec3(0, 0, 1), moveSpeed * f_Delta_In);

		//mspo_Objects.find("Robot Left Arm")->second->animate(40.f, f_Delta_In);
		//mspo_Objects.find("Robot Right Arm")->second->animate(-40.f, f_Delta_In);
		//mspo_Objects.find("Robot Left Leg")->second->animate(-40.f, f_Delta_In);
		//mspo_Objects.find("Robot Right Leg")->second->animate(40.f, f_Delta_In);
	}
	
	if (pab_KeyArray_In[GLFW_KEY_LEFT]) static_cast<GameObject_3D*>(mspo_Objects.find("Robot")->second)->turn(80.f * f_Delta_In, glm::vec3(0.f, 1.f, 0.f));
	if (pab_KeyArray_In[GLFW_KEY_RIGHT]) static_cast<GameObject_3D*>(mspo_Objects.find("Robot")->second)->turn(-80.f * f_Delta_In, glm::vec3(0.f, 1.f, 0.f));
}

void Game_Scene::mouse_Input(GLboolean* pab_MouseArray_In, GLfloat f_Delta_In)
{
	if (pab_MouseArray_In[GLFW_MOUSE_BUTTON_1])
	{
		static_cast<GameObject_3D*>(mspo_Objects.find("Robot")->second)->createBullet(*static_cast<GameObject_3D*>(mspo_Objects.find("Bullet")->second));
		static_cast<GameObject_3D*>(mspo_Objects.find("Robot")->second)->setFiring(true);
		//std::cout << "Shoosting time!!!" << std::endl;
		//glm::vec3 temp = static_cast<GameObject_3D*>(mspo_Objects.find("Bullet")->second)->get_Position();
		//std::cout << "(" << temp.x << ", " << temp.y << ", " << temp.z << ")" << std::endl << std::endl;
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

	if (b_Init)
	{
		for (auto const& pair : mspo_Objects)
		{
			Game_Object * po_GameObject = pair.second;

			//update game object
			po_GameObject->update();

			//update game components
			Component * po_Component;
			//Update AI character controller
			po_Component = po_GameObject->get_Component("Character_Controller");
			if (po_Component != nullptr) {
				//cast
				CharacterController* po_CharacterController = static_cast<CharacterController*>(po_Component);
				//set data
				CharacterController_Data* po_ccd = po_CharacterController->AccessData();
				po_ccd->deltaTime = f_Delta_In;
				//update
				po_CharacterController->Update(this);
			}
			//other components...
		}
		
		camera_3D->move_Keyboard(f_Delta_In);
		camera_3D->move_Mouse(f_Delta_In, v2_MousePos_In);
		camera_3D->update();
		camera_3D->reset();

		dynamic_cast<GameObject_3D*>(mspo_Objects.find("Robot")->second)->jump(glm::vec3(0, 1, 0));
		//shootBullet();
		//Check for Collisions between Game Objects
		colManage.collisionChecks(mspo_Objects);
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
			if (pair.second->get_Tag() == "Object") pair.second->render(po_Loader->get_Shader("0"));
			else if (pair.second->get_Tag() == "Light")
			{
				static_cast<Light*>(pair.second)->update_Shader(po_Loader->get_Shader("0"));
				pair.second->render(po_Loader->get_Shader("0"));
			}
		}
	}
}

void Game_Scene::clean_Up()
{
	if (!mspo_Objects.empty())
	{
		//For each object
		for (auto const& pair : mspo_Objects)
		{
			//Remove all components
			for (auto const& components : pair.second->get_Components()) if (components.first != "Mesh_3D") delete components.second;

			pair.second->get_Components().clear();
			delete pair.second;
		}

		mspo_Objects.clear();
	}

	delete o_SceneLoader;
	delete camera_3D;
}


