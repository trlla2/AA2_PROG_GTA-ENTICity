#pragma once
#include <iostream>
#include "Position.h"
#include "Utils.h"
#include "Peaton.h"
#include "Money.h"
#include "Zones.h"

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
	int getHeight() const;
	int getWidth() const;
	char** getBox() const;
	int GetNumPeatonesLosSantos() const;
	int GetNumPeatonesSanFierro()const;
	Peaton* GetPeatonesLosSantos() const;
	Peaton* GetPeatonesSanFierro()const;
	int CollectMoney(Position pos); 
	int** GetMoneyValues() const;
	~Map();
};



