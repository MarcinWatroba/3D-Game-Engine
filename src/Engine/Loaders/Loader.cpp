#include <Engine\Loaders\Loader.h>
#include <iostream>
#include <glad\glad.h>

void Loader::start()
{
	std::cout << "Parsing XML resource file..." << "\n";
	ParseXML_Resources("assets/Resources.xml");
	std::cout << "Pasrsing completed..." << "\n";
}

Mesh_3D* Loader::get_Mesh3D(std::string s_Name_In)
{
	return mipo_Meshes3D.find(s_Name_In)->second;
}

Mesh_Instanced* Loader::get_MeshInstanced(std::string s_Name_In)
{
	std::cout << mipo_MeshesInstanced.find(s_Name_In)->second->get_VAO() << std::endl;
	return mipo_MeshesInstanced.find(s_Name_In)->second;
}

Shader* Loader::get_Shader(std::string s_Name_In)
{
	return mipo_Shaders.find(s_Name_In)->second;
}

Texture* Loader::get_Texture(std::string s_Name_In)
{
	return mipo_TextureFiles.find(s_Name_In)->second;
}

void Loader::clean_Up()
{
	//Delete every memory
	for (const auto& pair : mipo_Meshes3D) delete pair.second;
	for (const auto& pair : mipo_MeshesInstanced) delete pair.second;
	for (const auto& pair : mipo_TextureFiles) delete pair.second;
	for (const auto& pair : mipo_Shaders) delete pair.second;
}

void Loader::ParseXML_Resources(const char* pc_FileName)
{
	tinyxml2::XMLDocument resources_File; // Create a file template
	resources_File.LoadFile(pc_FileName); // Load the file
	tinyxml2::XMLElement* po_Body = resources_File.FirstChildElement("resources"); // Start from <models>

	//Obj files first
	std::string obj_FileLoc = po_Body->FirstChildElement("object_File_Location")->GetText();
	for (tinyxml2::XMLElement* i = po_Body->FirstChildElement("object_Files")->FirstChildElement("new_File"); i != nullptr; i = i->NextSiblingElement("new_File"))
	{
		//Create variables
		std::string i_ID = i->Attribute("ID");
		std::string s_Name = obj_FileLoc + i->Attribute("name");
		int i_DrawMethod = std::atoi(i->Attribute("i_DrawMethod"));

		mipo_Meshes3D.insert(std::pair<std::string, Mesh_3D*>(i_ID, new Mesh_3D(s_Name.c_str(), i_DrawMethod)));
	}

	for (tinyxml2::XMLElement* i = po_Body->FirstChildElement("particle_Files")->FirstChildElement("new_File"); i != nullptr; i = i->NextSiblingElement("new_File"))
	{
		//Create variables
		std::string i_ID = i->Attribute("ID");
		std::string s_Name = obj_FileLoc + i->Attribute("name");
		int i_DrawMethod = std::atoi(i->Attribute("i_DrawMethod"));

		mipo_MeshesInstanced.insert(std::pair<std::string, Mesh_Instanced*>(i_ID, new Mesh_Instanced(s_Name.c_str(), i_DrawMethod)));
	}

	std::string texture_FileLoc = po_Body->FirstChildElement("texture_File_Location")->GetText();
	for (tinyxml2::XMLElement* i = po_Body->FirstChildElement("texture_Files")->FirstChildElement("new_File"); i != nullptr; i = i->NextSiblingElement("new_File"))
	{
		//Create variables
		std::string i_ID = i->Attribute("ID");
		std::string s_Name = texture_FileLoc + i->Attribute("name");
		int i_TextureMode = std::atoi(i->Attribute("texture_Mode"));
		int i_WrappingS = std::atoi(i->Attribute("wrapping_S"));
		int i_WrappingT = std::atoi(i->Attribute("wrapping_T"));
		int i_FilterMin = std::atoi(i->Attribute("filter_Min"));
		int i_FilterMag = std::atoi(i->Attribute("filter_Mag"));
		int i_SoilColourLoad = std::atoi(i->Attribute("soil_Colour_Load"));
		int i_OpenGLColour = std::atoi(i->Attribute("openGL_Colour"));
		int i_GenMipmaps = std::atoi(i->Attribute("gen_Mipmaps"));

		//Add texture
		mipo_TextureFiles.insert(std::make_pair(i_ID, new Texture(s_Name.c_str(), i_TextureMode, i_WrappingS, i_WrappingT, i_FilterMin, i_FilterMag, i_SoilColourLoad, i_OpenGLColour, i_GenMipmaps)));
	}

	std::string shader_FileLoc = po_Body->FirstChildElement("shader_File_Location")->GetText();
	for (tinyxml2::XMLElement* i = po_Body->FirstChildElement("shader_Files")->FirstChildElement("new_File"); i != nullptr; i = i->NextSiblingElement("new_File"))
	{
		//Create variables
		std::string i_ID = i->Attribute("ID");
		std::string s_NameVertex = shader_FileLoc + i->Attribute("vertex");
		std::string s_NameFragment = shader_FileLoc + i->Attribute("fragment");
		std::string s_NameGeometry = i->Attribute("geometry");

		if (s_NameGeometry == "") s_NameGeometry = "";
		else s_NameGeometry = shader_FileLoc + s_NameGeometry;
		
		//Add shader
		mipo_Shaders.insert(std::make_pair(i_ID, new Shader(s_NameVertex.c_str(), s_NameFragment.c_str(), s_NameGeometry.c_str())));
	}

	//std::string font_FileLoc = po_Body->FirstChildElement("font_File_Location")->GetText();
	//for (tinyxml2::XMLElement* i = po_Body->FirstChildElement("font_Files")->FirstChildElement("new_File"); i != nullptr; i = i->NextSiblingElement("new_File"))
	//{
	//	//Create variables
	//	int i_ID = std::atoi(i->Attribute("ID"));
	//	std::string s_FileName = font_FileLoc + i->Attribute("name");
	//	
	//	tinyxml2::XMLDocument fonts_File; // Create a file template
	//	fonts_File.LoadFile(s_FileName.c_str()); // Load the file
	//	tinyxml2::XMLElement* po_FontBody = fonts_File.FirstChildElement("font"); // Start from <models>
	//	
	//	float f_FontSizeX = std::atof(po_FontBody->FirstChildElement("common")->Attribute("scaleW"));
	//	float f_FontSizeY = std::atof(po_FontBody->FirstChildElement("common")->Attribute("scaleH"));
	//	int i_FontTextureID = std::atoi(po_FontBody->FirstChildElement("id")->Attribute("texture_ID"));
	//	int i_FontShaderID = std::atoi(po_FontBody->FirstChildElement("id")->Attribute("shader_ID"));

	//	//Add new font
	//	mipo_Fonts.insert(std::make_pair(i_ID, Font(glm::vec2(f_FontSizeX, f_FontSizeY), i_FontTextureID, i_FontShaderID)));

	//	for (tinyxml2::XMLElement* i = po_FontBody->FirstChildElement("chars")->FirstChildElement("char"); i != nullptr; i = i->NextSiblingElement("char"))
	//	{
	//		//Create variables
	//		char c_ID = std::atoi(i->Attribute("id"));
	//		float f_PosX = std::atof(i->Attribute("x"));
	//		float f_PosY = std::atof(i->Attribute("y"));
	//		float f_Width = std::atof(i->Attribute("width"));
	//		float f_Height = std::atof(i->Attribute("height"));
	//		float f_OffsetX = std::atof(i->Attribute("xoffset"));
	//		float f_OffsetY = std::atof(i->Attribute("yoffset"));
	//		float f_AdvanceX = std::atof(i->Attribute("xadvance"));

	//		//Add new glyph
	//		mipo_Fonts.find(i_ID)->second.add_Glyph(c_ID, Glyph(glm::vec2(f_PosX, f_PosY), glm::vec2(f_FontSizeX, f_FontSizeY), glm::vec2(f_Width, f_Height), glm::vec2(f_OffsetX, f_OffsetY), f_AdvanceX));
	//	}
	//}
}