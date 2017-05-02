#include <Engine/Loaders/SceneLoader.h>
#include<TinyXML2\tinyxml2.h>
#include <Engine/Loaders/Loader.h>
#include <Engine\Game_Objects\GameObject_3D.h>
#include <Engine\Component\Transform_3D.h>
#include <Engine\Component\RenderComp_3D.h>
#include <Engine\Component\Respond_Movement.h>
#include <Engine\Component\BoxCollider_3D.h>
#include <Engine\Component\RigidBody.h>
#include <Engine\Lighting\Point_Light.h>
#include <Game/CharacterController/CharacterController.h>
#include <Engine\Component\Character.h>
#include <glad\glad.h>

#include <iostream>

SceneLoader::SceneLoader(const char* pc_FileName_In, Loader* po_Loader_In, std::map<std::string, Game_Object*>& mspo_GameObjects_In)
{
	po_SceneLoader = po_Loader_In;
	i_NumOfPointLight = 0;

	tinyxml2::XMLDocument object_File;
	object_File.LoadFile(pc_FileName_In);
	tinyxml2::XMLElement* body = object_File.FirstChildElement("objects");

	for (tinyxml2::XMLElement* it = body->FirstChildElement("new_Object3D"); it != nullptr; it = it->NextSiblingElement("new_Object3D"))
	{
		std::cout << "Adding new object to the scene..." << "\n";

		//Extract data
		std::vector<std::string> vs_Children;
		std::string i_MeshID;
		std::string i_DiffuseID;
		std::string i_SpecularID;
		glm::vec2 v2_Tiling;
		std::string s_Components;
		int i_InitMode;
		float f_Shiny;
		glm::vec3 v3_Origin; 
		glm::vec3 v3_Position;
		glm::quat quat_OrientationX;
		glm::quat quat_OrientationY;
		glm::quat quat_OrientationZ;
		glm::vec3 v3_Scale;
		std::string s_Children;
		std::string s_Tag;

		std::string s_ObjectName = it->Attribute("name");
		std::string s_Container = it->Attribute("container");

		if (s_Container == "Yes") // This object has children
		{
				//Add variables
				s_Components = it->Attribute("component");
				v3_Origin = to3DVector(it->Attribute("origin"));
				v3_Position = to3DVector(it->Attribute("position"));
				quat_OrientationX = toQuat(it->Attribute("orientationX"));
				quat_OrientationY = toQuat(it->Attribute("orientationY"));
				quat_OrientationZ = toQuat(it->Attribute("orientationZ"));
				v3_Scale = to3DVector(it->Attribute("scale"));
				s_Children = it->Attribute("children");
				s_Tag = it->Attribute("tag");
				
				//Typical process of adding new 3D object
				mspo_GameObjects_In.insert(std::pair<std::string, Game_Object*>(s_ObjectName, new GameObject_3D()));
				auto object = static_cast<GameObject_3D*>(mspo_GameObjects_In.find(s_ObjectName)->second);
				object->set_Name(s_ObjectName);
				object->add_Component("Transform_3D", new Transform_3D());
				if (s_Components != "") add_Components(object, s_Components);
				object->set_RenderStatus(false);
				object->set_Position(v3_Position);
				object->set_Origin(v3_Origin);
				object->set_Rotation(quat_OrientationZ * quat_OrientationY * quat_OrientationX);
				object->set_Scale(v3_Scale);
				object->set_Tag(s_Tag);
				
				if (s_Children != "") // Make sure that children are really there
				{
					//Add child to the object
					add_Children(vs_Children, s_Children);
					for (auto it = vs_Children.begin(); it != vs_Children.end(); ++it)
					{
						auto found_Child = static_cast<GameObject_3D*>(mspo_GameObjects_In.find(*it)->second);
						object->add_Child(found_Child);
					}
				}
		}
		else // It doesn't
		{
			//Add variables
			s_Components = it->Attribute("component");
			i_MeshID = it->Attribute("mesh_ID");
			i_DiffuseID = it->Attribute("diffuse_ID");
			i_SpecularID = it->Attribute("specular_ID");
			v2_Tiling = to2DVector(it->Attribute("texture_Tiling"));
			s_Tag = it->Attribute("tag");
			i_InitMode = std::atoi(it->Attribute("init_Mode"));
			f_Shiny = std::strtof(it->Attribute("shininess"), nullptr);
			glm::vec3 origin = to3DVector(it->Attribute("origin"));
			glm::vec3 position = to3DVector(it->Attribute("position"));
			glm::quat orientationX = toQuat(it->Attribute("orientationX"));
			glm::quat orientationY = toQuat(it->Attribute("orientationY"));
			glm::quat orientationZ = toQuat(it->Attribute("orientationZ"));
			glm::vec3 scale = to3DVector(it->Attribute("scale"));

			//Typical process of adding new 3D object
			mspo_GameObjects_In.insert(std::pair<std::string, Game_Object*>(s_ObjectName, new GameObject_3D()));
			auto object = static_cast<GameObject_3D*>(mspo_GameObjects_In.find(s_ObjectName)->second);
			object->set_Name(s_ObjectName);
			object->add_Component("Mesh_3D", po_Loader_In->get_Mesh3D(i_MeshID));
			object->add_Component("Transform_3D", new Transform_3D());
			object->add_Component("RenderComp_3D", new RenderComp_3D());
			if (s_Components != "") add_Components(object, s_Components);
			object->set_Position(position);
			object->set_Origin(origin);
			object->set_Rotation(orientationZ * orientationY * orientationX);
			object->set_Scale(scale);
			object->add_Texture("Diffuse_Map", po_Loader_In->get_Texture(i_DiffuseID));
			object->add_Texture("Specular_Map", po_Loader_In->get_Texture(i_SpecularID));
			object->set_Tiles(v2_Tiling);
			object->set_Shininess(f_Shiny);
			object->set_Tag(s_Tag);
		}
	}

	//Find lights
	body = object_File.FirstChildElement("lights");

	for (tinyxml2::XMLElement* it = body->FirstChildElement("new_Light"); it != nullptr; it = it->NextSiblingElement("new_Light"))
	{
		std::cout << "Adding lights to the scene..." << "\n";

		//Add variables
		std::string s_Type;
		int i_LightID;
		glm::vec3 v3_Ambient;
		glm::vec3 v3_Diffuse;
		glm::vec3 v3_Specular;
		glm::vec3 v3_Direction;
		glm::vec3 v3_Position;
		float f_Constant;
		float f_Linear;
		float f_Quadratic;
		std::string s_Tag;

		s_Type = it->Attribute("type");
		i_LightID = std::atoi(it->Attribute("light_ID"));
		s_Tag = it->Attribute("tag");
		std::string s_Name = s_Type + "_" + std::to_string(i_LightID);

		if (s_Type == "Directional") // Later
		{
			//TO-DO
		}
		else if (s_Type == "Spotlight") // Later
		{
			//TO-DO
		}
		else if (s_Type == "Point_Light")
		{
			//Point light
			v3_Position = to3DVector(it->Attribute("position"));
			v3_Ambient = to3DVector(it->Attribute("ambient"));
			v3_Diffuse = to3DVector(it->Attribute("diffuse"));
			v3_Specular = to3DVector(it->Attribute("specular"));
			f_Constant = std::strtof(it->Attribute("constant"), nullptr);
			f_Linear = std::strtof(it->Attribute("linear"), nullptr);
			f_Quadratic = std::strtof(it->Attribute("quadratic"), nullptr);
			mspo_GameObjects_In.insert(std::pair<std::string, Game_Object*>(s_Name, new Point_Light(v3_Ambient, v3_Diffuse, v3_Specular, f_Constant, f_Linear, f_Quadratic, i_LightID)));
			i_NumOfPointLight++;

			auto point_Light = static_cast<Point_Light*>(mspo_GameObjects_In.find(s_Name)->second);
			point_Light->add_Component("Mesh_3D", po_Loader_In->get_Mesh3D("7"));
			point_Light->add_Component("Transform_3D", new Transform_3D());
			point_Light->add_Component("RenderComp_3D", new RenderComp_3D());
			point_Light->set_Position(v3_Position);
			point_Light->set_RenderStatus(false);
			point_Light->add_Texture("Diffuse_Map", po_Loader_In->get_Texture("7"));
			point_Light->add_Texture("Specular_Map", po_Loader_In->get_Texture("7"));
			point_Light->set_Tiles(glm::vec2(1.f, 1.f));
			point_Light->set_Shininess(1.f);
			point_Light->set_Tag(s_Tag);
		}
	}
}

void SceneLoader::identify_Component(GameObject_3D* po_GameObject_In, std::string& s_ToProcess_In)
{
	std::cout << "Component name: " << s_ToProcess_In << "\n";
	if (s_ToProcess_In == "Character_Controller") { po_GameObject_In->add_Component("Character_Controller", new CharacterController(po_GameObject_In)); }
	//else if (s_ToProcess_In == "Patrol_Path") po_GameObject_In->add_Component("Patrol_Path", );
	else if (s_ToProcess_In == "Respond_Movement") po_GameObject_In->add_Component("Respond_Movement", new Respond_Movement());
	else if (s_ToProcess_In == "BoxCollider_3D") po_GameObject_In->add_Component("BoxCollider_3D", new BoxCollider_3D());
	else if (s_ToProcess_In == "RigidBody") po_GameObject_In->add_Component("RigidBody", new RigidBody());
	else if (s_ToProcess_In == "Character") po_GameObject_In->add_Component("Character", new Character());
	else std::cout << "Unknown component..." << "\n"; // Else we can't find it

	s_ToProcess_In.clear();
}

glm::vec3 SceneLoader::to3DVector(const char* pc_Vector3D_In)
{
	std::string s_Result;
	int i_DataCounter = 0;
	int i_Length = std::strlen(pc_Vector3D_In);
	glm::vec3 v3_Vector;

	for (int i = 0; i < i_Length; i++)
	{
		switch (pc_Vector3D_In[i])
		{
		case 32: // Empty space
			//Ignore
			break;

		case 44: // Comma
			i_DataCounter++;

			switch (i_DataCounter)
				{
				case 1:
					v3_Vector.x = std::strtof(s_Result.c_str(), NULL);
					s_Result.clear();
					break;

				case 2:
					v3_Vector.y = std::strtof(s_Result.c_str(), NULL);
					s_Result.clear();
					break;
				}
				break;
			break;

		case 40: // This bracker "(" 
			//Ignore
			break;

		case 41: // This bracket ")"
			v3_Vector.z = std::strtof(s_Result.c_str(), NULL);
			break;

			//Process
		default:
			s_Result += pc_Vector3D_In[i];
		break;
		}
	}

	return glm::vec3(v3_Vector.x, v3_Vector.y, v3_Vector.z);
}

glm::vec2 SceneLoader::to2DVector(const char* pc_Vector2D_In)
{
	std::string s_Result;
	int i_DataCounter = 0;
	int i_Length = std::strlen(pc_Vector2D_In);
	glm::vec2 v2_Vector;

	for (int i = 0; i < i_Length; i++)
	{
		switch (pc_Vector2D_In[i])
		{
		case 32: // Empty space
				 //Ignore
			break;

		case 44: // Comma
			v2_Vector.x = std::strtof(s_Result.c_str(), nullptr);
			s_Result.clear();
			break;

		case 40: // This bracker "(" 
				 //Ignore
			break;

		case 41: // This bracket ")"
			v2_Vector.y = std::strtof(s_Result.c_str(), nullptr);
			break;

			//Process
		default:
			s_Result += pc_Vector2D_In[i];
			break;
		}
	}

	return glm::vec2(v2_Vector.x, v2_Vector.y);
}

glm::quat SceneLoader::toQuat(const char* pc_Quaternion_In)
{
	std::string s_Result;
	int i_DataCounter = 0;
	int i_Length = std::strlen(pc_Quaternion_In);
	float f_Angle;
	glm::vec3 v3_Vector;

	for (int i = 0; i < i_Length; i++)
	{
		switch (pc_Quaternion_In[i])
		{
			case 32: // Empty space
			//Ignore
			break;

			case 44: // Comma
				i_DataCounter++;

				switch (i_DataCounter)
				{
					case 1:
						f_Angle = std::strtof(s_Result.c_str(), nullptr);
						s_Result.clear();
					break;

					case 2:
						v3_Vector.x = std::strtof(s_Result.c_str(), nullptr);
						s_Result.clear();
					break;

					case 3:
						v3_Vector.y = std::strtof(s_Result.c_str(), nullptr);
						s_Result.clear();
					break;
				}
				break;

			case 40: // This bracket "("
			 //Ignore
			break;

			case 41: // This bracket ")"
				v3_Vector.z = std::strtof(s_Result.c_str(), nullptr);
			break;

				//Process
			default:
				s_Result = s_Result + pc_Quaternion_In[i];
			break;
		break;
		}	
	}

	glm::quat temp = glm::angleAxis(glm::radians(f_Angle), glm::vec3(v3_Vector.x, v3_Vector.y, v3_Vector.z));
	return temp;
}

void SceneLoader::add_Children(std::vector<std::string>& vs_Children_In, std::string s_ToProcess_In)
{
	std::string s_Result;
	int i_Length = s_ToProcess_In.length();
	bool b_IgnoreSpaces = false;

	for (int i = 0; i < i_Length; i++)
	{
		switch (s_ToProcess_In[i])
		{
			case 40: // This bracket "("
				 //Ignore
			break;

			case 41: // This bracket ")"
				vs_Children_In.push_back(s_Result);
				s_Result.clear();
				b_IgnoreSpaces = true;
			break;

			case 44:  // Comma
				vs_Children_In.push_back(s_Result);
				s_Result.clear();
				b_IgnoreSpaces = true;
			break;

			case '\n':
				break;

			case '\t':
				break;

			case 32:
				if (!b_IgnoreSpaces) s_Result = s_Result + s_ToProcess_In[i];
			break;

			//Process
			default:
				s_Result = s_Result + s_ToProcess_In[i];
				if (s_Result.length() > 1) b_IgnoreSpaces = false;

			break;
		}
	}
}

void SceneLoader::add_Components(GameObject_3D* po_GameObject_In, std::string s_ToProcess_In)
{
	std::string s_Result;
	int i_Length = s_ToProcess_In.length();

	for (int i = 0; i < i_Length; i++)
	{
		switch (s_ToProcess_In[i])
		{
		case 40: // This bracket "("
				 //Ignore
			break;

		case 41: // This bracket ")"
			identify_Component(po_GameObject_In, s_Result);
			break;

		case 44:  // Comma
			//Find the right component
			identify_Component(po_GameObject_In, s_Result);	
			break;

		case '\n':
			break;

		case '\t':
			break;

		case 32:
			break;

			//Process
		default:
			s_Result = s_Result + s_ToProcess_In[i];
			break;
		}
	}
}

void SceneLoader::set_LightAmount(Shader* p_Shader_In)
{
	//Send this amount of light to shader
	GLint lightLoc = glGetUniformLocation(p_Shader_In->get_Program(), "numOfLights");
	glUniform1i(lightLoc, i_NumOfPointLight);
}
