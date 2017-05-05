#include <Engine/Component/RenderComp.h>
#include <Engine/Creators/Texture.h>

glm::vec2 RenderComp::get_Tiles()
{
	return v2_Tiling;
}

void RenderComp::set_Tiles(glm::vec2 v2_Tiles_In)
{
	v2_Tiling = v2_Tiles_In;
}

void RenderComp::set_Colour(glm::vec3 rgb_Colour_In)
{
	v3_Colour = rgb_Colour_In;
}

glm::vec3 RenderComp::get_Colour()
{
	return v3_Colour;
}

void RenderComp::set_Mesh(Mesh* p_Mesh_In)
{
	p_Mesh = p_Mesh_In;
}

void RenderComp::add_Texture(std::string s_Name_In, Texture* p_Texture_In)
{
	mso_Textures.insert(std::pair<std::string, Texture*>(s_Name_In, p_Texture_In));
}

unsigned int RenderComp::get_Texture(std::string s_Name_In)
{
	auto found = mso_Textures.find(s_Name_In)->second->get_Texture();
	return found;
}

