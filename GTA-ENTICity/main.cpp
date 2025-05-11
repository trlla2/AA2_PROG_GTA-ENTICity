#include "map.h"
#include "player.h"
#include "config.h"
#include <Windows.h>
#include "peaton.h"


int main() {
	// CONFIG
	srand(time(NULL)); // Generate seed for random
	Config config;
	Player* player = new Player();
	Map* map = new Map(player, config.height, config.width, config.numPedastriansSantos, config.numPedastriansSanFierro);
	Peaton* p = new Peaton(player, map);
	Position pos(4, 5);
	p->SetPeatonPos(pos);
	player->setMapRef(map);
	bool win = false;

	const int FPS = 30;

	//GAMELOOP
	while (!win)
	{
		//INPUT
		player->movement();
		//UPDATE
		//RENDER
		system("CLS");
		map->printMap();

		for (int i = 0; i < config.numPedastriansSantos; i++){
			map->GetPeatonesLosSantos()[i].MovePeaton();
		}

		for (int i = 0; i < config.numPedastriansSanFierro; i++) {
			map->GetPeatonesSanFierro()[i].MovePeaton();
		}
		//FRAME CONTROL
		Sleep(1000 / FPS);
	}
}