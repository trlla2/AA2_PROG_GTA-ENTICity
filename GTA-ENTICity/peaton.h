#pragma once
#include <Windows.h>
#include "position.h"
#include "player.h"
#include "map.h"

class Peaton
{
private:
	Position pos;
	Player* playerRef;
	Map* mapRef;

	Peaton(Player* player, Map* map);
	~Peaton();

public:
	Position GetPosition();
};

