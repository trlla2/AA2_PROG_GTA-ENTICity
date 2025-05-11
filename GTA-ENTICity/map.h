#pragma once
#include <iostream>
#include "position.h"
#include "utils.h"
#include "peaton.h"
#include "money.h"
#include "zones.h"

class Player; // declaracion anticipada para evitar dependencia circular
class Peaton;

class Map
{
private:
	int height;
	int width;
	int numPeatonesLosSantos;
	int numPeatonesSanFierro;
	// Boxes can be: W = wall, . = Empty, J = Player(CJ), P = Pedestrians, M = Money
	char** box; 

	int toll1;
	int toll2;
	Peaton* peatonesLosSantos;
	Peaton* peatonesSanFierro;
	int** moneyValues; // Matriz de valores del dinero

	Player* playerRef;

	int seeDistance;
public:
	Map(Player* player, int h, int w , int numPeatonesSantos, int numPeatonesFierro, int maxMoneyDropLS, int maxMoneyDropSF);
	 
	bool setNewPlayerPosition(Position newPos);
	bool SetNewPeatonPosition(Position newPos, Peaton* peaton);
	void printMap();
	int getHeight();
	int getWidth();
	char** getBox();
	int GetNumPeatonesLosSantos();
	int GetNumPeatonesSanFierro();
	Peaton* GetPeatonesLosSantos();
	Peaton* GetPeatonesSanFierro();
	int CollectMoney(Position pos); 
	int** GetMoneyValues();
	~Map();
};



