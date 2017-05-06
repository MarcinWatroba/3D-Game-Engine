#pragma once

#include <glm\glm.hpp>

class Stats
{
private:
	float health;
	float ammo;
	float mass;
	bool gravity;
	glm::vec3 path1 = glm::vec3(0,0,0);
	glm::vec3 path2 = glm::vec3(0, 0, 0);
public:
	Stats(float inhealth, float inammo, float inmass, bool ingravity);
	~Stats();
	Stats(const Stats &stat);
	Stats(float inhealth, float inammo, float inmass, bool ingravity, glm::vec3 in_Path1, glm::vec3 in_Path2);
	float getHealth() { return health; }
	float getAmmo() { return ammo; }
	float getMass() { return mass; }
	bool getGravity() { return gravity; }
	glm::vec3 getPath1() { return path1; }
	glm::vec3 getPath2() { return path2; }

};