#include <Engine\Game_Objects\GameObject_3D.h>
#include <Engine/Component/RenderComp_3D.h>
#include <Engine/Component/Transform_3D.h>
#include <Engine/Component/BoxCollider_3D.h>
#include <Engine/Component/RigidBody.h>
#include <Engine\Component\Respond_Movement.h>
#include <Engine\Component\Character.h>
#include <Engine\Creators\Texture.h>
#include <Engine/Mesh/Mesh_3D.h>
#include <Game\Misc\Bullet.h>
#include <glad\glad.h>
#include <iostream>

glm::mat4 GameObject_3D::get_ParentMatrix()
{
	return static_cast<Transform_3D*>(mipo_Components.find("Transform_3D")->second)->get_ModelMatrix();
}

GameObject_3D::GameObject_3D()
{
	b_RenderStatus = true;
	count = fireRate;
}

void GameObject_3D::add_Component(std::string s_Name_In, Component* p_Component_In)
{
	mipo_Components.insert(std::pair<std::string, Component*>(s_Name_In, p_Component_In));

	if (s_Name_In == "RenderComp_3D")
	{
		auto found_Mesh = mipo_Components.find("Mesh_3D");

		if (found_Mesh == mipo_Components.end()) std::cout << "Mesh not found" << "\n";
		else
		{
			auto found_Render = mipo_Components.find("RenderComp_3D")->second;
			static_cast<RenderComp_3D*>(found_Render)->set_Mesh(static_cast<Mesh_3D*>(found_Mesh->second));
		}
	}
	else if (s_Name_In == "BoxCollider_3D")
	{
		auto found_Mesh = mipo_Components.find("Mesh_3D");

		if (found_Mesh == mipo_Components.end()) std::cout << "Mesh not found" << "\n";
		else
		{
			auto found_Collider = mipo_Components.find("BoxCollider_3D")->second;
			static_cast<BoxCollider_3D*>(found_Collider)->setUpBox(&static_cast<Mesh_3D*>(found_Mesh->second)->getMinVert(), &static_cast<Mesh_3D*>(found_Mesh->second)->getMaxVert());
		}

	}
	else if (s_Name_In == "RigidBody")
	{
		auto found_RigidBody = mipo_Components.find("RigidBody")->second;
		dynamic_cast<RigidBody*>(found_RigidBody)->setValues(1.0f, false, dynamic_cast<Transform_3D*>(mipo_Components.at("Transform_3D"))->get_Position());
	}
	else if (s_Name_In == "Character")
	{
		auto found_Character = mipo_Components.find("Character")->second;
		dynamic_cast<Character*>(found_Character)->setHealth(3);
		dynamic_cast<Character*>(found_Character)->setNumberOfBullets(100);
	}

}

void GameObject_3D::add_Texture(std::string s_Name_In, Texture* p_Texture_In)
{
	static_cast<RenderComp_3D*>(mipo_Components.find("RenderComp_3D")->second)->add_Texture(s_Name_In, p_Texture_In);
}

void GameObject_3D::update()
{

	if (po_Parent != nullptr)
	{
		static_cast<Transform_3D*>(mipo_Components.find("Transform_3D")->second)->force_Update(); // Update must be forced to update any children
		static_cast<Transform_3D*>(mipo_Components.find("Transform_3D")->second)->update(static_cast<GameObject_3D*>(po_Parent)->get_ParentMatrix());
		if (mipo_Components.count("BoxCollider_3D"))
		{
			dynamic_cast<BoxCollider_3D*>(mipo_Components.find("BoxCollider_3D")->second)->updatePos(static_cast<GameObject_3D*>(po_Parent)->get_ParentMatrix());
		}
	}
	else
	{
		static_cast<Transform_3D*>(mipo_Components.find("Transform_3D")->second)->update();
		if (mipo_Components.count("BoxCollider_3D"))
		{
			dynamic_cast<BoxCollider_3D*>(mipo_Components.find("BoxCollider_3D")->second)->updatePos(get_ParentMatrix());
		}
	}
	
	shootBullet();
	for (int i = 0; i < bulletList.size(); i++)
	{
		if (bulletList.empty())
		{
			break;
		}
		bulletList[i]->update();
		if (static_cast<BoxCollider_3D*>(bulletList[i]->get_Components().at("BoxCollider_3D"))->getCollisionCheck())
		{
			delete bulletList[i];
			bulletList.erase(bulletList.begin() + i);
			bulletNumber--;
			i--;
		}
		
	}
		

}

void GameObject_3D::renderDepth(Shader* p_Shader_In)
{
	static_cast<Transform_3D*>(mipo_Components.find("Transform_3D")->second)->update_Shader(p_Shader_In);
	if (b_RenderStatus) static_cast<RenderComp_3D*>(mipo_Components.find("RenderComp_3D")->second)->renderDepth(GL_TEXTURE_2D, GL_TRIANGLES, p_Shader_In);
}

void GameObject_3D::render(Shader* p_Shader_In)
{
	static_cast<Transform_3D*>(mipo_Components.find("Transform_3D")->second)->update_Shader(p_Shader_In);
	if (b_RenderStatus) static_cast<RenderComp_3D*>(mipo_Components.find("RenderComp_3D")->second)->render(GL_TEXTURE_2D, GL_TRIANGLES, p_Shader_In);

	for (int i = 0; i < bulletList.size(); i++)
	{
		bulletList[i]->render(p_Shader_In);
	}
}

void GameObject_3D::clean_Up()
{
	if (!mipo_Components.empty()) for (auto map : mipo_Components) if(map.first != "Mesh_3D") delete map.second;
	mipo_Components.clear();
}

void GameObject_3D::force_Update()
{
	static_cast<Transform_3D*>(mipo_Components.find("Transform_3D")->second)->force_Update();
}

void GameObject_3D::set_Position(glm::vec3 v3_Position_In)
{
	static_cast<Transform_3D*>(mipo_Components.find("Transform_3D")->second)->set_Position(v3_Position_In);
}

void GameObject_3D::set_Scale(glm::vec3 v3_Scale_In)
{
	static_cast<Transform_3D*>(mipo_Components.find("Transform_3D")->second)->set_Scale(v3_Scale_In);
}

void GameObject_3D::set_Origin(glm::vec3 v3_Origin_In)
{
	static_cast<Transform_3D*>(mipo_Components.find("Transform_3D")->second)->set_Origin(v3_Origin_In);
}

void GameObject_3D::set_Rotation(glm::quat quat_In)
{
	static_cast<Transform_3D*>(mipo_Components.find("Transform_3D")->second)->set_Rotation(quat_In);
}

void GameObject_3D::update_Rotation(glm::quat quat_In)
{
	static_cast<Transform_3D*>(mipo_Components.find("Transform_3D")->second)->update_Rotation(quat_In);
}

glm::vec3 GameObject_3D::get_Position()
{
	return static_cast<Transform_3D*>(mipo_Components.find("Transform_3D")->second)->get_Position();
}

glm::vec3 GameObject_3D::get_Origin()
{
	return static_cast<Transform_3D*>(mipo_Components.find("Transform_3D")->second)->get_Origin();
}

glm::quat GameObject_3D::get_Rotation()
{
	return static_cast<Transform_3D*>(mipo_Components.find("Transform_3D")->second)->get_Rotation();
}

glm::vec3 GameObject_3D::get_Scale()
{
	return static_cast<Transform_3D*>(mipo_Components.find("Transform_3D")->second)->get_Scale();
}

std::vector<GameObject_3D*> GameObject_3D::get_BulletList()
{
	return bulletList;
}

void GameObject_3D::set_Shininess(float f_Shiny_In)
{
	static_cast<RenderComp_3D*>(mipo_Components.find("RenderComp_3D")->second)->set_Shininess(f_Shiny_In);
}

void GameObject_3D::set_Tiles(glm::vec2 v2_Tiles_In)
{
	static_cast<RenderComp_3D*>(mipo_Components.find("RenderComp_3D")->second)->set_Tiles(v2_Tiles_In);
}

void GameObject_3D::move(glm::vec3 v3_Direction_In, float f_Speed_In)
{
	if (mipo_Components.count("Respond_Movement"))
	{
		auto found_Movement = mipo_Components.at("Respond_Movement");
		bool isPositive;
		if (f_Speed_In > 0)
		{
			isPositive = true;
		}
		else
		{
			isPositive = false;
		}

		if (mipo_Components.count("RigidBody"))
		{
			bool tempCheck = false;
			for (auto const& map : mspo_Children)
			{
				if (map.second->get_Components().count("BoxCollider_3D"))
				{
					if (dynamic_cast<BoxCollider_3D*>(map.second->get_Components().at("BoxCollider_3D"))->getCollisionCheck())
					{
						tempCheck = dynamic_cast<BoxCollider_3D*>(map.second->get_Components().at("BoxCollider_3D"))->getCollisionCheck();
					}
				}
			}
			if (tempCheck && lastDir == isPositive)
			{
				dynamic_cast<RigidBody*>(mipo_Components.at("RigidBody"))->setForwardForce(0);
			}
			else
			{
				dynamic_cast<RigidBody*>(mipo_Components.at("RigidBody"))->setForwardForce(f_Speed_In);
			}
			dynamic_cast<RigidBody*>(mipo_Components.at("RigidBody"))->update(get_Position());
			dynamic_cast<Respond_Movement*>(found_Movement)->move(this, v3_Direction_In, dynamic_cast<RigidBody*>(mipo_Components.at("RigidBody"))->getVelocity());
		}
		else
		{
			dynamic_cast<Respond_Movement*>(found_Movement)->move(this, v3_Direction_In, f_Speed_In);
		}
		lastDir = isPositive;
		//lastRot = get_Rotation();
	}
}

void GameObject_3D::jump(glm::vec3 v3_Direction_In)
{
	if (mipo_Components.count("Respond_Movement"))
	{
		auto found_Movement = mipo_Components.at("Respond_Movement");
		dynamic_cast<RigidBody*>(mipo_Components.at("RigidBody"))->update(get_Position());
		dynamic_cast<Respond_Movement*>(found_Movement)->move(this, v3_Direction_In, dynamic_cast<RigidBody*>(mipo_Components.at("RigidBody"))->getJumpVelocity());
	}
}

void GameObject_3D::turn(float f_Angle_In, glm::vec3 v3_TurnAxis_In)
{
	if (mipo_Components.count("Respond_Movement"))
	{
		auto found_Movement = mipo_Components.at("Respond_Movement");
		dynamic_cast<Respond_Movement*>(found_Movement)->turn(this, f_Angle_In, v3_TurnAxis_In);
	}
}

void GameObject_3D::setFiring(bool input)
{
	firing = input;
}

void GameObject_3D::createBullet(Bullet* bulletTemplate)
{ 
	if (count == fireRate)
	{
		if (static_cast<Character*>(mipo_Components.at("Character"))->getNumberOfBullets() != 0)
		{
			bulletList.push_back(bulletTemplate);
			//bulletList[bulletNumber]->set_Position(get_Position());
			//bulletList[bulletNumber]->set_Rotation(get_Rotation());
			bulletList[bulletNumber]->set_RenderStatus(true);
			static_cast<Character*>(mipo_Components.at("Character"))->loseBullets();
			bulletNumber++;
			count = 0;
			float e = static_cast<Character*>(mipo_Components.at("Character"))->getNumberOfBullets();
			std::cout << e << std::endl;
		}
		
	}
	else
	{
		count++;
	}

}

void GameObject_3D::shootBullet()
{
	for (int i = 0; i < bulletList.size(); i++)
	{
		bulletList[i]->move(glm::vec3(0, 0, 1), .1);

		
		
	}
	if (!bulletList.empty())
	{
		glm::vec3 temp = bulletList[0]->get_Position();
		//std::cout << "(" << temp.x << ", " << temp.y << ", " << temp.z << ")" << std::endl << std::endl;
	}
}


void GameObject_3D::resetCount()
{
	count = fireRate;
}
