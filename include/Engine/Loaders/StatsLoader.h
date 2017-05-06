#pragma once
#include <Engine\Stats\Stats.h>
#include <map>
#include <TinyXML2\tinyxml2.h>
#include <iostream>
#include <glm\glm.hpp>

class StatsLoader
{
private:
	std::map<std::string, Stats*> statsList;
public:
	StatsLoader(const char * pc_FileName_In);
	~StatsLoader();
	Stats* get_Stat(std::string temp);
};