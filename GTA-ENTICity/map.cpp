#include "map.h"
#include "Player.h" // incluyo player para evitar dependencia circular

Map::Map(Player* player) {
	// Debug ---- Aqui tendiramos que leer el "config.txt"
	height = 30;
	width = 20;
	// End Debug

	seeDistance = 10;

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
	// SeeDistance is a diagonal not a radius
	// Player has to be on the center (on the center of seeDistance)
	// printing start always will be playerPos -  seeDistance/2 or 0
	// printing ends when I and J is equal playerPos + seeDistance/2 or are equal to height and widht
	
	Position playerPos = playerRef->getPosition();
	int startI = playerPos.x - seeDistance * 0.5f;
	if (startI < 0)  startI = 0;
	
	int endI = playerPos.x + seeDistance * 0.5f;
	if (endI >= height) endI = height;

	int startJ = playerPos.y - seeDistance * 0.5f;
	if (startJ < 0)  startJ = 0;

	int endJ = playerPos.y + seeDistance * 0.5f;
	if (endJ >= width) endJ = width;

	

	for (int i = startI; i < endI; i++) {
		for (int j = startJ; j < endJ; j++) {
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
