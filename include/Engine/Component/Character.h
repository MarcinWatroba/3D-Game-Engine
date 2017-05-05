#ifndef CHARACTER_H
#define CHARACTER_H

#include <Engine\Component\Component.h>

class Character : public Component
{
private:
	float health;
	float numberOfBullets;
	std::string typeOfChar;
public:
	Character(std::string inType = "");
	~Character() {}
	Character(const Character &obj);
	std::string get_Type();
	void setHealth(float temp);
	void setNumberOfBullets(float newAmmo);

	void loseLife();
	void gainLife(float temp);
	void loseBullets();
	void gainBullets(float temp);

	float getHealth() { return health; }
	float getNumberOfBullets() { return numberOfBullets; }


};
#endif