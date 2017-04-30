#include <Engine\Physics\Physics.h>

Physics::Physics()
{
	// For jumping and normal movement, use eulerIntegration
	// For sprinting and/or driving, use RK4
}

Physics::~Physics()
{

}

float Physics::eulerIntegration(float force, float mass, float position)
{
	float timestep = 1;
	float acceleration = 0;
	float newAcceleration = 0;
	float time = 0;

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

glm::vec3 Physics::applyGravity(glm::vec3 position, float mass)
{
	// Modify y transform of passed object by -9.82f unless object is grounded
	return position;
}

void Physics::beginLoop()
{
	std::cout << "Hello user!" << std::endl;
	std::cout << "Which equation would you like to use?" << std::endl;
	std::cout << "A - Euler Integration?" << std::endl;
	std::cout << "B - SUVAT?" << std::endl;
	std::cout << "C - RK4?" << std::endl;
	std::cin >> cL;
	if (cL == 'A' || cL == 'a')
	{
		std::cout << "What is the mass of the object?" << std::endl;
		std::cin >> mass;
		std::cout << "What is the position of the object?" << std::endl;
		std::cin >> position;
		std::cout << "What is the force applied?" << std::endl;
		std::cin >> force;
		float result = eulerIntegration(force, mass, position);
		std::cout << "Using these values, the answer is " << result << std::endl << std::endl;
		system("PAUSE");

	}
	if (cL == 'B' || cL == 'b')
	{
		std::cout << "What is the acceleration of the object?" << std::endl;
		std::cin >> a;
		std::cout << "How long would you like to measure for?" << std::endl;
		std::cin >> t;
		float result = SUVAT(a, t);
		std::cout << "Using these values, the answer is " << result << std::endl << std::endl;
		system("PAUSE");
	}
	if (cL == 'C' || cL == 'c')
	{
		std::cout << "What is the position of the object?" << std::endl;
		std::cin >> stat.x;
		std::cout << "What is the velocity of the object?" << std::endl;
		std::cin >> stat.v;
		std::cout << "How long would you like to measure for?" << std::endl;
		std::cin >> t;
		RK4(stat, t, dT);
		std::cout << "Using these values, the position is " << stat.x << " and the velocity is " << stat.v << std::endl << std::endl;
		system("PAUSE");
	}
	if (cL == 'D' || cL == 'd')
	{

	}
	if (cL == 'E' || cL == 'e')
	{

	}
	exit(EXIT_SUCCESS);
}
