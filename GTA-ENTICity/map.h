#pragma once
#include <iostream>
#include "position.h"
#include "utils.h"
#include "peaton.h"

class Player; // declaracion anticipada para evitar dependencia circular
class Peaton;

class Map
{
private:
	int height;
	int width;
	// Boxes can be: W = wall, . = Empty, J = Player(CJ), P = Pedestrians, M = Money
	char** box; 

	int toll1;
	int toll2;
	Peaton* peatonesLosSantos;
	Peaton* peatonesSanFierro;

	Player* playerRef;

	int seeDistance;
public:
	Map(Player* player, int h, int w , int numPeatonesLosSantos, int numPeatonesSanFierro);
	 
	bool setNewPlayerPosition(Position newPos);
	bool SetNewPeatonPosition(Position newPos, Peaton* peaton);
	void printMap();
	int getHeight();
	int getWidth();
	char** getBox();
	Peaton* GetPeatonesLosSantos();
	Peaton* GetPeatonesSanFierro();
	~Map();
};

