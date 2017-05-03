#ifndef RIGIDBODY_H
#define RIGIDBODY_H

#include <Engine\Physics\Physics.h>
#include <iostream>
#include <string>
#include <map>
#include <Engine/Component/Component.h>

class RigidBody : public Component
{
private:
	Physics phys;
	std::map<std::string, bool> boolList;
	float mass;
	bool moveable;
	glm::vec3 centreOfMass;
	float forward_Force;
	float velocity;
	float jumpForce;
	float jumpVelocity;
	float jumpHeight = 5.0f;
	float counter = 0;
	bool reachedPeak = false;
	bool grounded = true;
public:
	RigidBody();
	~RigidBody();
	void setValues(float baseMass, bool move, glm::vec3 position);
	void setPhysics(std::string iD, bool value);
	void update(glm::vec3 &newPos);
	bool get_Moveable()
	{
		return moveable;
	}
	float getVelocity()
	{
		return velocity;
	}
	float getJumpForce()
	{
		return jumpForce;
	}
	float getJumpVelocity()
	{
		return jumpVelocity;
	}
	bool getGrounded()
	{
		return grounded;
	}
	void setJumpForce(float force);
	void setForwardForce(float force);
	void setJumpHeight(float force);
	void setGrounded(bool isGrounded);
};
#endif