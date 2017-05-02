#ifndef CHARACTER_H
#define CHARACTER_H

#include <Engine\Component\Component.h>

class Character : public Component
{
private:
	float health = 3;
	float numberOfBullets;
public:
	Character() {}
	~Character() {}
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