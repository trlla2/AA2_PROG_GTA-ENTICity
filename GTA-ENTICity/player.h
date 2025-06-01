#pragma once
#include "Position.h"
#include <Windows.h>


class Map; // declaracion anticipada para evitar dependencia circular
class Car;

class Player
{
private:
	int playerMoney = 0;
	enum PlayerMovement {EMPTY, UP, DOWN, LEFT, RIGHT};
	Position pos;
	Car* currentCar;

	Map* mapRef;

	void setNewPosition(Position newPos);

public:
	Player();
	void setMapRef(Map* map);
	void movement();
	void Attack();
	void GetInCar();
	Car* GetCurrentCar() const;
	Position GetPosition() const;
	int GetPlayerMoney() const;
};

