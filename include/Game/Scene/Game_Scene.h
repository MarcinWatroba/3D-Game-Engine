#pragma once

#include <Engine\Scene\Scene.h>
//#include <Scene.h>
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
	bool rendered;
	bool b_Render[render::Num];
	bool b_SwitchCamMode;
	glm::vec3 light[30];
	glm::vec3 pos[100];
	glm::uvec2 depth[30];
	float radius[30];

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