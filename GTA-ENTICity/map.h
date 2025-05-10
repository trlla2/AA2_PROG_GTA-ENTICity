#pragma once
#include <iostream>
#include "player.h"
#include "position.h"
#include "utils.h"

class Map
{
private:
	int height;
	int width;
	char** box; // Boxes can be: W = wall, . = Empty, C = Player(CJ), P = Pedestrians 

	Player* playerRef;

	int seeDistance;
public:
	Map(Player* playerRef);
	 
	bool setNewPlayerPosition(Position newPos);
	void printMap();

	~Map();
};

