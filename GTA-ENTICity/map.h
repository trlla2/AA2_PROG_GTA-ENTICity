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
	char** box; // Boxes can be: W = wall, . = Empty, J = Player(CJ), P = Pedestrians 

	Player* playerRef;

	int seeDistance;
public:
	Map(Player* playerRef);
	 
	bool setNewPlayerPosition(Position newPos);
	void printMap();

	~Map();
};

