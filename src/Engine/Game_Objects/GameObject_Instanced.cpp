#include <Engine\Game_Objects\GameObject_Instanced.h>
#include <Engine/Component/RenderComp_Instanced.h>
#include <Engine/Component/Transform_Instanced.h>
#include <Engine\Creators\Texture.h>
#include <Engine/Mesh/Mesh_Instanced.h>
#include <glad\glad.h>
#include <iostream>

glm::mat4 GameObject_Instanced::get_ParentMatrix()
{
	return glm::mat4();
}

GameObject_Instanced::GameObject_Instanced()
{
	b_RenderStatus = true;
}

void GameObject_Instanced::update()
{
	static_cast<Transform_Instanced*>(mipo_Components.find("Transform_Instanced")->second)->update();
}

//void GameObject_Instanced::update_Particles(float t, float y, float z, glm::vec3 delta)
//{
//	update_Particles(t, y, z, delta);
//}

void GameObject_Instanced::force_Update()
{
	static_cast<Transform_Instanced*>(mipo_Components.find("Transform_Instanced")->second)->force_Update();
}

void GameObject_Instanced::add_Component(std::string s_Name_In, Component * p_Component_In)
{
	mipo_Components.insert(std::pair<std::string, Component*>(s_Name_In, p_Component_In));

	if (s_Name_In == "RenderComp_Instanced")
	{
		auto found_Mesh = mipo_Components.find("RenderComp_Instanced");

		if (found_Mesh == mipo_Components.end()) std::cout << "Mesh not found" << "\n";
		else
		{
			auto found_Render = mipo_Components.find("RenderComp_Instanced")->second;
			static_cast<RenderComp_Instanced*>(found_Render)->set_Mesh(static_cast<Mesh_Instanced*>(found_Mesh->second));
		}

	}
}

void GameObject_Instanced::add_Texture(std::string s_Name_In, Texture * p_Texture_In)
{
	static_cast<RenderComp_Instanced*>(mipo_Components.find("RenderComp_Instanced")->second)->add_Texture(s_Name_In, p_Texture_In);
}

void GameObject_Instanced::renderDepth(Shader * p_Shader_In)
{
}

void GameObject_Instanced::render(Shader * p_Shader_In)
{
	static_cast<Transform_Instanced*>(mipo_Components.find("Transform_Instanced")->second)->update_Shader(p_Shader_In);
	if (b_RenderStatus) static_cast<RenderComp_Instanced*>(mipo_Components.find("RenderComp_Instanced")->second)->renderInstanced(GL_TEXTURE_2D, GL_TRIANGLES, p_Shader_In, 1000, ParticlesCount, particlePositions);
}

void GameObject_Instanced::clean_Up()
{

}

void GameObject_Instanced::set_Position(glm::vec3 v3_Position_In)
{
	static_cast<Transform_Instanced*>(mipo_Components.find("Transform_Instanced")->second)->set_Position(v3_Position_In);
}

void GameObject_Instanced::set_Scale(glm::vec3 v3_Scale_In)
{
	static_cast<Transform_Instanced*>(mipo_Components.find("Transform_Instanced")->second)->set_Scale(v3_Scale_In);
}

void GameObject_Instanced::set_Origin(glm::vec3 v3_Origin_In)
{
	static_cast<Transform_Instanced*>(mipo_Components.find("Transform_Instanced")->second)->set_Origin(v3_Origin_In);
}

void GameObject_Instanced::set_Rotation(glm::quat quat_In)
{
	static_cast<Transform_Instanced*>(mipo_Components.find("Transform_Instanced")->second)->set_Rotation(quat_In);
}

void GameObject_Instanced::update_Rotation(glm::quat quat_In)
{
	static_cast<Transform_Instanced*>(mipo_Components.find("Transform_Instanced")->second)->update_Rotation(quat_In);
}

glm::vec3 GameObject_Instanced::get_Position()
{
	return static_cast<Transform_Instanced*>(mipo_Components.find("Transform_Instanced")->second)->get_Position();
}

glm::vec3 GameObject_Instanced::get_Origin()
{
	return static_cast<Transform_Instanced*>(mipo_Components.find("Transform_Instanced")->second)->get_Origin();
}

glm::quat GameObject_Instanced::get_Rotation()
{
	return static_cast<Transform_Instanced*>(mipo_Components.find("Transform_Instanced")->second)->get_Rotation();
}

glm::vec3 GameObject_Instanced::get_Scale()
{
	return static_cast<Transform_Instanced*>(mipo_Components.find("Transform_Instanced")->second)->get_Scale();
}

void GameObject_Instanced::set_Tiles(glm::vec2 v2_Tiles_In)
{
	static_cast<RenderComp_Instanced*>(mipo_Components.find("RenderComp_Instanced")->second)->set_Tiles(v2_Tiles_In);
}

void GameObject_Instanced::update_Particles(float t, float y, float z, glm::vec3 delta)
{

	ParticlesCount = 0;
	int newparticles = (int)(t*1000.0);
	if (newparticles > 16)
		newparticles = 16;
	
	for (int i = 0; i < newparticles; i++)
	{
		FindUnusedParticle();
		random = static_cast <float> (rand()) / static_cast <float> (RAND_MAX / 100) - 50;
		random2 = static_cast <float> (rand()) / static_cast <float> (RAND_MAX / 100);
		random3 = static_cast <float> (rand()) / static_cast <float> (RAND_MAX / 100) - 50;

		iParticle = this->FindUnusedParticle();
		ParticlesContainer[iParticle].life = 1.0f;
		ParticlesContainer[iParticle].position = glm::vec3(random, random2, -random3);
		ParticlesContainer[iParticle].size = 1.0f;
		ParticlesContainer[iParticle].speed = glm::vec3(0.0, -32.0, 0.0);
		ParticlesContainer[iParticle].r = 1.0f;
		ParticlesContainer[iParticle].g = 1.0f;
		ParticlesContainer[iParticle].b = 1.0f;
	}
	for (int i = 0; i<1000; i++) {

		Particle& p = ParticlesContainer[i]; // shortcut

		if (p.life > 0.0f) {

			// Decrease life
			p.life -= t;

			if (p.life > 0.0f) {
				// Simulate simple physics : gravity only, no collisions

				p.speed = glm::vec3(0.0, -32.0, 0.0);
				//p.speed += glm::vec3(0.0f, -3.81f, 0.0f) * (float)t * 0.5f;
				p.position += (p.speed * (float)t);

				// Fill the GPU buffer
				particlePositions[3 * ParticlesCount + 0] = p.position.x;
				particlePositions[3 * ParticlesCount + 1] = p.position.y;
				particlePositions[3 * ParticlesCount + 2] = p.position.z;

			}
			else {


			}

			ParticlesCount++;

		}
	}
}

int GameObject_Instanced::FindUnusedParticle()
{
	for (int i = LastUsedParticle; i < 1000; i++) {
		if (ParticlesContainer[i].life <= 0) {
			LastUsedParticle = i;

			return i;
		}
	}

	for (int i = 0; i<LastUsedParticle; i++) {
		if (ParticlesContainer[i].life <= 0) {
			LastUsedParticle = i;

			return i;
		}
	}
	return 0;
}