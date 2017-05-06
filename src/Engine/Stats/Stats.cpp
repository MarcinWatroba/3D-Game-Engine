#include <Engine\Stats\Stats.h>

Stats::Stats(float inhealth,float inammo,float inmass, bool ingravity)
{
	health = inhealth;
	ammo = inammo;
	mass = inmass;
	gravity = ingravity;
}
Stats::~Stats()
{

}
Stats::Stats(const Stats &stat)
{
	health = stat.health;
	ammo = stat.ammo;
	mass = stat.mass;
	gravity = stat.gravity;
}
Stats::Stats(float inhealth, float inammo, float inmass, bool ingravity, glm::vec3 in_Path1, glm::vec3 in_Path2)
{
	health = inhealth;
	ammo = inammo;
	mass = inmass;
	gravity = ingravity;
	path1 = in_Path1;
	path2 = in_Path2;
}