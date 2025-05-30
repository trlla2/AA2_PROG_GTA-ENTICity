#include "Map.h"
#include "Player.h" // incluyo player para evitar dependencia circular

Map::Map(Player* player, int h, int w, int numPeatonesLS, int numPeatonesSF, int maxMoneyDropLS, int maxMoneyDropSF) {
	
	height = h;
	width = w;
	numPeatonesLosSantos = numPeatonesLS;
	numPeatonesSanFierro = numPeatonesSF;

	seeDistance = 10;

	playerRef = player; // get player ref
	

	// Create the map boxes
	box = new char* [height];

	for (int i = 0; i < height; ++i)
	{
		box[i] = new char[width];
	}

	// gaps of the divisions 
	toll1 = GenerateClampedRandom(1, height - 2);  // avoid edges
	toll2 = GenerateClampedRandom(1, height - 2);

	// fill boxes
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			// Verify if is wall
			if (i == 0 || i == height - 1 || j == 0 || j == width - 1) {
				box[i][j] = 'W'; // Wall
			}
			else if (j == width / 3) { // Los Santos San Fierro diviison
				if( i == toll1)
					box[i][j] = '.';
				else
					box[i][j] = 'W';
			}
			else if (j == 2 * width / 3) { //San Fierro  diviison
				if (i == toll2)
					box[i][j] = '.';
				else
					box[i][j] = 'W';
			}
			else {
				box[i][j] = '.'; // Empty box
			}
		}
	}
	
	// Set Player Pos --------------------------------- Debug
	Position playerPos = playerRef->getPosition();
	box[playerPos.x][playerPos.y] = 'J';

	peatonesLosSantos = new Peaton[numPeatonesLosSantos];
	Peaton* tempPeaton;
	for (int i = 0; i < numPeatonesLosSantos; i++) {
		tempPeaton = new Peaton(playerRef, this, Zone::LOS_SANTOS, maxMoneyDropLS);

		if (peatonesLosSantos != nullptr) {
			peatonesLosSantos[i] = *tempPeaton;
		}
	}

	peatonesSanFierro = new Peaton[numPeatonesSanFierro];
	for (int i = 0; i < numPeatonesSanFierro; i++) {
		tempPeaton = new Peaton(playerRef, this, Zone::SAN_FIERRO, maxMoneyDropSF);

		if (peatonesSanFierro != nullptr) {
			peatonesSanFierro[i] = *tempPeaton;
		}
	}
	
	moneyValues = new int* [height];
	for (int i = 0; i < height; i++) {
		moneyValues[i] = new int[width](); // Inicializar a 0
	}
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

bool Map::SetNewPeatonPosition(Position newPos, Peaton *peaton)
{
	if (box[newPos.x][newPos.y] == 'W' || box[newPos.x][newPos.y] == 'J' || box[newPos.x][newPos.y] == 'P') {
		return false;
	}

	Position peatonPos = peaton->GetPosition();
	box[peatonPos.x][peatonPos.y] = '.'; // clear old position box

	box[newPos.x][newPos.y] = 'P'; // print new position box

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

	// Mostrar dinero del jugador debajo del mapa
	std::cout << "\nDinero: $" << playerRef->GetPlayerMoney() << std::endl;
}


int Map::getHeight() const { return height; }
int Map::getWidth() const { return width; }
char** Map::getBox() const { return box; }

int Map::GetNumPeatonesLosSantos() const { return numPeatonesLosSantos; }

int Map::GetNumPeatonesSanFierro() const { return numPeatonesSanFierro; }

Peaton* Map::GetPeatonesLosSantos() const { return peatonesLosSantos; }

Peaton* Map::GetPeatonesSanFierro() const { return peatonesSanFierro; }


int Map::CollectMoney(Position pos) {
	if (box[pos.x][pos.y] == '$') {
		int value = moneyValues[pos.x][pos.y];
		moneyValues[pos.x][pos.y] = 0; // Resetear valor
		box[pos.x][pos.y] = '.'; // Quitar s�mbolo
		return value;
	}
	return 0;
}

int** Map::GetMoneyValues() const { return moneyValues; }

Map::~Map() {
	for (int i = 0; i < height; i++) {
		delete[] box[i];
	}
	delete[] box;

	for (int i = 0; i < height; i++) {
		delete[] moneyValues[i];
	}
	delete[] moneyValues;
}
