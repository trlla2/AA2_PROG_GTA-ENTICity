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

	// Generar nuevo peatón
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
	if (playerRef->getPosition().x != this->pos.x + 1 && playerRef->getPosition().y != this->pos.y + 1 ||
		playerRef->getPosition().x != this->pos.x + 1 && playerRef->getPosition().y != this->pos.y - 1 ||
		playerRef->getPosition().x != this->pos.x - 1 && playerRef->getPosition().y != this->pos.y + 1 ||
		playerRef->getPosition().x != this->pos.x - 1 && playerRef->getPosition().y != this->pos.y - 1 ||
		playerRef->getPosition().x != this->pos.x && playerRef->getPosition().y != this->pos.y - 1 || 
		playerRef->getPosition().x != this->pos.x && playerRef->getPosition().y != this->pos.y + 1 || 
		playerRef->getPosition().x != this->pos.x - 1 && playerRef->getPosition().y != this->pos.y || 
		playerRef->getPosition().x != this->pos.x + 1 && playerRef->getPosition().y != this->pos.y )
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

	}
	
}

void Peaton::SetPeatonPos(Position p)
{
	pos = p;
}
