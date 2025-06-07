#pragma once
#include <iostream>
#include <vector>
#include "Position.h"
#include "Utils.h"
#include "Peaton.h"
#include "Money.h"
#include "Zones.h"
#include "BigSmoke.h"


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
	int numPeatonesLasVenturas;
	int numCarsLosSantos;
	int numCarsSanFierro;
	int numCarsLasVenturas;
	// Boxes can be: W = wall, . = Empty, J = Player(CJ), P = Pedestrians, M = Money
	char** box; 

	int toll1;
	int toll2;

	int moneyForToll1;
	int moneyForToll2;

	bool alreadyPassedToll1;
	bool alreadyPassedToll2;


	Peaton* peatonesLosSantos;
	Peaton* peatonesSanFierro;
	Peaton* peatonesLasVenturas;
	Car* carsLosSantos;
	Car* carsSanFierro;
	Car* carsLasVenturas;
	BigSmoke* bigSmoke;
	int** moneyValues; // Matriz de valores del dinero

	

	Player* playerRef;

	int seeDistance;
public:
	Map(Player* player, int h, int w, int numPeatonesLS, int numPeatonesSF, int numPeatonesLV, int maxMoneyDropLS, int maxMoneyDropSF, int maxMoneyDropLV, int numCarsLS, int numCarsSF, int numCarsLV, int peatonDMGLS, int peatonDMGSF, int peatonDMGLV, int peatonHPLS, int peatonHPSF, int peatonHPLV, int toll1Cost, int toll2Cost);
	 
	bool CheckNewPlayerPosition(Position newPos);
	bool CheckNewCarPosition(Position newPos);
	Car* FindNearestCar(Position playerPos);
	void HandleCarPedestrianCollision(Position carPos);
	bool SetNewPeatonPosition(Position newPos, Peaton* peaton);
	void PrintMap();
	int GetHeight() const;
	int GetWidth() const;
	char** GetBox() const;
	int GetNumPeatonesLosSantos() const;
	int GetNumPeatonesSanFierro()const;
	int GetNumPeatonesLasVenturas() const;
	Peaton* GetPeatonesLosSantos() const;
	Peaton* GetPeatonesSanFierro()const;
	Peaton* GetPeatonesLasVenturas() const;
	int GetNumCarsLosSantos() const;
	int GetNumCarsSanFierro() const;
	int GetNumCarsLasVenturas() const;
	Car* GetCarsLosSantos() const;
	Car* GetCarsSanFierro() const;
	Car* GetCarsLasVenturas() const;
	BigSmoke* GetBigSmoke() const;

	int CollectMoney(Position pos); 
	int** GetMoneyValues() const;
	~Map();
};



