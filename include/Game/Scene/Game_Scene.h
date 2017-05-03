#pragma once

#include <Engine\Scene\Scene.h>
#include <Engine\Scene\Scene.h>
#include <Engine\Lighting\Light.h>
#include <Engine\Lighting\Point_Light.h>

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
	bool b_Render[render::Num];
	bool b_SwitchCamMode;

	// the following variables are used to help control when audio is played
	// moving
	int walkCount = 0;
	int walkRate = 35;
	// firing
	int triggerHoldCount = 0;
	int ammoRemaining = 6;
	int firerate = 100;
	
public:
	//Constructor
	Game_Scene() {};

	//Initialize
	void init();

	//Do something with keyboard input
	void keyboard_Input(GLfloat f_Delta_In, GLboolean* pab_KeyArray_In, GLboolean* pab_LockedKeys_In);
	void mouse_Input(GLboolean* pab_MouseArray_In);

	//Update the scene
	void update_Scene(GLfloat f_Delta_In, glm::vec2 v2_MousePos_In);

	//Render all scene objects
	void render();

	void clean_Up();

	void reload_Scene();
};