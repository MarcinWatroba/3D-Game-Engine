#pragma once

class Stats
{
private:
	float health;
	float ammo;
	float mass;
	bool gravity;
public:
	Stats(float inhealth, float inammo, float inmass, bool ingravity);
	~Stats();
	Stats(const Stats &stat);
	float getHealth() { return health; }
	float getAmmo() { return ammo; }
	float getMass() { return mass; }
	bool getGravity() { return gravity; }

};