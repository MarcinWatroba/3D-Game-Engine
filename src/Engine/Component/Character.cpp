#include <Engine\Component\Character.h>

void Character::setHealth(float temp)
{
	health = temp;
}

void Character::setNumberOfBullets(float temp)
{
	numberOfBullets = temp;
}

void Character::loseLife()
{
	health--;
}

void Character::gainLife(float temp)
{
	health += temp;
}

void Character::loseBullets()
{
	numberOfBullets--;
}

void Character::gainBullets(float temp)
{
	numberOfBullets += temp;
}