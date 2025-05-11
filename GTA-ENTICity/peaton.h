#pragma once
#include <Windows.h>
#include "position.h"
#include "player.h"
#include "map.h"

//class Map;

class Peaton
{
private:
	Position pos;
	Player* playerRef;
	Map* mapRef;



	void SetNewPosition(Position p);

public:
	Peaton();
	Peaton(Player* player, Map* map);
	~Peaton();
	Position GetPosition() const;
	void MovePeaton();
	void SetPeatonPos(Position);
};

