#include "peaton.h"

Peaton::Peaton(Player* player, Map* map)
{
	playerRef = player;
	mapRef = map;

	pos.x = rand() % mapRef->getWidth();
	//pos.y = rand() % map
}

Peaton::~Peaton()
{
	// Generar nuevo peat�n
}

Position Peaton::GetPosition()
{
	return pos;
}
