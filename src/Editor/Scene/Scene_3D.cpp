#include <Editor\Scene\Scene_3D.h>
#include <GLFW\glfw3.h>
#include <Engine/Mesh/Mesh_3D.h>
#include <Engine\Game_Objects\GameObject_3D.h>
#include <Engine\Loaders\SceneLoader.h>
#include <Engine/Component/RenderComp_3D.h>
#include <Engine\Component\Transform_3D.h>
#include <Engine\Lighting\Light.h>
#include <iostream>
#include <Editor\Objects\Arrow_3D.h>
#include <Engine\Game_Objects\Camera_2D.h>
#include <Engine\GUI\Button.h>
#include <Engine\GUI\Textbox.h>
#include <Engine\GUI\Text.h>
#include <algorithm>

void Scene_3D::add_Arrows()
{
	glm::quat quat_RedArrow = glm::angleAxis(glm::radians(-90.f), glm::vec3(0.f, 0.f, 1.f));
	glm::quat quat_GreenArrow = glm::angleAxis(glm::radians(0.f), glm::vec3(0.f, 1.f, 0.f));
	glm::quat quat_BlueArrow = glm::angleAxis(glm::radians(-90.f), glm::vec3(1.f, 0.f, 0.f));

	mspo_Objects.insert(std::pair<std::string, Game_Object*>("Red Arrow", new Arrow_3D(1000000, "Red Arrow", static_cast<Mesh_3D*>(po_Loader->get_Mesh("8")), quat_RedArrow, po_Loader->get_Texture("27"), po_Loader->get_Texture("7"))));
	mspo_Objects.insert(std::pair<std::string, Game_Object*>("Green Arrow", new Arrow_3D(1000001, "Green Arrow", static_cast<Mesh_3D*>(po_Loader->get_Mesh("8")) , quat_GreenArrow, po_Loader->get_Texture("28"), po_Loader->get_Texture("7"))));
	mspo_Objects.insert(std::pair<std::string, Game_Object*>("Blue Arrow", new Arrow_3D(1000002, "Blue Arrow", static_cast<Mesh_3D*>(po_Loader->get_Mesh("8")), quat_BlueArrow, po_Loader->get_Texture("29"), po_Loader->get_Texture("7"))));
}

void Scene_3D::add_GUI()
{
	mspo_Objects.insert(std::make_pair("Add_Object", (new Button(1000, "Add object", po_Loader->get_Font("0"), po_Loader->get_Mesh("0"), po_Loader->get_Texture("8"), glm::vec2(0, v2_WindowSize.y - 50.f), glm::vec2(200.f, 50.f), 0.f, 0.f, true, "Universal"))));
	mspo_Objects.insert(std::make_pair("Move", (new Button(1001, "Move", po_Loader->get_Font("0"), po_Loader->get_Mesh("0"), po_Loader->get_Texture("8"), glm::vec2(0, 0), glm::vec2(200.f, 50.f), 0.f, 0.f, true, "Universal"))));
	mspo_Objects.insert(std::make_pair("Rotate", (new Button(1002, "Rotate", po_Loader->get_Font("0"), po_Loader->get_Mesh("0"), po_Loader->get_Texture("8"), glm::vec2(200, 0.f), glm::vec2(200.f, 50.f), 0.f, 0.f, true, "Universal"))));
	mspo_Objects.insert(std::make_pair("Scale", (new Button(1003, "Scale", po_Loader->get_Font("0"), po_Loader->get_Mesh("0"), po_Loader->get_Texture("8"), glm::vec2(400, 0.f), glm::vec2(200.f, 50.f), 0.f, 0.f, true, "Universal"))));
	mspo_Objects.insert(std::make_pair("Select", (new Button(1004, "Select", po_Loader->get_Font("0"), po_Loader->get_Mesh("0"), po_Loader->get_Texture("8"), glm::vec2(600, 0.f), glm::vec2(200.f, 50.f), 0.f, 0.f, true, "Universal"))));

	mspo_Objects.insert(std::make_pair("Add_ObjectText", (new Text(1005, "Object Name:", glm::vec2(0.f, 600.f), 0.f, po_Loader->get_Font("0"), 0.f, false, "Hidden_Add"))));
	mspo_Objects.insert(std::make_pair("Add_ObjectTextbox", (new Textbox(1006, po_Loader->get_Font("0"), po_Loader->get_Mesh("0"), po_Loader->get_Texture("8"), glm::vec2(130, 600.f), glm::vec2(300.f, 20.f), 0.f, 0.f, false, "Hidden_Add"))));
	mspo_Objects.insert(std::make_pair("Add_PrefabText", (new Text(1007, "Prefab Name:", glm::vec2(0.f, 630.f), 0.f, po_Loader->get_Font("0"), 0.f, false, "Hidden_Add"))));
	mspo_Objects.insert(std::make_pair("Add_PrefabTextbox", (new Textbox(1008, po_Loader->get_Font("0"), po_Loader->get_Mesh("0"), po_Loader->get_Texture("8"), glm::vec2(130, 630.f), glm::vec2(300.f, 20.f), 0.f, 0.f, false, "Hidden_Add"))));
	mspo_Objects.insert(std::make_pair("Add_OriginText", (new Text(1009, "Origin:", glm::vec2(0.f, 660.f), 0.f, po_Loader->get_Font("0"), 0.f, false, "Hidden_Add"))));
	mspo_Objects.insert(std::make_pair("Add_OriginTextbox", (new Textbox(1010, po_Loader->get_Font("0"), po_Loader->get_Mesh("0"), po_Loader->get_Texture("8"), glm::vec2(130, 660.f), glm::vec2(300.f, 20.f), 0.f, 0.f, false, "Hidden_Add"))));
	mspo_Objects.insert(std::make_pair("Add_PositionText", (new Text(1011, "Position:", glm::vec2(0.f, 690.f), 0.f, po_Loader->get_Font("0"), 0.f, false, "Hidden_Add"))));
	mspo_Objects.insert(std::make_pair("Add_PositionTextbox", (new Textbox(1012, po_Loader->get_Font("0"), po_Loader->get_Mesh("0"), po_Loader->get_Texture("8"), glm::vec2(130, 690.f), glm::vec2(300.f, 20.f), 0.f, 0.f, false, "Hidden_Add"))));
	mspo_Objects.insert(std::make_pair("Add_ScaleText", (new Text(1013, "Scale:", glm::vec2(0.f, 720.f), 0.f, po_Loader->get_Font("0"), 0.f, false, "Hidden_Add"))));
	mspo_Objects.insert(std::make_pair("Add_ScaleTextbox", (new Textbox(1014, po_Loader->get_Font("0"), po_Loader->get_Mesh("0"), po_Loader->get_Texture("8"), glm::vec2(130, 720.f), glm::vec2(300.f, 20.f), 0.f, 0.f, false, "Hidden_Add"))));

	mspo_Objects.insert(std::make_pair("Show_ObjectText", (new Text(1015, "Object Name:", glm::vec2(0.f, 600.f), 0.f, po_Loader->get_Font("0"), 0.f, false, "Hidden_Show"))));
	mspo_Objects.insert(std::make_pair("Show_ObjectTextbox", (new Textbox(1016, po_Loader->get_Font("0"), po_Loader->get_Mesh("0"), po_Loader->get_Texture("8"), glm::vec2(130, 600.f), glm::vec2(300.f, 20.f), 0.f, 0.f, false, "Hidden_Show"))));
	mspo_Objects.insert(std::make_pair("Show_PrefabText", (new Text(1017, "Prefab Name:", glm::vec2(0.f, 630.f), 0.f, po_Loader->get_Font("0"), 0.f, false, "Hidden_Show"))));
	mspo_Objects.insert(std::make_pair("Show_PrefabTextbox", (new Textbox(1018, po_Loader->get_Font("0"), po_Loader->get_Mesh("0"), po_Loader->get_Texture("8"), glm::vec2(130, 630.f), glm::vec2(300.f, 20.f), 0.f, 0.f, false, "Hidden_Show"))));
	mspo_Objects.insert(std::make_pair("Show_OriginText", (new Text(1019, "Origin:", glm::vec2(0.f, 660.f), 0.f, po_Loader->get_Font("0"), 0.f, false, "Hidden_Show"))));
	mspo_Objects.insert(std::make_pair("Show_OriginTextbox", (new Textbox(1020, po_Loader->get_Font("0"), po_Loader->get_Mesh("0"), po_Loader->get_Texture("8"), glm::vec2(130, 660.f), glm::vec2(300.f, 20.f), 0.f, 0.f, false, "Hidden_Show"))));
	mspo_Objects.insert(std::make_pair("Show_PositionText", (new Text(1021, "Position:", glm::vec2(0.f, 690.f), 0.f, po_Loader->get_Font("0"), 0.f, false, "Hidden_Show"))));
	mspo_Objects.insert(std::make_pair("Show_PositionTextbox", (new Textbox(1022, po_Loader->get_Font("0"), po_Loader->get_Mesh("0"), po_Loader->get_Texture("8"), glm::vec2(130, 690.f), glm::vec2(300.f, 20.f), 0.f, 0.f, false, "Hidden_Show"))));
	mspo_Objects.insert(std::make_pair("Show_ScaleText", (new Text(1023, "Scale:", glm::vec2(0.f, 720.f), 0.f, po_Loader->get_Font("0"), 0.f, false, "Hidden_Show"))));
	mspo_Objects.insert(std::make_pair("Show_ScaleTextbox", (new Textbox(1024, po_Loader->get_Font("0"), po_Loader->get_Mesh("0"), po_Loader->get_Texture("8"), glm::vec2(130, 720.f), glm::vec2(300.f, 20.f), 0.f, 0.f, false, "Hidden_Show"))));

}

void Scene_3D::render_ColourScene()
{
	glClearColor(1.f, 1.f, 1.f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	glUseProgram(po_Loader->get_Shader("3")->get_Program());
	camera_3D->update_Shader(po_Loader->get_Shader("3"));

	for (auto const& pair : mspo_Objects)
	{
		if (pair.second->get_Tag() != "GUI")
		{
			int r = (pair.second->get_ObjectID() & 0x000000FF) >> 0;
			int g = (pair.second->get_ObjectID() & 0x0000FF00) >> 8;
			int b = (pair.second->get_ObjectID() & 0x00FF0000) >> 16;

			GLuint pickingColourID = glGetUniformLocation(po_Loader->get_Shader("3")->get_Program(), "pickColour");
			glUniform4f(pickingColourID, r / 255.0f, g / 255.0f, b / 255.0f, 1.0f);

			pair.second->render(po_Loader->get_Shader("3"));
		}
	}

	glClear(GL_DEPTH_BUFFER_BIT);
	for (auto const& pair : mspo_Objects)
	{
		if (pair.second->get_Tag() == "Arrow")
		{
			int r = (pair.second->get_ObjectID() & 0x000000FF) >> 0;
			int g = (pair.second->get_ObjectID() & 0x0000FF00) >> 8;
			int b = (pair.second->get_ObjectID() & 0x00FF0000) >> 16;

			GLuint pickingColourID = glGetUniformLocation(po_Loader->get_Shader("3")->get_Program(), "pickColour");
			glUniform4f(pickingColourID, r / 255.0f, g / 255.0f, b / 255.0f, 1.0f);

			pair.second->render(po_Loader->get_Shader("3"));
		}
	}

	glClear(GL_DEPTH_BUFFER_BIT);
	glUseProgram(po_Loader->get_Shader("4")->get_Program());
	camera_2D->update_Shader(po_Loader->get_Shader("4"));

	for (auto const& pair : mspo_Objects)
	{
		if (pair.second->get_Tag() == "GUI")
		{
			int r = (pair.second->get_ObjectID() & 0x000000FF) >> 0;
			int g = (pair.second->get_ObjectID() & 0x0000FF00) >> 8;
			int b = (pair.second->get_ObjectID() & 0x00FF0000) >> 16;

			GLuint pickingColourID = glGetUniformLocation(po_Loader->get_Shader("4")->get_Program(), "pickColour");
			glUniform4f(pickingColourID, r / 255.0f, g / 255.0f, b / 255.0f, 1.0f);

			pair.second->render(po_Loader->get_Shader("4"));
		}
	}

	glFlush();
	glFinish();
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	unsigned char data[4];
	glReadPixels((v2_WindowSize.x / 2.f) + (v2_MousePos.x - (v2_WindowSize.x / 2.f)), (v2_WindowSize.y / 2.f) - (v2_MousePos.y - (v2_WindowSize.y / 2.f)), 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, data);

	// Convert the color back to an integer ID
	pickedID =
		data[0] +
		data[1] * 256 +
		data[2] * 256 * 256;

	if (pickedID == 0x00ffffff) { // Full white, must be the background !
		std::cout << "background" << "\n";
	}
	else {
		std::cout << "Object with ID:" << pickedID << "\n";
	}
}

std::string Scene_3D::to3DVectorString(glm::vec3 pc_Vector3D_In)
{
	std::string s_Vector3D = "(" + std::to_string(pc_Vector3D_In.x) + ", " + std::to_string(pc_Vector3D_In.y) + ", " + std::to_string(pc_Vector3D_In.z) + ")";

	return s_Vector3D;
}

void Scene_3D::process_3DClick(float f_Delta_In, glm::vec2 v2_MousePos_In)
{
	if (b_Conditions[Conditions::Arrow_Moving]&& !b_Conditions[Conditions::Stop_Arrow])
	{
		switch (pickedID)
		{
			//Red Arrow moving
		case 1000000:
			if (picked_Object->get_Parent() != nullptr)
			{
				auto parent = static_cast<GameObject_3D*>(picked_Object->get_Parent());
				parent->set_Position(glm::vec3(parent->get_Position().x + camera_3D->get_PitchYaw(f_Delta_In, v2_MousePos_In, v2_WindowSize).x * camera_3D->get_CameraSide(), parent->get_Position().y, parent->get_Position().z));
				static_cast<GameObject_3D*>(mspo_Objects.find("Red Arrow")->second)->set_Position(glm::vec3(parent->get_Position()));
				static_cast<GameObject_3D*>(mspo_Objects.find("Green Arrow")->second)->set_Position(glm::vec3(parent->get_Position()));
				static_cast<GameObject_3D*>(mspo_Objects.find("Blue Arrow")->second)->set_Position(glm::vec3(parent->get_Position()));
			}
			else if (picked_Object->get_Children().empty())
			{
				picked_Object->set_Position(glm::vec3(picked_Object->get_Position().x + camera_3D->get_PitchYaw(f_Delta_In, v2_MousePos_In, v2_WindowSize).x * camera_3D->get_CameraSide(), picked_Object->get_Position().y, picked_Object->get_Position().z));
				static_cast<GameObject_3D*>(mspo_Objects.find("Red Arrow")->second)->set_Position(glm::vec3(picked_Object->get_Position()));
				static_cast<GameObject_3D*>(mspo_Objects.find("Green Arrow")->second)->set_Position(glm::vec3(picked_Object->get_Position()));
				static_cast<GameObject_3D*>(mspo_Objects.find("Blue Arrow")->second)->set_Position(glm::vec3(picked_Object->get_Position()));
			}
			break;

			//Green arrow moving
		case 1000001:
			if (picked_Object->get_Parent() != nullptr)
			{
				auto parent = static_cast<GameObject_3D*>(picked_Object->get_Parent());
				parent->set_Position(glm::vec3(parent->get_Position().x, parent->get_Position().y - camera_3D->get_PitchYaw(f_Delta_In, v2_MousePos_In, v2_WindowSize).y, parent->get_Position().z));
				static_cast<GameObject_3D*>(mspo_Objects.find("Red Arrow")->second)->set_Position(glm::vec3(parent->get_Position()));
				static_cast<GameObject_3D*>(mspo_Objects.find("Green Arrow")->second)->set_Position(glm::vec3(parent->get_Position()));
				static_cast<GameObject_3D*>(mspo_Objects.find("Blue Arrow")->second)->set_Position(glm::vec3(parent->get_Position()));
			}
			else if (picked_Object->get_Children().empty())
			{
				picked_Object->set_Position(glm::vec3(picked_Object->get_Position().x, picked_Object->get_Position().y - camera_3D->get_PitchYaw(f_Delta_In, v2_MousePos_In, v2_WindowSize).y, picked_Object->get_Position().z));
				static_cast<GameObject_3D*>(mspo_Objects.find("Red Arrow")->second)->set_Position(glm::vec3(picked_Object->get_Position()));
				static_cast<GameObject_3D*>(mspo_Objects.find("Green Arrow")->second)->set_Position(glm::vec3(picked_Object->get_Position()));
				static_cast<GameObject_3D*>(mspo_Objects.find("Blue Arrow")->second)->set_Position(glm::vec3(picked_Object->get_Position()));
			}
			break;

			//Blue arrow moving
		case 1000002:
			if (picked_Object->get_Parent() != nullptr)
			{
				auto parent = static_cast<GameObject_3D*>(picked_Object->get_Parent());
				parent->set_Position(glm::vec3(parent->get_Position().x, parent->get_Position().y, parent->get_Position().z - camera_3D->get_PitchYaw(f_Delta_In, v2_MousePos_In, v2_WindowSize).x));
				static_cast<GameObject_3D*>(mspo_Objects.find("Red Arrow")->second)->set_Position(glm::vec3(parent->get_Position()));
				static_cast<GameObject_3D*>(mspo_Objects.find("Green Arrow")->second)->set_Position(glm::vec3(parent->get_Position()));
				static_cast<GameObject_3D*>(mspo_Objects.find("Blue Arrow")->second)->set_Position(glm::vec3(parent->get_Position()));
			}
			else if (picked_Object->get_Children().empty())
			{
				picked_Object->set_Position(glm::vec3(picked_Object->get_Position().x, picked_Object->get_Position().y, picked_Object->get_Position().z - camera_3D->get_PitchYaw(f_Delta_In, v2_MousePos_In, v2_WindowSize).x));
				static_cast<GameObject_3D*>(mspo_Objects.find("Red Arrow")->second)->set_Position(glm::vec3(picked_Object->get_Position()));
				static_cast<GameObject_3D*>(mspo_Objects.find("Green Arrow")->second)->set_Position(glm::vec3(picked_Object->get_Position()));
				static_cast<GameObject_3D*>(mspo_Objects.find("Blue Arrow")->second)->set_Position(glm::vec3(picked_Object->get_Position()));
			}
			break;
		}
	}
	else if (b_Conditions[Conditions::Arrow_Scaling] && !b_Conditions[Conditions::Stop_Arrow])
	{
		switch (pickedID)
		{
			//Red Arrow moving
		case 1000000:
			if (picked_Object->get_Parent() != nullptr)
			{
				auto parent = static_cast<GameObject_3D*>(picked_Object->get_Parent());
				parent->set_Scale(glm::vec3(parent->get_Scale().x + camera_3D->get_PitchYaw(f_Delta_In, v2_MousePos_In, v2_WindowSize).x, parent->get_Scale().y, parent->get_Scale().z));
			}
			else if (picked_Object->get_Children().empty())
			{
				picked_Object->set_Scale(glm::vec3(picked_Object->get_Scale().x + camera_3D->get_PitchYaw(f_Delta_In, v2_MousePos_In, v2_WindowSize).x, picked_Object->get_Scale().y, picked_Object->get_Scale().z));
			}
			break;

			//Green arrow moving
		case 1000001:
			if (picked_Object->get_Parent() != nullptr)
			{
				auto parent = static_cast<GameObject_3D*>(picked_Object->get_Parent());
				parent->set_Scale(glm::vec3(parent->get_Scale().x, parent->get_Scale().y - camera_3D->get_PitchYaw(f_Delta_In, v2_MousePos_In, v2_WindowSize).y, parent->get_Scale().z));
			}
			else if (picked_Object->get_Children().empty())
			{
				picked_Object->set_Scale(glm::vec3(picked_Object->get_Scale().x, picked_Object->get_Scale().y - camera_3D->get_PitchYaw(f_Delta_In, v2_MousePos_In, v2_WindowSize).y, picked_Object->get_Scale().z));
			}
			break;

			//Blue arrow moving
		case 1000002:
			if (picked_Object->get_Parent() != nullptr)
			{
				auto parent = static_cast<GameObject_3D*>(picked_Object->get_Parent());
				parent->set_Scale(glm::vec3(parent->get_Scale().x, parent->get_Scale().y, parent->get_Scale().z + camera_3D->get_PitchYaw(f_Delta_In, v2_MousePos_In, v2_WindowSize).x));
			}
			else if (picked_Object->get_Children().empty())
			{
				picked_Object->set_Scale(glm::vec3(picked_Object->get_Scale().x, picked_Object->get_Scale().y, picked_Object->get_Scale().z + camera_3D->get_PitchYaw(f_Delta_In, v2_MousePos_In, v2_WindowSize).x));
			}
			break;
		}
	}
	else if (b_Conditions[Conditions::Arrow_Rotation] && !b_Conditions[Conditions::Stop_Arrow])
	{
		switch (pickedID)
		{
			//Red Arrow moving
		case 1000000:

			if (picked_Object->get_Parent() != nullptr)
			{
				auto parent = static_cast<GameObject_3D*>(picked_Object->get_Parent());

				glm::quat other_Quat = glm::normalize(glm::angleAxis(glm::radians(camera_3D->get_PitchYaw(f_Delta_In, v2_MousePos_In, v2_WindowSize).x) * camera_3D->get_CameraSide(), glm::vec3(0.f, 0.f, -1.f)));
				parent->set_Rotation(other_Quat);
			}
			else if (picked_Object->get_Children().empty())
			{
				glm::quat other_Quat = glm::normalize(glm::angleAxis(glm::radians(camera_3D->get_PitchYaw(f_Delta_In, v2_MousePos_In, v2_WindowSize).x) * camera_3D->get_CameraSide(), glm::vec3(0.f, 0.f, -1.f)));
				picked_Object->set_Rotation(other_Quat);
			}
			break;

			//Green arrow moving
		case 1000001:
			if (picked_Object->get_Parent() != nullptr)
			{
				auto parent = static_cast<GameObject_3D*>(picked_Object->get_Parent());
				glm::quat other_Quat = glm::normalize(glm::angleAxis(glm::radians(camera_3D->get_PitchYaw(f_Delta_In, v2_MousePos_In, v2_WindowSize).x) * camera_3D->get_CameraSide(), glm::vec3(0.f, -1.f, 0.f)));
				parent->set_Rotation(other_Quat);
			}
			else if (picked_Object->get_Children().empty())
			{
				glm::quat other_Quat = glm::normalize(glm::angleAxis(glm::radians(camera_3D->get_PitchYaw(f_Delta_In, v2_MousePos_In, v2_WindowSize).x) * camera_3D->get_CameraSide(), glm::vec3(0.f, -1.f, 0.f)));
				picked_Object->set_Rotation(other_Quat);
			}
			break;

			//Blue arrow moving
		case 1000002:
			if (picked_Object->get_Parent() != nullptr)
			{
				auto parent = static_cast<GameObject_3D*>(picked_Object->get_Parent());
				glm::quat other_Quat = glm::normalize(glm::angleAxis(glm::radians(camera_3D->get_PitchYaw(f_Delta_In, v2_MousePos_In, v2_WindowSize).x), glm::vec3(-1.f, 0.f, 0.f)));
				parent->set_Rotation(other_Quat);

			}
			else if (picked_Object->get_Children().empty())
			{
				glm::quat other_Quat = glm::normalize(glm::angleAxis(glm::radians(camera_3D->get_PitchYaw(f_Delta_In, v2_MousePos_In, v2_WindowSize).x), glm::vec3(-1.f, 0.f, 0.f)));
				picked_Object->set_Rotation(other_Quat);
			}
			break;
		}
	}
	else
	{
		pickedID = -1;
	}
}

void Scene_3D::process_2DClick(int i_ID_In)
{
	switch (i_ID_In)
	{
	case 1000: // Add object button
		for (auto const& pair : mspo_Objects)
		{
			if (pair.second->get_Tag() == "GUI" && pair.second->get_ObjectType() == "Hidden_Add") pair.second->set_RenderStatus(true);
			if (pair.second->get_Tag() == "GUI" && pair.second->get_ObjectType() == "Hidden_Show") pair.second->set_RenderStatus(false);
		}
		
		break;
	case 1001: // Move button
		b_Conditions[Conditions::Arrow_Moving] = true;
		b_Conditions[Conditions::Arrow_Scaling] = false;
		b_Conditions[Conditions::Arrow_Rotation] = false;
		b_Conditions[Conditions::Selection] = false;

		for (auto const& pair : mspo_Objects)
		{
			if (pair.second->get_Tag() == "GUI" && pair.second->get_ObjectType() == "Hidden_Add") pair.second->set_RenderStatus(false);
			if (pair.second->get_Tag() == "GUI" && pair.second->get_ObjectType() == "Hidden_Show") pair.second->set_RenderStatus(false);
		}
		
		break;
	
	case 1002: //Rotate button
			b_Conditions[Conditions::Arrow_Moving] = false;
			b_Conditions[Conditions::Arrow_Scaling] = false;
			b_Conditions[Conditions::Arrow_Rotation] = true;
			b_Conditions[Conditions::Selection] = false;

			for (auto const& pair : mspo_Objects)
			{
				if (pair.second->get_Tag() == "GUI" && pair.second->get_ObjectType() == "Hidden_Add") pair.second->set_RenderStatus(false);
				if (pair.second->get_Tag() == "GUI" && pair.second->get_ObjectType() == "Hidden_Show") pair.second->set_RenderStatus(false);
			}
			
			break;
	
	case 1003: // Scale button
		b_Conditions[Conditions::Arrow_Moving] = false;
		b_Conditions[Conditions::Arrow_Scaling] = true;
		b_Conditions[Conditions::Arrow_Rotation] = false;
		b_Conditions[Conditions::Selection] = false;

		for (auto const& pair : mspo_Objects)
		{
			if (pair.second->get_Tag() == "GUI" && pair.second->get_ObjectType() == "Hidden_Add") pair.second->set_RenderStatus(false);
			if (pair.second->get_Tag() == "GUI" && pair.second->get_ObjectType() == "Hidden_Show") pair.second->set_RenderStatus(false);
		}
		break;
	
	case 1004: // Selection button
		b_Conditions[Conditions::Arrow_Moving] = false;
		b_Conditions[Conditions::Arrow_Scaling] = false;
		b_Conditions[Conditions::Arrow_Rotation] = false;
		b_Conditions[Conditions::Selection] = true;

		for (auto const& pair : mspo_Objects)
		{
			if (pair.second->get_Tag() == "GUI" && pair.second->get_ObjectType() == "Hidden_Add") pair.second->set_RenderStatus(false);
			if (pair.second->get_Tag() == "GUI" && pair.second->get_ObjectType() == "Hidden_Show") pair.second->set_RenderStatus(true);
		}
		break;

	case 1006: // Textbox add name!
		b_Conditions[Conditions::ListenToKeyboard] = true;
			break;

	default:
		break;
	}
}

//Initialize everything once
void Scene_3D::init()
{
	//Initialize
	lock_mouse(true);
	b_Conditions[0] = false;

	camera_3D = new Camera_3D(45.f, v2_WindowSize.x / v2_WindowSize.y, 0.1f, 1000.f);
	camera_3D->set_CameraPos(glm::vec3(0.f, -20.f, 0.f));
	camera_2D = new Camera_2D(0, v2_WindowSize.x, v2_WindowSize.y, 0);
	//Load the scene
	po_PrefabLoader = new PrefabLoader("assets/Prefabs.xml", po_Loader);
	o_SceneLoader = new SceneLoader("assets/scenes/Robot_Scene.xml", po_Loader, po_PrefabLoader, mspo_Objects);
	save = new SceneSaver();
	f_Speed = 0.f;
	add_Arrows();
	add_GUI();
	b_Init = true;
}

//Do something with keyboard input
void Scene_3D::keyboard_Input(GLfloat f_Delta_In, GLboolean* pab_KeyArray_In, GLboolean* pab_LockedKeys_In, int i_KeyPress_In)
{
	if (b_Conditions[Conditions::ListenToKeyboard])
	{
		if (pab_KeyArray_In[GLFW_KEY_LEFT_SHIFT] && !pab_LockedKeys_In[GLFW_KEY_LEFT_SHIFT]) b_Conditions[Conditions::ShiftDetected] = true;
		
		if (pab_KeyArray_In[i_KeyPress_In] && !pab_LockedKeys_In[i_KeyPress_In] && i_KeyPress_In != GLFW_KEY_LEFT_SHIFT)
		{
			pab_LockedKeys_In[i_KeyPress_In] = true;
			std::cout << i_KeyPress_In << "\n";

			for (auto const& pair : mspo_Objects)
			{
				if (pair.second->get_ObjectID() == pickedID && pair.second->get_Tag() == "GUI") // We got it
				{
					auto text_Box = static_cast<Textbox*>(pair.second);

					if (i_KeyPress_In == GLFW_KEY_BACKSPACE && !text_Box->is_LineEmpty())
					{
						text_Box->erase_Letter();
					}
					else if (i_KeyPress_In == GLFW_KEY_BACKSPACE && text_Box->is_LineEmpty())
					{
						text_Box->delete_Line();
					}
					else if (i_KeyPress_In == GLFW_KEY_ENTER)
					{
						b_Conditions[Conditions::ListenToKeyboard] = false;
						pickedID = -1; // Stop pointing at this textbox
						break;
					}
					else
					{
						std::string s_Letter;

						s_Letter.push_back(i_KeyPress_In);
						if (!b_Conditions[Conditions::ShiftDetected]) std::transform(s_Letter.begin(), s_Letter.end(), s_Letter.begin(), ::tolower);
						s_Letter.push_back(i_KeyPress_In);
						text_Box->add_Letter(s_Letter);
					}
				}
			}

		}
		if (!pab_KeyArray_In[i_KeyPress_In]) pab_LockedKeys_In[i_KeyPress_In] = false;		
	}
	else
	{
		float f_MagicNumber = 0.7071f;

		if (pab_KeyArray_In[GLFW_KEY_R] && !pab_LockedKeys_In[GLFW_KEY_R])
		{
			reload_Scene();
			pab_LockedKeys_In[GLFW_KEY_R] = true;
		}
		if (!pab_KeyArray_In[GLFW_KEY_R]) pab_LockedKeys_In[GLFW_KEY_R] = false;

		if (pab_KeyArray_In[GLFW_KEY_LEFT_ALT])
		{
			b_Conditions[Conditions::Alt_Press] = true;
		}

		if (!pab_KeyArray_In[GLFW_KEY_LEFT_ALT])
		{
			b_Conditions[Conditions::Alt_Press] = false;
		}

		if (pab_KeyArray_In[GLFW_KEY_LEFT_CONTROL] && pab_KeyArray_In[GLFW_KEY_S] && !pab_LockedKeys_In[GLFW_KEY_S])
		{
			save->save(mspo_Objects, "assets/scenes/Robot_Scene.xml");
			pab_LockedKeys_In[GLFW_KEY_S] = true;
			std::cout << "Scene saved..." << "\n";
		}
		if (!pab_KeyArray_In[GLFW_KEY_S]) pab_LockedKeys_In[GLFW_KEY_S] = false;
	}
}

void Scene_3D::mouse_Input(GLboolean* pab_MouseArray_In, GLboolean* pab_LockedMouse_In)
{
	if (pab_MouseArray_In[GLFW_MOUSE_BUTTON_LEFT] && !pab_LockedMouse_In[GLFW_MOUSE_BUTTON_LEFT] && !b_Conditions[Conditions::Alt_Press])
	{
		b_Conditions[Conditions::LeftMouse_Button] = true;

		pab_LockedMouse_In[GLFW_MOUSE_BUTTON_LEFT] = true;
	}
	if (!pab_MouseArray_In[GLFW_MOUSE_BUTTON_LEFT]) pab_LockedMouse_In[GLFW_MOUSE_BUTTON_LEFT] = false;
	
	if (pab_MouseArray_In[GLFW_MOUSE_BUTTON_LEFT] && b_Conditions[Conditions::Alt_Press])
	{
		lock_mouse(true);
		b_Conditions[Conditions::Move_Mouse] = true;
	}

	if (pab_MouseArray_In[GLFW_MOUSE_BUTTON_LEFT] && pickedID == 1000000 ||
		pab_MouseArray_In[GLFW_MOUSE_BUTTON_LEFT] && pickedID == 1000001 ||
		pab_MouseArray_In[GLFW_MOUSE_BUTTON_LEFT] && pickedID == 1000002)
	{
		lock_mouse(true);
		b_Conditions[Conditions::Stop_Arrow] = false;
	}

	if (!pab_MouseArray_In[GLFW_MOUSE_BUTTON_LEFT] && pickedID == 1000000 ||
		!pab_MouseArray_In[GLFW_MOUSE_BUTTON_LEFT] && pickedID == 1000001 ||
		!pab_MouseArray_In[GLFW_MOUSE_BUTTON_LEFT] && pickedID == 1000002)
	{
		b_Conditions[Conditions::Stop_Arrow] = true;
	}

	if (pab_MouseArray_In[GLFW_MOUSE_BUTTON_RIGHT])
	{
		lock_mouse(true);
		b_Conditions[Conditions::RightMouse_Button] = true;
	}

	if (!pab_MouseArray_In[GLFW_MOUSE_BUTTON_RIGHT])
	{
		b_Conditions[Conditions::RightMouse_Button] = false;
	}

}

void Scene_3D::scroll_Input(glm::vec2 v2_Scroll_In)
{
	if (v2_Scroll_In.y > 0)
	{
		camera_3D->set_Speed(f_Speed);
		camera_3D->move_Forward();
	}
	else
	{
		camera_3D->set_Speed(f_Speed);
		camera_3D->move_Backward();
	}
}

void Scene_3D::reload_Scene()
{
	clean_Up();
	b_Init = false;
}

//Update the scene
void Scene_3D::update_Scene(GLfloat f_Delta_In, glm::vec2 v2_MousePos_In)
{
	v2_MousePos = v2_MousePos_In;
	////Initialize
	if (!b_Init) init();

	if (b_Init)
	{
		f_Speed = 2000 * f_Delta_In;
		
		for (auto const& pair : mspo_Objects)
		{
			if (pair.second->get_ObjectID() == pickedID)
			{
				if (pair.second->get_Tag() != "Arrow" && pair.second->get_Tag() != "GUI")
				{
					picked_Object = static_cast<GameObject_3D*>(pair.second);

					if (picked_Object->get_Parent() != nullptr)
					{
						auto parent = static_cast<GameObject_3D*>(picked_Object->get_Parent());
						static_cast<GameObject_3D*>(mspo_Objects.find("Red Arrow")->second)->set_Position(glm::vec3(parent->get_Position()));				
						static_cast<GameObject_3D*>(mspo_Objects.find("Green Arrow")->second)->set_Position(glm::vec3(parent->get_Position()));
						static_cast<GameObject_3D*>(mspo_Objects.find("Blue Arrow")->second)->set_Position(glm::vec3(parent->get_Position()));

						static_cast<GameObject_3D*>(mspo_Objects.find("Red Arrow")->second)->set_RenderStatus(true);
						static_cast<GameObject_3D*>(mspo_Objects.find("Green Arrow")->second)->set_RenderStatus(true);
						static_cast<GameObject_3D*>(mspo_Objects.find("Blue Arrow")->second)->set_RenderStatus(true);
					}
					else if (picked_Object->get_Children().empty())
					{
						static_cast<GameObject_3D*>(mspo_Objects.find("Red Arrow")->second)->set_Position(glm::vec3(picked_Object->get_Position()));			
						static_cast<GameObject_3D*>(mspo_Objects.find("Green Arrow")->second)->set_Position(glm::vec3(picked_Object->get_Position()));			
						static_cast<GameObject_3D*>(mspo_Objects.find("Blue Arrow")->second)->set_Position(glm::vec3(picked_Object->get_Position()));
					
						static_cast<GameObject_3D*>(mspo_Objects.find("Red Arrow")->second)->set_RenderStatus(true);
						static_cast<GameObject_3D*>(mspo_Objects.find("Green Arrow")->second)->set_RenderStatus(true);
						static_cast<GameObject_3D*>(mspo_Objects.find("Blue Arrow")->second)->set_RenderStatus(true);
					}
				}
				else if (pair.second->get_Tag() == "GUI")
				{
					process_2DClick(pickedID);
				}
				else
				{
					process_3DClick(f_Delta_In, v2_MousePos);

				}
			}

			pair.second->update();
		}
		if (b_Conditions[Conditions::RightMouse_Button]) camera_3D->move_MouseEditor(f_Delta_In, v2_MousePos_In, v2_WindowSize);

		camera_3D->move_Keyboard(f_Delta_In);
		if (b_Conditions[Conditions::Move_Mouse]) camera_3D->move_Mouse(f_Delta_In, v2_MousePos_In, v2_WindowSize);
		camera_3D->update();
		camera_3D->reset();
	}
}

//Render all scene objects
void Scene_3D::render()
{
	if (b_Init)
	{
		if (b_Conditions[Conditions::LeftMouse_Button])
		{
			render_ColourScene();
			if (b_Conditions[Conditions::Selection])
			{
				for (auto const& pair : mspo_Objects)
				{
					if (pair.second->get_Tag() == "GUI" &&  pair.second->get_ObjectType() == "Hidden_Show")
					{
						if (pair.first == "Show_PositionTextbox")
						{
							for (auto const find_obj : mspo_Objects)
							{
								if (find_obj.second->get_ObjectID() == pickedID && find_obj.second->get_Tag() != "GUI" && find_obj.second->get_Tag() != "Arrow")
								{
									auto object = static_cast<GameObject_3D*>(find_obj.second);

									if (object->get_Parent() != nullptr)
									{
										auto parent = static_cast<GameObject_3D*>(object->get_Parent());
										static_cast<Textbox*>(pair.second)->set_Text(to3DVectorString(parent->get_Position()));
									}
									else static_cast<Textbox*>(pair.second)->set_Text(to3DVectorString(object->get_Position()));

								}
							}
						}
						else if (pair.first == "Show_OriginTextbox")
						{
							for (auto const find_obj : mspo_Objects)
							{
								if (find_obj.second->get_ObjectID() == pickedID && find_obj.second->get_Tag() != "GUI" && find_obj.second->get_Tag() != "Arrow")
								{
									auto object = static_cast<GameObject_3D*>(find_obj.second);

									if (object->get_Parent() != nullptr)
									{
										auto parent = static_cast<GameObject_3D*>(object->get_Parent());
										static_cast<Textbox*>(pair.second)->set_Text(to3DVectorString(parent->get_Origin()));
									}
									else static_cast<Textbox*>(pair.second)->set_Text(to3DVectorString(object->get_Origin()));
								}
							}
						}
						else if (pair.first == "Show_ScaleTextbox")
						{
							for (auto const find_obj : mspo_Objects)
							{
								if (find_obj.second->get_ObjectID() == pickedID && find_obj.second->get_Tag() != "GUI" && find_obj.second->get_Tag() != "Arrow")
								{
									auto object = static_cast<GameObject_3D*>(find_obj.second);

									if (object->get_Parent() != nullptr)
									{
										auto parent = static_cast<GameObject_3D*>(object->get_Parent());
										static_cast<Textbox*>(pair.second)->set_Text(to3DVectorString(parent->get_Scale()));
									}
									else static_cast<Textbox*>(pair.second)->set_Text(to3DVectorString(object->get_Scale()));
								}
							}
						}
						else if (pair.first == "Show_ObjectTextbox")
						{
							for (auto const find_obj : mspo_Objects)
							{
								if (find_obj.second->get_ObjectID() == pickedID && find_obj.second->get_Tag() != "GUI" && find_obj.second->get_Tag() != "Arrow")
								{
									auto object = static_cast<GameObject_3D*>(find_obj.second);
									if (object->get_Parent() != nullptr)
									{
										auto parent = static_cast<GameObject_3D*>(object->get_Parent());
										static_cast<Textbox*>(pair.second)->set_Text(parent->get_Name());
									}
									else static_cast<Textbox*>(pair.second)->set_Text(object->get_Name());
								}
							}
						}
						else if (pair.first == "Show_PrefabTextbox")
						{
							for (auto const find_obj : mspo_Objects)
							{
								if (find_obj.second->get_ObjectID() == pickedID && find_obj.second->get_Tag() != "GUI" && find_obj.second->get_Tag() != "Arrow")
								{
									auto object = static_cast<GameObject_3D*>(find_obj.second);
									if (object->get_Parent() != nullptr)
									{
										auto parent = static_cast<GameObject_3D*>(object->get_Parent());
										static_cast<Textbox*>(pair.second)->set_Text(parent->get_PrefabName());
									}
									else static_cast<Textbox*>(pair.second)->set_Text(object->get_PrefabName());
								}
							}
						}
					}
				}
			}
		}

		glClearColor(0.1f, 0.1f, 0.1f, 0.1f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glEnable(GL_DEPTH_TEST);

		glUseProgram(po_Loader->get_Shader("0")->get_Program());
		camera_3D->update_Shader(po_Loader->get_Shader("0"));
		o_SceneLoader->set_LightAmount(po_Loader->get_Shader("0"));

		for (auto const& pair : mspo_Objects)
		{
			if (pair.second->get_Tag() == "Light")
			{
				static_cast<Light*>(pair.second)->update_Shader(po_Loader->get_Shader("0"));
				pair.second->render(po_Loader->get_Shader("0"));
			}
		}

		for (auto const& pair : mspo_Objects)
		{
			if (pair.second->get_Tag() == "Object" || pair.second->get_Tag() == "Object_NonSavable") pair.second->render(po_Loader->get_Shader("0"));
		}

		glClear(GL_DEPTH_BUFFER_BIT);
		glUseProgram(po_Loader->get_Shader("5")->get_Program());
		camera_3D->update_Shader(po_Loader->get_Shader("5"));
		for (auto const& pair : mspo_Objects) if (pair.second->get_Tag() == "Arrow") pair.second->render(po_Loader->get_Shader("5"));

		glClear(GL_DEPTH_BUFFER_BIT);
		glUseProgram(po_Loader->get_Shader("1")->get_Program());
		camera_2D->update_Shader(po_Loader->get_Shader("1"));

		for (auto const& pair : mspo_Objects)
		{
			if (pair.second->get_Tag() == "GUI")
			{
				pair.second->render(po_Loader->get_Shader("1"));	
			}
		}
	}

	lock_mouse(false);
	b_Conditions[Conditions::Move_Mouse] = false;
	b_Conditions[Conditions::LeftMouse_Button] = false;
	b_Conditions[Conditions::ShiftDetected] = false;
}

void Scene_3D::clean_Up()
{
	if (!mspo_Objects.empty())
	{
		//For each object
		for (auto const& pair : mspo_Objects)
		{
			pair.second->clean_Up();
			delete pair.second;
		}
		mspo_Objects.clear();
	}

	pickedID = -1;
	delete o_SceneLoader;
	delete camera_3D;
	delete save;
}