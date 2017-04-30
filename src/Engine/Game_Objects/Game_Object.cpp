#include "Engine\Game_Objects\Game_Object.h"

void Game_Object::set_RenderStatus(bool b_RenderStatus_In)
{
	b_RenderStatus = b_RenderStatus_In;
}

void Game_Object::add_Child(Game_Object * po_Child_In)
{
	po_Child_In->set_Parent(this);
	mspo_Children.insert(std::pair<std::string, Game_Object*>(po_Child_In->get_Name(), po_Child_In));
}

void Game_Object::set_Parent(Game_Object* po_Parent_In)
{
	po_Parent = po_Parent_In;
}

Game_Object* Game_Object::get_Parent()
{
	return po_Parent;
}

std::string Game_Object::get_Name()
{
	return s_Name;
}

void Game_Object::set_Name(std::string s_Name_In)
{
	s_Name = s_Name_In;
}

std::map<std::string, Component*> Game_Object::get_Components()
{
	return mipo_Components;
}

Component* Game_Object::get_Component(std::string s_Name_In)
{
	std::map<std::string, Component*>::iterator iter = mipo_Components.find(s_Name_In);
	if (iter != mipo_Components.end()) {
		return iter->second;
	}
	//not found
	return nullptr;
}

void Game_Object::set_Tag(std::string s_Tag_In)
{
	s_Tag = s_Tag_In;
}

std::string Game_Object::get_Tag()
{
	return s_Tag;
}