#include <Engine\Loaders\StatsLoader.h>

StatsLoader::StatsLoader(const char * pc_FileName_In)
{
	tinyxml2::XMLDocument stats_File;
	stats_File.LoadFile(pc_FileName_In);
	tinyxml2::XMLElement* body = stats_File.FirstChildElement("stats");
	for (tinyxml2::XMLElement* it = body->FirstChildElement("new_Stat"); it != nullptr; it = it->NextSiblingElement("new_Stat"))
	{
		std::cout << "Adding new object to the scene..." << "\n";

		std::string s_ObjectName = it->Attribute("name");

		std::string s_Health = it->Attribute("health");
		float i_Health = std::strtof(s_Health.c_str(), nullptr);

		std::string s_Ammo = it->Attribute("ammo");
		float i_Ammo = std::strtof(s_Ammo.c_str(), nullptr);

		std::string s_Mass = it->Attribute("mass");
		float i_Mass = std::strtof(s_Mass.c_str(), nullptr);

		std::string s_Gravity = it->Attribute("gravity");
		bool b_Gravity;
		if (s_Gravity == "false")
		{
			b_Gravity = false;
		}
		else
		{
			b_Gravity = true;
		}

		std::string s_Path1 = it->Attribute("path1");
		if (s_Path1 != "")
		{
			glm::vec3 v_Path1; // = path1;
			std::string s_Path2 = it->Attribute("path2");
			glm::vec3 v_Path2;
			if (s_Path2 != "")
			{
				// v_Path2 = path2;
			}
			statsList.insert(std::make_pair(s_ObjectName, new Stats(i_Health, i_Ammo, i_Mass, b_Gravity, v_Path1, v_Path2)));
		}
		else
		{
			statsList.insert(std::make_pair(s_ObjectName, new Stats(i_Health, i_Ammo, i_Mass, b_Gravity)));
		}

		

		
	}
}

StatsLoader::~StatsLoader()
{

}

Stats * StatsLoader::get_Stat(std::string temp)
{
	return statsList.find(temp)->second;
}

