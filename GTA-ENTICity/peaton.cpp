#include "peaton.h"

Peaton::Peaton(Player* player, Map* map)
{
	playerRef = player;
	mapRef = map;

	//pos.x = rand() % 
	//pos.y = rand() %
}

Peaton::~Peaton()
{
	// Generar nuevo peat�n
}

Position Peaton::GetPosition()
{
	return pos;
}
