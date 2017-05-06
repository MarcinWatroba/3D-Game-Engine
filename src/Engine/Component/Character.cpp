#include <Engine\Component\Character.h>
Character::Character(std::string inType)
{
	typeOfChar = inType;
	if (typeOfChar == "")
	{
		health = 0;
		numberOfBullets = 0;
	}
	else if (typeOfChar == "Player")
	{
		health = 300;
		numberOfBullets = 100;
	}
	else if (typeOfChar == "Enemy")
	{
		health = 1;
		numberOfBullets = 300;
	}
	else if (typeOfChar == "Enemy_Big")
	{
		health = 5;
		numberOfBullets = 500;
	}
}

Character::Character(const Character &obj)
{
	
}
Character::Character(Stats * stat)
{
	health = stat->getHealth();
	numberOfBullets = stat->getAmmo();
}

std::string Character::get_Type()
{
	return "Character";
}

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