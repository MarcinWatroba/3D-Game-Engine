#pragma once
#include <vector>
#include <glm\glm.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <map>

class Loader;
class PrefabLoader;
class Game_Object;
class GameObject_3D;
class GameObject_Instanced;
class Light;
class Shader;
class Sound;

class SceneLoader
{
private:
	//Loader
	Loader* po_SceneLoader;
	//Convert to 3D vector
	glm::vec3 to3DVector(const char* pc_Vector3D_In);
	//Convert to 2D vector
	glm::vec2 to2DVector(const char* pc_Vector2D_In);

	glm::vec2 shadowMapDimensions;
	//Convert to quaternion
	glm::quat toQuat(const char* pc_Quaternion_In);

	//Depth map GLuints for binding
	//unsigned int depthMapFBO;
	unsigned int depthCubemap;

	float aspect;
	float nearP;
	float farP;
	glm::mat4 projection;

	//Number of lights
	int i_NumOfPointLight;
	glm::vec3 f_pos[100];
	float f_radii[100];



	int count;

public:
	//Constructor
	SceneLoader() {};

	//Main constructor
	SceneLoader(const char* pc_FileName_In, Loader* po_Loader_In, PrefabLoader* po_PrefLoader_In, std::map<std::string, Game_Object*>& mspo_GameObjects_In);

	int get_Count();

	//Set amount of lights to shader
	glm::vec3 get_LightPosition(int i);
	float get_LightRadius(int i);
	void set_LightAmount(Shader* p_Shader_In);
	glm::uvec2 setup_FBO();
	void prepare_DepthCube(Shader * p_Shader_In, glm::vec3 light_Pos, glm::uvec2 ui_Depth_In, unsigned int tex_Num);
};