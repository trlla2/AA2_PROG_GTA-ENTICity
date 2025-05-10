#pragma once
#include <iostream>
#include "position.h"
#include "utils.h"

class Player; // declaracion anticipada para evitar dependencia circular

class Map
{
private:
	int height;
	int width;
	// Boxes can be: W = wall, . = Empty, J = Player(CJ), P = Pedestrians, M = Money
	char** box; 

	Player* playerRef;

	int seeDistance;
public:
	Map(Player* player);
	 
	bool setNewPlayerPosition(Position newPos);
	void printMap();
	int getHeight();
	int getWidth();
	char** getBox();
	~Map();
};

