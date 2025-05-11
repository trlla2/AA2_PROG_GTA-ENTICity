#pragma once
#include <Windows.h>
#include "position.h"
#include "player.h"
#include "map.h"
#include "zones.h"

//class Map;

class Peaton
{
private:
	Position pos;
	Player* playerRef;
	Map* mapRef;
	Zone zone;
	int maxMoneyDrop;


	void SetNewPosition(Position p);

public:
	Peaton();
	Peaton(Player* player, Map* map, Zone peatonZone, int maxMonDrop);
	~Peaton();
	Position GetPosition() const;
	void MovePeaton();
	bool IsNearToPlayer();
	void Respawn();
};

