#include "peaton.h"

Peaton::Peaton()
{
}

Peaton::Peaton(Player* player, Map* map)
{
	playerRef = player;
	mapRef = map;

	bool instancedPeaton = false;
	int checkPosX = 0;
	int checkPosY = 0;
	while (instancedPeaton == false) {
		checkPosY = rand() % mapRef->getWidth();
		checkPosX = rand() % mapRef->getHeight();
		
		if (mapRef->getBox()[checkPosX][checkPosY] != NULL) {
			if (mapRef->getBox()[checkPosX][checkPosY] == '.') {
				pos.x = checkPosX;
				pos.y = checkPosY;
				instancedPeaton = true;
			}
		}
		
			
	}
}

Peaton::~Peaton()
{
	// Soltar dinero

	// Generar nuevo peat�n
	bool instancedPeaton = false;
	int checkPosX = 0;
	int checkPosY = 0;
	while (instancedPeaton == false) {
		checkPosX = rand() % mapRef->getWidth();
		checkPosX = rand() % mapRef->getHeight();

		if (mapRef->getBox()[pos.x][pos.y] == '.') {
			pos.x = checkPosX;
			pos.y = checkPosY;
			instancedPeaton = true;
		}
	}
}

void Peaton::SetNewPosition(Position p)
{
	pos = p;
}



Position Peaton::GetPosition() const
{
	return pos;
}

void Peaton::MovePeaton()
{
	Position playerPos = playerRef->getPosition();
	int x = abs(playerPos.x - pos.x);
	int y = abs(playerPos.x - pos.x);

	bool shouldMove = false;

	if (x <= 1 && y <= 1)
		shouldMove = false;
	else
		shouldMove = true;

	if (shouldMove) // move 
	{
		int randomMoveDirection = rand() % 4; // 0 = up // 1 = down // 2 = left // 3 = right

		if (randomMoveDirection == 0) {
			Position newPos(pos.x, pos.y - 1);
			if (mapRef->SetNewPeatonPosition(newPos, this))
				SetNewPosition(newPos);
		}
		else if (randomMoveDirection == 1)
		{
			Position newPos(pos.x, pos.y + 1);
			if (mapRef->SetNewPeatonPosition(newPos, this))
				SetNewPosition(newPos);
		}
		else if (randomMoveDirection == 2)
		{
			Position newPos(pos.x - 1, pos.y);
			if (mapRef->SetNewPeatonPosition(newPos, this))
				SetNewPosition(newPos);
		}
		else if (randomMoveDirection == 3)
		{
			Position newPos(pos.x + 1, pos.y);
			if (mapRef->SetNewPeatonPosition(newPos, this))
				SetNewPosition(newPos);
		}
	}
	else
	{
		// stop moving
	}
	
}

void Peaton::SetPeatonPos(Position p)
{
	pos = p;
}
