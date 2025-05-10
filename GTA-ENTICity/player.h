#pragma once
#include "position.h"
class player
{
private:
	enum PlayerMovement {EMPTY, UP, DOWN, LEFT, RIGHT};
	position pos;



public:
	position getPosition();
	void move();
};

