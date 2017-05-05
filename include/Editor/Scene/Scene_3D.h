#pragma once

#include <Engine\Scene\Scene.h>
#include <Engine\Loaders\SceneSaver.h>


namespace Conditions
{
	enum Conditions {
		Move_Mouse,
		Alt_Press,
		LeftMouse_Button,
		RightMouse_Button,
		IsColourPick,
		Moving,
		Arrow_Moving,
		Arrow_Scaling,
		Arrow_Rotation,
		Stop_Arrow,
		Selection,
		ListenToKeyboard,
		ShiftDetected,
		Num
	};
}

class Interface;
class Camera_2D;

class Scene_3D : public Scene
{
private:
	float f_Speed;
	std::map<std::string, int> msio_ObjectIDs;
	int pickedID;
	int previousPicked;
	Camera_2D* camera_2D;
	Camera_3D* arrow_Cam;
	GameObject_3D* picked_Object;
	bool b_Conditions[Conditions::Num];
	glm::vec2 v2_MousePos;

	void add_Arrows();
	void render_ColourScene();
	std::string to3DVectorString(glm::vec3 pc_Vector3D_In);
	void process_3DClick(float f_Delta_In, glm::vec2 v2_MousePos_In);
	void process_2DClick(int i_ID_In);
	SceneSaver* save;
public:
	//Constructor
	Scene_3D() {};

	//Initialize
	void init();

	void add_GUI();

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