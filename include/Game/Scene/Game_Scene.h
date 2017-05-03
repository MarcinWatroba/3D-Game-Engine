#pragma once

#include <Engine\Scene\Scene.h>
#include <Engine\Physics\CollisionManager.h>
//#include <Label.h>
//#include <Directional_Light.h>
//#include <Point_Light.h>

namespace render
{
	enum Render_ID
	{
		Alpha,
		Num
	};
}

class Game_Scene : public Scene
{
private:
	//Label* o_Label;
	bool b_Render[render::Num];
	bool b_SwitchCamMode;
	bool shooting = false;

	//Collision Manager
	CollisionManager colManage;
	GameObject_3D* player;

public:
	//Constructor
	Game_Scene() {};

	//Initialize
	void init();

	//Do something with keyboard input
	void keyboard_Input(GLfloat f_Delta_In, GLboolean* pab_KeyArray_In, GLboolean* pab_LockedKeys_In);
	void mouse_Input(GLboolean* pab_MouseArray_In, GLfloat f_Delta_In);

	//Update the scene
	void update_Scene(GLfloat f_Delta_In, glm::vec2 v2_MousePos_In);

	//Render all scene objects
	void render();

	void clean_Up();

	void reload_Scene();


};