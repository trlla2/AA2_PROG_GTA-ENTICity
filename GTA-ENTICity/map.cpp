#include "map.h"
#include "Player.h" // incluyo player para evitar dependencia circular

Map::Map(Player* player) {
	// Debug ---- Aqui tendiramos que leer el "config.txt"
	height = 30;
	width = 20;
	// End Debug

	seeDistance = 15;

	playerRef = player; // get player ref

	// Create the map boxes
	box = new char* [height];

	for (int i = 0; i < height; ++i)
	{
		box[i] = new char[width];
	}


	// fill boxes
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			// Verify if is wall
			if (i == 0 || i == height - 1 || j == 0 || j == width - 1) {
				box[i][j] = 'W'; // Wall
			}
			else {
				box[i][j] = '.'; // Empty box
			}
		}
	}
	
	// Set Player Pos --------------------------------- Debug
	Position playerPos = playerRef->getPosition();
	box[playerPos.x][playerPos.y] = 'J';
	

}

bool Map::setNewPlayerPosition(Position newPosition){
	if (box[newPosition.x][newPosition.y] == 'W' || box[newPosition.x][newPosition.y] == 'P') {
		return false;
	}

	Position playerPos = playerRef->getPosition();
	box[playerPos.x][playerPos.y] = '.'; // clear old position box

	box[newPosition.x][newPosition.y] = 'J'; // print new position box
	
	return true;
}

void Map::printMap() {
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			std::cout << box[i][j];
		}
		std::cout << std::endl;
	}
}

Map::~Map() {
	for (int i = 0; i < height; i++) {
		delete[] box[i];
	}
	delete[] box;
}
