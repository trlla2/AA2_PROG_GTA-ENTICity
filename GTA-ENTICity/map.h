#pragma once
#include "player.h"

class Map
{
private:
	int height;
	int witdth;

	int seeDistance;
	Player* player;  
public:
	Map();
	
	void printMap();
};

