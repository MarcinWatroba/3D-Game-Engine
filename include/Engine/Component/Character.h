#ifndef CHARACTER_H
#define CHARACTER_H

#include <Engine\Component\Component.h>
#include <Engine\Stats\Stats.h>

class Character : public Component
{
private:
	float health;
	float numberOfBullets;
	glm::vec3 path1;
	glm::vec3 path2;
	std::string typeOfChar;
	bool endLevel = false;
public:
	Character(std::string inType = "");
	~Character() {}
	Character(const Character &obj);
	Character(Stats* stat);
	std::string get_Type();
	void setHealth(float temp);
	void setNumberOfBullets(float newAmmo);
	void setEndLevel(bool temp);

	void loseLife();
	void gainLife(float temp);
	void loseBullets();
	void gainBullets(float temp);

	float getHealth() { return health; }
	float getNumberOfBullets() { return numberOfBullets; }
	bool getEndLevel() { return endLevel; }


};
#endif