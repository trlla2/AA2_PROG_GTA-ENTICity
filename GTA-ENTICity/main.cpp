#include "Map.h"
#include "Player.h"
#include "Config.h"
#include <Windows.h>
#include "Peaton.h"


int main() {
	// CONFIG
	srand(time(NULL)); // Generate seed for random
	Config config("config.txt");
	Player* player = new Player();
	Map* map = new Map(player, config.height, config.width, config.numPedastriansSantos, config.numPedastriansSanFierro, config.maxMoneyDropPedastriansSantos, config.maxMoneyDropPedastriansSanFerro, config.numCarsLosSantos, config.numCarsSanFierro, config.numCarsLasVenturas);
	
	player->setMapRef(map);
	bool win = false;

	const int FPS = 30;

	//GAMELOOP
	while (!win)
	{
		//INPUT
		player->movement();
		player->Attack();
		player->GetInCar();
		//UPDATE
		for (int i = 0; i < config.numPedastriansSantos; i++) {
			map->GetPeatonesLosSantos()[i].MovePeaton();
		}

		for (int i = 0; i < config.numPedastriansSanFierro; i++) {
			map->GetPeatonesSanFierro()[i].MovePeaton();
		}
		//RENDER
		system("CLS");
		map->printMap();

		
		//FRAME CONTROL
		Sleep(1000 / FPS);
	}
}