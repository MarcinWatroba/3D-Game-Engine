#include <Engine\Component\Transform_Instanced.h>
#include <Engine\Creators\Shader.h>
#include <glad\glad.h>
#include <vector>

void Transform_Instanced::update()
{
	if (b_Update)
	{
		mat4_Model = glm::mat4();
		quat_Orientation = glm::normalize(quat_Orientation);
		mat4_Model = glm::translate(mat4_Model, v3_Position);
		mat4_Model = glm::translate(mat4_Model, -v3_Origin);
		mat4_Model *= glm::mat4_cast(quat_Orientation);
		mat4_Model = glm::translate(mat4_Model, v3_Origin);
		mat4_Model = glm::scale(mat4_Model, v3_Scale);

		b_Update = false;
	}
}

void Transform_Instanced::update(glm::mat4 parent_Matrix_In)
{
	if (b_Update)
	{
		mat4_Model = parent_Matrix_In;
		quat_Orientation = glm::normalize(quat_Orientation);
		mat4_Model = glm::translate(mat4_Model, v3_Position);
		mat4_Model = glm::translate(mat4_Model, -v3_Origin);
		mat4_Model *= glm::mat4_cast(quat_Orientation);
		mat4_Model = glm::translate(mat4_Model, v3_Origin);
		mat4_Model = glm::scale(mat4_Model, v3_Scale);

		b_Update = false;
	}
}

//void Transform_Instanced::update_Particles(float t, float y, float z, glm::vec3 delta)
//{
//	random = static_cast <float> (rand()) / static_cast <float> (RAND_MAX / 20) - 10;
//	random2 = static_cast <float> (rand()) / static_cast <float> (RAND_MAX / 10);
//	random3 = static_cast <float> (rand()) / static_cast <float> (RAND_MAX / 20) - 10;
//	ParticlesCount = 0;
//	FindUnusedParticle();
//
//	iParticle = this->FindUnusedParticle();
//	ParticlesContainer[iParticle].life = 1.0f;
//	ParticlesContainer[iParticle].position = glm::vec3(random, random2, -random3);
//	ParticlesContainer[iParticle].size = 1.0f;
//	ParticlesContainer[iParticle].speed = glm::vec3(0.0, -9.0 * y, 0.0);
//	ParticlesContainer[iParticle].r = 1.0f;
//	ParticlesContainer[iParticle].g = 1.0f;
//	ParticlesContainer[iParticle].b = 1.0f;
//
//	for (int i = 0; i<10000; i++) {
//
//		Particle& p = ParticlesContainer[i]; // shortcut
//
//		if (p.life > 0.0f) {
//
//			// Decrease life
//			p.life -= t;
//
//			if (p.life > 0.0f) {
//				// Simulate simple physics : gravity only, no collisions
//
//				p.speed = glm::vec3(0.0, -9.0 * y, 0.0);
//				p.speed += glm::vec3(0.0f, -9.81f, 0.0f) * (float)t * 0.5f;
//				p.position += (p.speed * (float)t);
//
//				// Fill the GPU buffer
//				particlePositions[3 * ParticlesCount + 0] = p.position.x;
//				particlePositions[3 * ParticlesCount + 1] = p.position.y;
//				particlePositions[3 * ParticlesCount + 2] = p.position.z;
//
//			}
//			else {
//
//
//			}
//
//			ParticlesCount++;
//
//		}
//	}
//
//	toVector(particlePositions);
//	//updateParticles(MaxParticles, ParticlesCount, particlePositions);
//}
//
//void Transform_Instanced::toVector(float i_Array_In[])
//{
//	for (int i = 0; i < 30000; i++)
//	{
//		positions.push_back(i_Array_In[i]);
//	}
//}

glm::mat4 Transform_Instanced::get_ModelMatrix()
{
	return mat4_Model;
}

void Transform_Instanced::update_Shader(Shader* p_Shader_In)
{
	//Uniform locations
	int modelLoc = glGetUniformLocation(p_Shader_In->get_Program(), "model");
	//Pass them to shaders
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(mat4_Model));
}

void Transform_Instanced::set_Position(glm::vec3 v3_Position_In)
{
	b_Update = true;
	v3_Position = v3_Position_In;
}

void Transform_Instanced::set_Origin(glm::vec3 v3_Origin_In)
{
	b_Update = true;
	v3_Origin = v3_Origin_In;
}

glm::vec3 Transform_Instanced::get_Position()
{
	return v3_Position;
}

void Transform_Instanced::set_Scale(glm::vec3 v3_Scale_In)
{
	b_Update = true;
	v3_Scale = v3_Scale_In;
}

glm::vec3& Transform_Instanced::get_Scale()
{
	return v3_Scale;
}

void Transform_Instanced::set_Rotation(glm::quat quat_Rot_In)
{
	b_Update = true;
	quat_Orientation = quat_Rot_In * quat_Orientation;

}

void Transform_Instanced::update_Rotation(glm::quat quat_Rot_In)
{
	b_Update = true;
	quat_Orientation = glm::slerp(quat_Orientation, quat_Rot_In, 0.5f);
}

glm::quat Transform_Instanced::get_Rotation()
{
	return quat_Orientation;
}

//int Transform_Instanced::FindUnusedParticle()
//{
//	for (int i = LastUsedParticle; i<10000; i++) {
//		if (ParticlesContainer[i].life <= 0) {
//			LastUsedParticle = i;
//
//			return i;
//		}
//	}
//
//	for (int i = 0; i<LastUsedParticle; i++) {
//		if (ParticlesContainer[i].life <= 0) {
//			LastUsedParticle = i;
//
//			return i;
//		}
//	}
//	return 0;
//}

glm::vec3 Transform_Instanced::get_Origin()
{
	return v3_Origin;
}

void Transform_Instanced::set_Rotation(float f_Angle_In, glm::vec3 v3_RotAxis_In)
{
	b_Update = true;
	glm::quat quat_Temp = glm::angleAxis(glm::radians(f_Angle_In), v3_RotAxis_In);
	quat_Orientation = quat_Temp * quat_Orientation;
}

//int Transform_Instanced::get_ParticleCount()
//{
//	return ParticlesCount;
//}
//
//std::vector<float> Transform_Instanced::get_ParticlePositions()
//{
//	return positions;
//}
//
//float Transform_Instanced::get_ParticlePositionss()
//{
//	return 0.0f;
//}