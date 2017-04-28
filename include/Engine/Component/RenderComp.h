#pragma once

#include <Engine\Component\Component.h>
#include <Engine\Mesh\Mesh.h>

class Shader;
class Texture;

class RenderComp : public Component
{
protected:
	glm::vec3 v3_Colour; // Colour
	glm::vec2 v2_Tiling; // Tiling
	Mesh* p_Mesh;

	std::map<std::string, Texture*> mso_Textures;
public:
	//Constructor
	RenderComp() {};
	virtual void render(int i_DrawMode_In, int i_DrawShape_In, Shader* p_Shader_In) = 0; //Render

	void set_Mesh(Mesh* p_Mesh_In);
	void set_Colour(glm::vec3 rgb_Colour_In);
	glm::vec3 get_Colour();
	void set_Tiles(glm::vec2 v2_Tiles_In);
	glm::vec2 get_Tiles();

	void add_Texture(std::string s_Name_In, Texture* p_Texture_In);
	unsigned int get_Texture(std::string s_Name_In);
};