#include "Map.h"
#include "Car.h"
#include "Player.h" // incluyo player para evitar dependencia circular
#include "BigSmoke.h"

Map::Map(Player* player, int h, int w, int numPeatonesLS, int numPeatonesSF, int maxMoneyDropLS, int maxMoneyDropSF, int numCarsLS, int numCarsSF, int numCarsLV, int peatonDMGLS, int peatonDMGSF, int peatonHPLS, int peatonHPSF) {

	height = h;
	width = w;
	numPeatonesLosSantos = numPeatonesLS;
	numPeatonesSanFierro = numPeatonesSF;
	numCarsLosSantos = numCarsLS;
	numCarsSanFierro = numCarsSF;
	numCarsLasVenturas = numCarsLV;

	seeDistance = 10;

	playerRef = player; // get player ref

	moneyForToll1 = 100;
	moneyForToll2 = 500;
	alreadyPassedToll1 = false;
	alreadyPassedToll2 = false;


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
				box[i][j] = 'W';
			}
			else if (j == width / 3) { // Los Santos San Fierro diviision
				if (i == toll1)
					box[i][j] = '.';
				else
					box[i][j] = 'W';
			}
			else if (j == 2 * width / 3) { //San Fierro  diviision
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
	Position playerPos = playerRef->GetPosition();
	box[playerPos.x][playerPos.y] = 'J';

	// Create Cars
	carsLosSantos = new Car[numCarsLosSantos];
	Car* tempCar;
	for (int i = 0; i < numCarsLosSantos; i++) {
		tempCar = new Car(playerRef, this, Zone::LOS_SANTOS);
		if (carsLosSantos != nullptr) {
			carsLosSantos[i] = *tempCar;
		}
	}

	carsSanFierro = new Car[numCarsSanFierro];
	for (int i = 0; i < numCarsSanFierro; i++) {
		tempCar = new Car(playerRef, this, Zone::SAN_FIERRO);
		if (carsSanFierro != nullptr) {
			carsSanFierro[i] = *tempCar;
		}
	}

	carsLasVenturas = new Car[numCarsLasVenturas];
	for (int i = 0; i < numCarsLasVenturas; i++) {
		tempCar = new Car(playerRef, this, Zone::LAS_VENTURAS);
		if (carsLasVenturas != nullptr) {
			carsLasVenturas[i] = *tempCar;
		}
	}

	// Create peatones
	peatonesLosSantos = new Peaton[numPeatonesLosSantos];
	Peaton* tempPeaton;
	for (int i = 0; i < numPeatonesLosSantos; i++) {
		tempPeaton = new Peaton(playerRef, this, Zone::LOS_SANTOS, maxMoneyDropLS, peatonDMGLS, peatonHPLS);

		if (peatonesLosSantos != nullptr) {
			peatonesLosSantos[i] = *tempPeaton;
		}
	}

	peatonesSanFierro = new Peaton[numPeatonesSanFierro];
	for (int i = 0; i < numPeatonesSanFierro; i++) {
		tempPeaton = new Peaton(playerRef, this, Zone::SAN_FIERRO, maxMoneyDropSF, peatonDMGSF, peatonHPSF);

		if (peatonesSanFierro != nullptr) {
			peatonesSanFierro[i] = *tempPeaton;
		}
	}

	// Create BigSmoke 
	bigSmoke = new BigSmoke(playerRef, this);

	moneyValues = new int* [height];
	for (int i = 0; i < height; i++) {
		moneyValues[i] = new int[width](); // Inicializar a 0
	}
}

bool Map::checkNewPlayerPosition(Position newPos) {
	
	if (box[newPos.x][newPos.y] == 'W' ||
		box[newPos.x][newPos.y] == 'P' ||
		box[newPos.x][newPos.y] == 'C' ||
		box[newPos.x][newPos.y] == 'B') {
		return false;
	}

	Position playerPos = playerRef->GetPosition();
	box[playerPos.x][playerPos.y] = '.'; // clear old position box

	box[newPos.x][newPos.y] = 'J'; // print new position box

	Position toll1Pos(toll1, width / 3);
	Position toll2Pos(toll2, 2 * width / 3);


	if (newPos == toll1Pos && !alreadyPassedToll1) {
		if (playerRef->GetPlayerMoney() - moneyForToll1 < 0) {
			playerRef->SetIsArrested();
		}
		else {
			playerRef->RestPlayerMoney(moneyForToll1);
			alreadyPassedToll1 = true;
		}
	}
	else if (newPos == toll2Pos && !alreadyPassedToll2) {
		if (playerRef->GetPlayerMoney() - moneyForToll2 < 0) {
			playerRef->SetIsArrested();
		}
		else {
			playerRef->RestPlayerMoney(moneyForToll2);
			alreadyPassedToll2 = true;
		}
	}

	return true;
}

bool Map::checkNewCarPosition(Position newPos) {
	
	if (box[newPos.x][newPos.y] == 'W' ||
		box[newPos.x][newPos.y] == 'C' ||
		box[newPos.x][newPos.y] == 'B') {
		return false;
	}

	Position toll1Pos(toll1, width / 3);
	Position toll2Pos(toll2, 2 * width / 3);


	if (newPos == toll1Pos && !alreadyPassedToll1) {
		if (playerRef->GetPlayerMoney() - moneyForToll1 < 0) {
			playerRef->SetIsArrested();
		}
		else {
			playerRef->RestPlayerMoney(moneyForToll1);
			alreadyPassedToll1 = true;
		}
	}
	else if (newPos == toll2Pos && !alreadyPassedToll2) {
		if (playerRef->GetPlayerMoney() - moneyForToll2 < 0) {
			playerRef->SetIsArrested();
		}
		else {
			playerRef->RestPlayerMoney(moneyForToll2);
			alreadyPassedToll2 = true;
		}
	}

	return true;
}

Car* Map::FindNearestCar(Position playerPos) {
	std::vector<Car*> nearbyCars;

	for (int i = 0; i < numCarsLosSantos; i++) {
		if (!carsLosSantos[i].IsPlayerDriving()) {
			Position carPos = carsLosSantos[i].GetPosition();
			int distX = abs(playerPos.x - carPos.x);
			int distY = abs(playerPos.y - carPos.y);
			if (distX <= 1 && distY <= 1) {
				nearbyCars.push_back(&carsLosSantos[i]);
			}
		}
	}

	for (int i = 0; i < numCarsSanFierro; i++) {
		if (!carsSanFierro[i].IsPlayerDriving()) {
			Position carPos = carsSanFierro[i].GetPosition();
			int distX = abs(playerPos.x - carPos.x);
			int distY = abs(playerPos.y - carPos.y);
			if (distX <= 1 && distY <= 1) {
				nearbyCars.push_back(&carsSanFierro[i]);
			}
		}
	}

	for (int i = 0; i < numCarsLasVenturas; i++) {
		if (!carsLasVenturas[i].IsPlayerDriving()) {
			Position carPos = carsLasVenturas[i].GetPosition();
			int distX = abs(playerPos.x - carPos.x);
			int distY = abs(playerPos.y - carPos.y);
			if (distX <= 1 && distY <= 1) {
				nearbyCars.push_back(&carsLasVenturas[i]);
			}
		}
	}

	if (!nearbyCars.empty()) {
		int randomIndex = rand() % nearbyCars.size();
		nearbyCars[randomIndex]->SetPlayerDriving(true);
		return nearbyCars[randomIndex];
	}

	return nullptr;
}

void Map::HandleCarPedestrianCollision(Position carPos) {
	if (box[carPos.x][carPos.y] == 'P') {
		Peaton* hitPedestrian = nullptr;
		int maxMoneyDrop = 0;

		for (int i = 0; i < numPeatonesLosSantos; i++) {
			if (peatonesLosSantos[i].GetPosition() == carPos) {
				hitPedestrian = &peatonesLosSantos[i];
				maxMoneyDrop = 10;
				break;
			}
		}


		if (hitPedestrian == nullptr) {
			for (int i = 0; i < numPeatonesSanFierro; i++) {
				if (peatonesSanFierro[i].GetPosition() == carPos) {
					hitPedestrian = &peatonesSanFierro[i];
					maxMoneyDrop = 16;
					break;
				}
			}
		}

		if (hitPedestrian != nullptr) {
			box[carPos.x][carPos.y] = '.';

			int directions[8][2] = { {-1,-1}, {-1,0}, {-1,1}, {0,-1}, {0,1}, {1,-1}, {1,0}, {1,1} };
			bool moneyPlaced = false;

			for (int i = 0; i < 8 && !moneyPlaced; i++) {
				int newX = carPos.x + directions[i][0];
				int newY = carPos.y + directions[i][1];

				if (newX >= 0 && newX < height && newY >= 0 && newY < width && box[newX][newY] == '.') {
					int moneyValue = rand() % maxMoneyDrop + 1;
					box[newX][newY] = '$';
					moneyValues[newX][newY] = moneyValue;
					moneyPlaced = true;
				}
			}

			if (!moneyPlaced) {
				int moneyValue = rand() % maxMoneyDrop + 1;
				box[carPos.x][carPos.y] = '$';
				moneyValues[carPos.x][carPos.y] = moneyValue;
			}

			hitPedestrian->Respawn();
		}
	}
}


bool Map::SetNewPeatonPosition(Position newPos, Peaton* peaton)
{
	if (box[newPos.x][newPos.y] == 'W' ||
		box[newPos.x][newPos.y] == 'J' ||
		box[newPos.x][newPos.y] == 'P' ||
		box[newPos.x][newPos.y] == 'C' ||
		box[newPos.x][newPos.y] == 'B' ||
		newPos.y > (2 * getWidth())) {
		return false;
	}

	Position peatonPos = peaton->GetPosition();
	box[peatonPos.x][peatonPos.y] = '.'; // clear old position box

	box[newPos.x][newPos.y] = 'P'; // print new position box

	return true;
}

void Map::printMap() {
	
	if (!playerRef->IsInCar()) {
		Position playerPos = playerRef->GetPosition();
		box[playerPos.x][playerPos.y] = 'J';
	}
	else {
		Position carPos = playerRef->GetCurrentCar()->GetPosition();
		box[carPos.x][carPos.y] = 'C';
	}

	for (int i = 0; i < numPeatonesLosSantos; i++) {
		Position peatonPos = peatonesLosSantos[i].GetPosition();
		if (box[peatonPos.x][peatonPos.y] == '.') {
			box[peatonPos.x][peatonPos.y] = 'P';
		}
	}

	for (int i = 0; i < numPeatonesSanFierro; i++) {
		Position peatonPos = peatonesSanFierro[i].GetPosition();
		if (box[peatonPos.x][peatonPos.y] == '.') {
			box[peatonPos.x][peatonPos.y] = 'P';
		}
	}

	if (bigSmoke != nullptr && bigSmoke->IsAlive()) {
		Position bigSmokePos = bigSmoke->GetPosition();
		if (box[bigSmokePos.x][bigSmokePos.y] == '.') {
			box[bigSmokePos.x][bigSmokePos.y] = 'B';
		}
	}

	Position playerPos = playerRef->IsInCar() ? playerRef->GetCurrentCar()->GetPosition() : playerRef->GetPosition();
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

	std::cout << "\nDinero: $" << playerRef->GetPlayerMoney() << std::endl;

	if (playerRef->IsInCar()) {
		std::cout << "Driving - Press E to exit the car" << std::endl;
	}
}


int Map::getHeight() const { return height; }
int Map::getWidth() const { return width; }
char** Map::getBox() const { return box; }

int Map::GetNumPeatonesLosSantos() const { return numPeatonesLosSantos; }

int Map::GetNumPeatonesSanFierro() const { return numPeatonesSanFierro; }

Peaton* Map::GetPeatonesLosSantos() const { return peatonesLosSantos; }

Peaton* Map::GetPeatonesSanFierro() const { return peatonesSanFierro; }

int Map::GetNumCarsLosSantos() const { return numCarsLosSantos; }
int Map::GetNumCarsSanFierro() const { return numCarsSanFierro; }
int Map::GetNumCarsLasVenturas() const { return numCarsLasVenturas; }
Car* Map::GetCarsLosSantos() const { return carsLosSantos; }
Car* Map::GetCarsSanFierro() const { return carsSanFierro; }
Car* Map::GetCarsLasVenturas() const { return carsLasVenturas; }

BigSmoke* Map::GetBigSmoke() const { return bigSmoke; }

int Map::CollectMoney(Position pos) {
	if (box[pos.x][pos.y] == '$') {
		int value = moneyValues[pos.x][pos.y];
		moneyValues[pos.x][pos.y] = 0; // Resetear valor
		box[pos.x][pos.y] = '.'; // Quitar símbolo
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

	if (bigSmoke != nullptr) {
		delete bigSmoke;
	}
}