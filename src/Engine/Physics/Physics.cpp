#include <Engine\Physics\Physics.h>

Physics::Physics()
{
	// For jumping and normal movement, use eulerIntegration
	// For sprinting and/or driving, use RK4
}

Physics::~Physics()
{

}

float Physics::eulerIntegration(float force, float mass, float position, bool grounded)
{
	float timestep = 1;
	float acceleration = 0;
	float newAcceleration = 0;
	float time = 0;
	//force += gravConst * mass;
	if (grounded)
	{
		gravConst = 0;
	}
	else
	{
		gravConst = -0.982f;
	}

	;
	float velocity = 0;

	while (time <= 100)
	{
		////position = position + velocity * dt;
		//acceleration = force * (timestep, position) / mass;
		//velocity = velocity + (force / mass) * dt;
		//timestep = timestep + dt;

		acceleration = force / mass;
		time += timestep;
		//position += timestep * (velocity + timestep * acceleration / 2);
		velocity += timestep * acceleration;
		//newAcceleration = force(time, position, velocity) / mass;
		//velocity += timestep * (newAcceleration - acceleration) / 2;
	}
	velocity += gravConst;
	return velocity;
}

float Physics::SUVAT(float accel, float time)
{
	float distance = glm::pow((0.5f * accel * time), 2);
	return distance;
}

void Physics::RK4(Active &state, float t, float dt)
{
	Derivative a, b, c, d;

	a = evaluate(state, t, 0.0f, Derivative());
	b = evaluate(state, t, dt*0.5f, a);
	c = evaluate(state, t, dt*0.5f, b);
	d = evaluate(state, t, dt, c);

	float dxdt = 1.0f / 6.0f * (a.dx + 2.0f*(b.dx + c.dx) + d.dx);

	float dvdt = 1.0f / 6.0f * (a.dv + 2.0f*(b.dv + c.dv) + d.dv);

	state.x = state.x + dxdt * dt;
	state.v = state.v + dvdt * dt;
}

Derivative Physics::evaluate(const Active &initial, float t, float dt, const Derivative &d)
{
	Active s;
	s.x = initial.x + d.dx*dt;
	s.v = initial.v + d.dv*dt;

	Derivative output;
	output.dx = s.v;
	output.dv = acceleration(s, t + dt);
	return output;
}

float Physics::acceleration(const Active &state, float t)
{
	const float k = 10;
	const float b = 1;
	return -k * state.x - b*state.v;
}

glm::vec3 Physics::applyGravity(glm::vec3 position, float mass, float force)
{
	return position;
}

