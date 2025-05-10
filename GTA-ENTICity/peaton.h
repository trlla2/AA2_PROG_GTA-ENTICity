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
	void SetNewPosition(Position p);

public:
	Position GetPosition() const;
	void MovePeaton();
};

