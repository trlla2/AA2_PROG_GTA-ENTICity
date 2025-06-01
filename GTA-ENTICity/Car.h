#pragma once
#include "Position.h"
#include "Zones.h"
#include "Utils.h"

class Player;
class Map;

class Car
{
private:
	Position pos;
	bool isPlayerDriving;
	Zone zone;
	Player* playerRef;
	Map* mapRef;
public:
	Car();
	Car(Player* player, Map* map, Zone carZone);

	Position GetPosition() const;
	bool IsPlayerDriving() const;
	void SetPlayerDriving(bool driving);
	Position ExitCar();
	void SetNewPosition(Position newPos);

	
};