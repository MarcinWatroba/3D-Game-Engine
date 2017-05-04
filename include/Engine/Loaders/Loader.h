#pragma once

//Obligatory
///Engine classes///
#include <Engine\Creators\Shader.h>
#include <Engine\Creators\Texture.h>
#include <Engine\Mesh\Mesh_3D.h>
#include <Engine\Mesh\Mesh_Instanced.h>
//#include <Model_IDs.h>
//#include <Font.h>

///3rd party///
#include <TinyXML2\tinyxml2.h>

//Include all components here
/// Cube ///
//#include <RenderComp_3D.h>

class Loader
{
private:
	//Models
	std::map<std::string, Mesh_3D*> mipo_Meshes3D;
	std::map<std::string, Mesh_Instanced*> mipo_MeshesInstanced;
	//Shader
	std::map<std::string, Shader*> mipo_Shaders;
	//Texture files
	std::map<std::string, Texture*> mipo_TextureFiles;
	//Fonts
	//std::map<int, Font> mipo_Fonts;

	void ParseXML_Resources(const char* pc_FileName); // Parse the shaders
public:
	//Constructor
	Loader() {};

	//Start the maker
	void start();

	//Get the shader
	Shader* get_Shader(std::string s_Name_In);
	
	//Get texture
	Texture* get_Texture(std::string s_Name_In);

	//Get the model
	//Model* get_Model(int i_Model_ID);
	Mesh_3D* get_Mesh3D(std::string s_Name_In);

	Mesh_Instanced * get_MeshInstanced(std::string s_Name_In);

	//Font& get_Font(int i_Font_ID);

	//Clean up the memory
	void clean_Up();

	//std::map<int, Shader>* get_ShaderMap();
};