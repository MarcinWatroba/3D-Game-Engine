#pragma once

#include <Engine\Scene\Scene.h>

class Game_Scene : public Scene
{
public:
	//Constructor
	Game_Scene() {};

	//Initialize
	void init();

	//Do something with keyboard input
	void keyboard_Input(GLfloat f_Delta_In, GLboolean* pab_KeyArray_In, GLboolean* pab_LockedKeys_In, int i_KeyPress);
	void mouse_Input(GLboolean* pab_MouseArray_In, GLboolean* pab_LockedMouse_In);
	void scroll_Input(glm::vec2 v2_Scroll_In);
	//Update the scene
	void update_Scene(GLfloat f_Delta_In, glm::vec2 v2_MousePos_In);

	//Render all scene objects
	void render();

	void clean_Up();

	void reload_Scene();
};