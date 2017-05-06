#ifndef CHARACTER_H
#define CHARACTER_H

#include <Engine\Component\Component.h>

class Character : public Component
{
private:
	float health;
	float numberOfBullets;
	bool exitLevel;
	std::string typeOfChar;
public:
	Character(std::string inType = "");
	~Character() {}
	void setHealth(float temp);
	void setNumberOfBullets(float newAmmo);
	void setEndLevel(bool temp);

	void loseLife();
	void gainLife(float temp);
	void loseBullets();
	void gainBullets(float temp);

	float getHealth() { return health; }
	float getNumberOfBullets() { return numberOfBullets; }
	bool getEndLevel() { return exitLevel; }


};
#endif