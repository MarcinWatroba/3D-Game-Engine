#ifndef PHYSICS_H
#define PHYSICS_H

#define GRAVITY = 9.8f;


#include <glm\glm.hpp>
#include <iostream>
#include <string>
#include <map>

struct Active
{
	float x;      // position
	float v;      // velocity
};

struct Derivative
{
	float dx;      // dx/dt = velocity
	float dv;      // dv/dt = acceleration
};


class Physics
{
private:
	int iNum;
	char cL;
	float force;
	float mass;
	float position;
	float a;
	float t;
	float dT = 60;
	Active stat;
public:
	Physics();
	~Physics();
	void RK4(Active &state, float t, float dt);
	Derivative evaluate(const Active &initial, float t, float dt, const Derivative &d);
	float eulerIntegration(float force, float mass, float position);
	float SUVAT(float accel, float time);
	float acceleration(const Active &state, float t);
	glm::vec3 applyGravity(glm::vec3 position, float mass);
	void beginLoop();
};

#endif