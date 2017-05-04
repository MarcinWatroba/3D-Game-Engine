#pragma once

#include <Engine\Game_Objects\Game_Object.h>
#include <glm\glm.hpp>

struct Particle {
	glm::vec3 position, speed;
	glm::vec3 lastPos;
	unsigned char r, g, b; // Color
	float size, angle, weight;
	float life; // Remaining life of the particle. if < 0 : dead and unused.
	float cameraDistance;

};

class GameObject_Instanced : public Game_Object
{
private:
	unsigned int maxParticles;
	float particlePositions[3000];
	Particle ParticlesContainer[1000];
	int ParticlesCount, iParticle, LastUsedParticle;
	float random, random2, random3;
	//std::vector<float> positions;
	glm::mat4 get_ParentMatrix();
public:
	//Constructor
	GameObject_Instanced();

	void update();
	void update_Particles(float t, float y, float z, glm::vec3 delta);
	int FindUnusedParticle();
	void force_Update();
	void add_Component(std::string s_Name_In, Component* p_Component_In);
	void add_Texture(std::string s_Name_In, Texture* p_Texture_In);
	void renderDepth(Shader * p_Shader_In);
	void render(Shader* p_Shader_In);
	void clean_Up();

	//-----Set Transformations---------------------------
	void set_Position(glm::vec3 v3_Position_In);
	void set_Scale(glm::vec3 v3_Scale_In);
	void set_Origin(glm::vec3 v3_Origin_In);
	void set_Rotation(glm::quat quat_In);
	void update_Rotation(glm::quat quat_In);

	//-----Get Transformations---------------------------
	virtual glm::vec3 get_Position();
	virtual glm::vec3 get_Origin();
	virtual glm::quat get_Rotation();
	virtual glm::vec3 get_Scale();

	void set_Tiles(glm::vec2 v2_Tiles_In);
};