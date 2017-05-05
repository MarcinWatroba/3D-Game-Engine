#pragma once
#include <Engine\Component\Transform.h>

class Transform_Instanced : public Transform
{

private:
	//void toVector(float i_Array_In[]);
public:
	//------------------Transformations-------------------------
	void set_Position(glm::vec3 v3_Position_In); //Set position
	void set_Origin(glm::vec3 v3_Origin_In); //Set origin

											 //Get origin
	glm::vec3 get_Origin();
	glm::vec3 get_Position();

	//set Scale/Size
	void set_Scale(glm::vec3 v3_Scale_In);

	//Get Scale/Size
	glm::vec3& get_Scale();

	//Set rotation
	void set_Rotation(glm::quat quat_Rot_In);
	void set_Rotation(float f_Angle_In, glm::vec3 v3_RotAxis_In);

	//int get_ParticleCount();
	//std::vector<float> get_ParticlePositions();
	
	//float get_ParticlePositionss();

	//Updating roration
	void update_Rotation(glm::quat quat_Rot_In);
	glm::quat get_Rotation();
	//int FindUnusedParticle();

	void update(); // Update
	void update(glm::mat4 parentMatrix_In); // Update child
	//void update_Particles(float t, float y, float z, glm::vec3 delta);

	void update_Shader(Shader* p_Shader_In);

	glm::mat4 get_ModelMatrix();
};