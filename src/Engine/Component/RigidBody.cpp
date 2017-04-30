#include <Engine\Component\RigidBody.h>

RigidBody::RigidBody()
{
	
}

RigidBody::~RigidBody()
{

}

void RigidBody::setValues(float baseMass, bool move, glm::vec3 position)
{
	mass = 10;
	moveable = move;
	centreOfMass = position;
}

void RigidBody::setPhysics(std::string iD, bool value)
{
	boolList[iD] = value;
}

void RigidBody::setForwardForce(float force)
{
	forward_Force = force;
}

void RigidBody::setJumpForce(float force)
{
	jumpForce = force;
}

void RigidBody::setJumpHeight(float force)
{
	//jumpHeight = force;
}

void RigidBody::setGrounded(bool isGrounded)
{
	grounded = isGrounded;
}

void RigidBody::update(glm::vec3 &pos)
{
	centreOfMass = pos;
	if (grounded)
	{
		velocity = phys.eulerIntegration(forward_Force, mass, pos.z);
	}
	else
	{
		if (!reachedPeak)
		{
			if (pos.y >= jumpHeight)
			{
				reachedPeak = true;
			}
			else
			{
				jumpVelocity = phys.eulerIntegration(jumpForce, mass, pos.y);
			}
			
			
		}
		else
		{
			if (pos.y <= 0)
			{
				jumpVelocity = 0;
				grounded = true;
				reachedPeak = false;
			}
			else
			{
				jumpVelocity = phys.eulerIntegration(-jumpForce, mass, pos.y);
			}
			
			
		}
		std::cout << jumpVelocity << std::endl;
	}
		
	//}
	//if (boolList["SUVAT"])
	//{
	//	// Apply SUVAT
	//}
	//if (boolList["Gravity"])
	//{
	//	if (!grounded && moveable)
	//	{
	//		pos = phys.applyGravity(pos, mass);
	//	}
	//}

}
