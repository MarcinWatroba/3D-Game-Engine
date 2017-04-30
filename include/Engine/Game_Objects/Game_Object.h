#pragma once
#include <string>
#include <map>
#include <glm\glm.hpp>

class Component;
class Shader;
class Texture;

class Game_Object
{
protected:
	//Name of the object
	std::string s_Name;

	//Components
	std::map<std::string, Component*> mipo_Components;

	//Children of the object
	std::map<std::string, Game_Object*> mspo_Children;

	std::string s_Tag;

	//Parent
	Game_Object* po_Parent;

	//Check if container
	bool b_IsContainer;

	//Status of rendering
	bool b_RenderStatus;

	virtual glm::mat4 get_ParentMatrix() = 0;

	//Last Direction for Movement
	bool lastDir = false;

public:
	virtual void add_Component(std::string s_Name_In, Component* p_Component_In) = 0;
	virtual void add_Texture(std::string s_Name_In, Texture* p_Texture_In) = 0;
	virtual void set_Tiles(glm::vec2 v2_Tiles_In) = 0;
	virtual void update() = 0;
	virtual void force_Update() = 0;
	virtual void render(Shader* p_Shader_In) = 0;
	virtual void clean_Up() = 0;

	void set_Name(std::string s_Name_In);
	std::string get_Name();
	void set_RenderStatus(bool b_RenderStatus_In);
	void add_Child(Game_Object* po_Child_In);
	void set_Parent(Game_Object* po_Parent_In);
	Game_Object* get_Parent();
	std::map<std::string, Component*> get_Components();
	Component* get_Component(std::string s_Name_In);
	std::map<std::string, Game_Object*> get_Children();
	void set_Tag(std::string s_Tag_In);
	std::string get_Tag();
	bool is_Container();
};