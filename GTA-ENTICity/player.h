#pragma once
#include "position.h"
#include "map.h"
#include <Windows.h>
class Player
{
private:
	enum PlayerMovement {EMPTY, UP, DOWN, LEFT, RIGHT};
	Position pos;

	Map* mapRef;

	void setNewPosition(Position newPos);

public:
	Player();
	void setMapRef(Map* map);
	void movement();
	void attack();
	Position getPosition();
};

