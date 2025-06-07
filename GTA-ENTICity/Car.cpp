#include "Car.h"
#include "Map.h"
#include "Player.h"


Car::Car() {
	pos.x = 0;
	pos.y = 0;

	isPlayerDriving = false;
	zone = Zone::LOS_SANTOS;
	playerRef = nullptr;
	mapRef = nullptr;
}

Car::Car(Player* player, Map* map, Zone carZone) {
	playerRef = player;
	mapRef = map;
	zone = carZone;
	isPlayerDriving = false;

	// Find empty position to spawn the car
	int minY = 0;
	int maxY = 0;

	switch (zone)
	{
	case Zone::LOS_SANTOS:
		minY = 1;
		maxY = (mapRef->GetWidth() / 3) - 1;
		break;
	case Zone::SAN_FIERRO:
		minY = (mapRef->GetWidth() / 3) + 1;
		maxY =  2 * (mapRef->GetWidth() / 3) - 1;
		break;
	case Zone::LAS_VENTURAS:
		minY = 2 * (mapRef->GetWidth() / 3) + 1;
		maxY = mapRef->GetWidth() - 2;
		break;
	default:// if there is no zone spawn on losSantos
		minY = 1;
		maxY = (mapRef->GetWidth() / 3) - 1;
		break;
	}

	bool carPlaced = false;
	while (!carPlaced) {
		int checkPosX = GenerateClampedRandom(1, mapRef->GetHeight() - 2);
		int checkPosY = GenerateClampedRandom(minY, maxY);

		if (mapRef->GetBox()[checkPosX][checkPosY] == '.') {
			pos.x = checkPosX;
			pos.y = checkPosY;
			mapRef->GetBox()[pos.x][pos.y] = 'C';
			carPlaced = true;
		}
	}
}

Position Car::ExitCar()
{
	if (!isPlayerDriving) {
		return Position(-1, -1); // Posición inválida
	}

	int directions[8][2] = { {-1,-1}, {-1,0}, {-1,1}, {0,-1}, {0,1}, {1,-1}, {1,0}, {1,1} };

	for (int i = 0; i < 8; i++) {
		int newX = pos.x + directions[i][0];
		int newY = pos.y + directions[i][1];

		if (newX >= 0 && newX < mapRef->GetHeight() && newY >= 0 && newY < mapRef->GetWidth() && mapRef->GetBox()[newX][newY] == '.') {

			isPlayerDriving = false;
			mapRef->GetBox()[pos.x][pos.y] = 'C';
			return Position(newX, newY);
		}
	}

	return Position(-1, -1);
}

void Car::SetNewPosition(Position newPos) {
	if (mapRef->CheckNewCarPosition(newPos)) {
		mapRef->GetBox()[pos.x][pos.y] = '.';
		pos = newPos;
		mapRef->GetBox()[pos.x][pos.y] = 'C';
	}
}

Position Car::GetPosition() const { return pos; }

bool Car::IsPlayerDriving() const { return isPlayerDriving; }

void Car::SetPlayerDriving(bool driving) { isPlayerDriving = driving; }
