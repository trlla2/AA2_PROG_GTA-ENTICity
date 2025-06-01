#include "position.h"

Position::Position() {
	x = 0;
	y = 0;
}

Position::Position(int posX, int posY) {
	x = posX;
	y = posY;
}

bool Position::operator==(const Position& other) const {
	return x == other.x && y == other.y;
}