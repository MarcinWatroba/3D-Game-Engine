#pragma once
#include <vector>
#include <glm\glm.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <map>

class Model;
class Loader;
class Game_Object;
class GameObject_3D;
class Light;
class Shader;

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



	//Add children
	void add_Components(GameObject_3D* po_GameObject_In, std::string s_ToProcess_In);

	//Identify the component
	void identify_Component(GameObject_3D* po_GameObject_In, std::string& s_Result_In);

	//Add children
	void add_Children(std::vector<std::string>& vs_Children_In, std::string s_ToProcess_In);

public:
	//Constructor
	SceneLoader() {};

	//Main constructor
	SceneLoader(const char* pc_FileName_In, Loader* po_Loader_In, std::map<std::string, Game_Object*>& mspo_GameObjects3D_In);
	//Set amount of lights to shader
	void set_LightAmount(Shader* p_Shader_In);
	glm::uvec2 setup_FBO();
	void prepare_DepthCube(Shader * p_Shader_In, glm::vec3 light_Pos, glm::uvec2 ui_Depth_In, unsigned int tex_Num);
};