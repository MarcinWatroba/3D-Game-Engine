#include <Engine\Component\Character.h>
Character::Character(std::string inType)
{

}

Character::Character(const Character &obj)
{
	health = obj.health;
	numberOfBullets = obj.numberOfBullets;
}
Character::Character(Stats * stat)
{
	health = stat->getHealth();
	numberOfBullets = stat->getAmmo();
	if (stat->getPath1() != glm::vec3(0, 0, 0))
	{
		path1 = stat->getPath1();
		path2 = stat->getPath2();
	}	
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

void Character::setEndLevel(bool temp)
{
	endLevel = temp;
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