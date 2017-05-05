#include <Engine/Loaders/SceneLoader.h>
#include<TinyXML2\tinyxml2.h>
#include <Engine/Loaders/Loader.h>
#include <Engine\Game_Objects\GameObject_3D.h>
#include <Engine\Component\Transform_3D.h>
#include <Engine\Component\RenderComp_3D.h>
#include <Engine\Lighting\Point_Light.h>
#include <glad\glad.h>
#include <Engine\Loaders\PrefabLoader.h>
#include <Engine\Lighting\Light.h>

#include <iostream>

SceneLoader::SceneLoader(const char* pc_FileName_In, Loader* po_Loader_In, PrefabLoader* po_PrefLoader_In, std::map<std::string, Game_Object*>& mspo_GameObjects_In)
{
	po_SceneLoader = po_Loader_In;
	i_NumOfPointLight = 0;
	int i_Incrementor = 0;

	tinyxml2::XMLDocument object_File;
	object_File.LoadFile(pc_FileName_In);
	
	tinyxml2::XMLElement* body = object_File.FirstChildElement("objects");
	for (tinyxml2::XMLElement* it = body->FirstChildElement("new_Object3D"); it != nullptr; it = it->NextSiblingElement("new_Object3D"))
	{
		std::cout << "Adding new object to the scene..." << "\n";

		std::string s_ObjectName = it->Attribute("name");
		std::string s_Prefab = it->Attribute("prefab");
		glm::vec3 v3_Position = to3DVector(it->Attribute("position"));
		glm::vec3 v3_Scale = to3DVector(it->Attribute("scale"));
		glm::vec3 v3_Origin = to3DVector(it->Attribute("origin"));
		glm::quat v3_Orientation = toQuat(it->Attribute("orientation"));

		auto desired_Prefab = static_cast<GameObject_3D*>(po_PrefLoader_In->get_Prefab(s_Prefab));
		mspo_GameObjects_In.insert(std::pair<std::string, Game_Object*>(s_ObjectName, new GameObject_3D(*desired_Prefab)));
		auto desired_Object = static_cast<GameObject_3D*>(mspo_GameObjects_In.find(s_ObjectName)->second);

		if (!desired_Prefab->get_ChildrenNames().empty())
		{
			for (int i = 0; i < desired_Prefab->get_ChildrenNames().size(); i++)
			{
				std::string s_ChildName = s_ObjectName + " Child " + std::to_string(i_Incrementor + i);

				auto prefab_Child = static_cast<GameObject_3D*>(po_PrefLoader_In->get_Prefab(desired_Prefab->get_ChildrenNames()[i]));
				mspo_GameObjects_In.insert(std::pair<std::string, GameObject_3D*>(s_ChildName, new GameObject_3D(*prefab_Child)));
				auto found_Child = mspo_GameObjects_In.find(s_ChildName)->second;
				found_Child->set_Name(s_ChildName);
				found_Child->set_ObjectID(i_Incrementor);
				found_Child->set_Tag("Object_NonSavable");
				desired_Object->add_Child(found_Child);
				desired_Object->add_ChildName(desired_Prefab->get_ChildrenNames()[i]);
			}
		}

		desired_Object->set_Name(s_ObjectName);
		desired_Object->set_Position(v3_Position);
		desired_Object->set_Scale(v3_Scale);
		desired_Object->set_Rotation(v3_Orientation);
		desired_Object->set_Origin(v3_Origin);
		desired_Object->set_ObjectID(i_Incrementor);
		i_Incrementor++;
	}

	body = object_File.FirstChildElement("lights");

	i_NumOfPointLight = 0;
	for (tinyxml2::XMLElement* it = body->FirstChildElement("new_Light"); it != nullptr; it = it->NextSiblingElement("new_Light"))
	{
		std::cout << "Adding new light to the scene..." << "\n";

		std::string s_ObjectName = it->Attribute("name");
		std::string s_Prefab = it->Attribute("prefab");
		glm::vec3 v3_Position = to3DVector(it->Attribute("position"));
		std::string s_Type = it->Attribute("type");

		if (s_Type == "Point_Light")
		{
			auto desired_Prefab = dynamic_cast<Point_Light*>(po_PrefLoader_In->get_Prefab(s_Prefab));
			mspo_GameObjects_In.insert(std::pair<std::string, Game_Object*>(s_ObjectName, new Point_Light(*desired_Prefab)));
			auto desired_Object = dynamic_cast<Point_Light*>(mspo_GameObjects_In.find(s_ObjectName)->second);

			desired_Object->set_Name(s_ObjectName);
			desired_Object->set_Position(v3_Position);
			desired_Object->set_ObjectID(i_Incrementor);
			desired_Object->set_ID(i_NumOfPointLight);
			i_NumOfPointLight++;
			i_Incrementor++;
		}
		
	}

	////Find lights
	//body = object_File.FirstChildElement("lights");

	//for (tinyxml2::XMLElement* it = body->FirstChildElement("new_Light"); it != nullptr; it = it->NextSiblingElement("new_Light"))
	//{
	//	std::cout << "Adding lights to the scene..." << "\n";

	//	//Add variables
	//	std::string s_Type;
	//	int i_LightID;
	//	glm::vec3 v3_Ambient;
	//	glm::vec3 v3_Diffuse;
	//	glm::vec3 v3_Specular;
	//	glm::vec3 v3_Direction;
	//	glm::vec3 v3_Position;
	//	float f_Constant;
	//	float f_Linear;
	//	float f_Quadratic;
	//	std::string s_Tag;

	//	s_Type = it->Attribute("type");
	//	i_LightID = std::atoi(it->Attribute("light_ID"));
	//	s_Tag = it->Attribute("tag");
	//	std::string s_Name = s_Type + "_" + std::to_string(i_LightID);

	//	if (s_Type == "Directional") // Later
	//	{
	//		//TO-DO
	//	}
	//	else if (s_Type == "Spotlight") // Later
	//	{
	//		//TO-DO
	//	}
	//	else if (s_Type == "Point_Light")
	//	{
	//		//Point light
	//		v3_Position = to3DVector(it->Attribute("position"));
	//		v3_Ambient = to3DVector(it->Attribute("ambient"));
	//		v3_Diffuse = to3DVector(it->Attribute("diffuse"));
	//		v3_Specular = to3DVector(it->Attribute("specular"));
	//		f_Constant = std::strtof(it->Attribute("constant"), nullptr);
	//		f_Linear = std::strtof(it->Attribute("linear"), nullptr);
	//		f_Quadratic = std::strtof(it->Attribute("quadratic"), nullptr);
	//		mspo_GameObjects_In.insert(std::pair<std::string, Game_Object*>(s_Name, new Point_Light(v3_Ambient, v3_Diffuse, v3_Specular, f_Constant, f_Linear, f_Quadratic, i_LightID)));
	//		i_NumOfPointLight++;

	//		auto point_Light = static_cast<Point_Light*>(mspo_GameObjects_In.find(s_Name)->second);
	//		auto i_ObjectID = reinterpret_cast<std::uintptr_t>(point_Light);
	//		point_Light->set_ObjectID(i_ObjectID);
	//		point_Light->add_Component("Mesh_3D", po_Loader_In->get_Mesh("7"));
	//		point_Light->add_Component("Transform_3D", new Transform_3D());
	//		point_Light->add_Component("RenderComp_3D", new RenderComp_3D());
	//		point_Light->set_Position(v3_Position);
	//		point_Light->set_RenderStatus(false);
	//		point_Light->add_Texture("Diffuse_Map", po_Loader_In->get_Texture("7"));
	//		point_Light->add_Texture("Specular_Map", po_Loader_In->get_Texture("7"));
	//		point_Light->set_Tiles(glm::vec2(1.f, 1.f));
	//		point_Light->set_Shininess(1.f);
	//		point_Light->set_Tag(s_Tag);
	//	}
	//}
}

void SceneLoader::identify_Component(GameObject_3D* po_GameObject_In, std::string& s_ToProcess_In)
{
	if (s_ToProcess_In == "YourCompnentHere") std::cout << "Nope" << "\n";
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
	//glm::vec3 v3_Vector;
	glm::quat temp;
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
						temp.w = std::strtof(s_Result.c_str(), nullptr);
						s_Result.clear();
					break;

					case 2:
						temp.x = std::strtof(s_Result.c_str(), nullptr);
						s_Result.clear();
					break;

					case 3:
						temp.y = std::strtof(s_Result.c_str(), nullptr);
						s_Result.clear();
					break;
				}
				break;

			case 40: // This bracket "("
			 //Ignore
			break;

			case 41: // This bracket ")"
				temp.z = std::strtof(s_Result.c_str(), nullptr);
			break;

				//Process
			default:
				s_Result = s_Result + pc_Quaternion_In[i];
			break;
		break;
		}	
	}


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
