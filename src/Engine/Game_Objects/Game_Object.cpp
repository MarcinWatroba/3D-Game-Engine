#include "Engine\Game_Objects\Game_Object.h"

void Game_Object::set_RenderStatus(bool b_RenderStatus_In)
{
	b_RenderStatus = b_RenderStatus_In;
}

void Game_Object::set_Prefab(std::string s_Name_In)
{
	s_PrefabName = s_Name_In;
}

std::string Game_Object::get_PrefabName()
{
	return s_PrefabName;
}

bool Game_Object::get_RenderStatus()
{
	return b_RenderStatus;
}

void Game_Object::add_Child(Game_Object* po_Child_In)
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

void Game_Object::add_ChildName(std::string s_Name_In)
{
	vs_ChildrenNames.push_back(s_Name_In);
}

std::vector<std::string>& Game_Object::get_ChildrenNames()
{
	return vs_ChildrenNames;
}

void Game_Object::set_Name(std::string s_Name_In)
{
	s_Name = s_Name_In;
}

void Game_Object::set_ObjectType(std::string s_Type_In)
{
	s_ObjectType = s_Type_In;
}

std::map<std::string, Component*>& Game_Object::get_Components()
{
	return mipo_Components;
}

std::map<std::string, Game_Object*>& Game_Object::get_Children()
{
	return mspo_Children;
}

void Game_Object::set_Tag(std::string s_Tag_In)
{
	s_Tag = s_Tag_In;
}

std::string Game_Object::get_Tag()
{
	return s_Tag;
}

std::string Game_Object::get_ObjectType()
{
	return s_ObjectType;
}

void Game_Object::set_ObjectID(int i_ID_In)
{
	i_ObjectID = i_ID_In;
}

int Game_Object::get_ObjectID()
{
	return i_ObjectID;
}

Game_Object::Game_Object(const Game_Object &p_NewObject_In)
{
	s_Tag = p_NewObject_In.s_Tag;
	po_Parent = p_NewObject_In.po_Parent;
	b_IsContainer = p_NewObject_In.b_IsContainer;
	i_ObjectID = p_NewObject_In.i_ObjectID;
	b_RenderStatus = p_NewObject_In.b_RenderStatus;
	v2_Tiling = p_NewObject_In.v2_Tiling;
}
