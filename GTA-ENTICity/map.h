#pragma once
#include <iostream>
#include <vector>
#include "Position.h"
#include "Utils.h"
#include "Peaton.h"
#include "Money.h"
#include "Zones.h"

class Player; // declaracion anticipada para evitar dependencia circular
class Peaton;
class Car;

class Map
{
private:
	int height;
	int width;
	int numPeatonesLosSantos;
	int numPeatonesSanFierro;
	int numCarsLosSantos;
	int numCarsSanFierro;
	int numCarsLasVenturas;
	// Boxes can be: W = wall, . = Empty, J = Player(CJ), P = Pedestrians, M = Money
	char** box; 

	int toll1;
	int toll2;
	Peaton* peatonesLosSantos;
	Peaton* peatonesSanFierro;
	Car* carsLosSantos;
	Car* carsSanFierro;
	Car* carsLasVenturas;
	int** moneyValues; // Matriz de valores del dinero

	Player* playerRef;

	int seeDistance;
public:
	Map(Player* player, int h, int w , int numPeatonesSantos, int numPeatonesFierro, int maxMoneyDropLS, int maxMoneyDropSF, int numCarsLS, int numCarsSF, int numCarsLV);
	 
	bool checkNewPlayerPosition(Position newPos);
	bool checkNewCarPosition(Position newPos);
	Car* FindNearestCar(Position playerPos);
	void ExitCar();
	void HandleCarPedestrianCollision(Position carPos);
	bool SetNewPeatonPosition(Position newPos, Peaton* peaton);
	void printMap();
	int getHeight() const;
	int getWidth() const;
	char** getBox() const;
	int GetNumPeatonesLosSantos() const;
	int GetNumPeatonesSanFierro()const;
	Peaton* GetPeatonesLosSantos() const;
	Peaton* GetPeatonesSanFierro()const;
	int GetNumCarsLosSantos() const;
	int GetNumCarsSanFierro() const;
	int GetNumCarsLasVenturas() const;
	Car* GetCarsLosSantos() const;
	Car* GetCarsSanFierro() const;
	Car* GetCarsLasVenturas() const;
	
	int CollectMoney(Position pos); 
	int** GetMoneyValues() const;
	~Map();
};



