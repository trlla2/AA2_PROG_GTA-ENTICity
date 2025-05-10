#include "map.h"
#include "player.h"
#include "config.h"
#include <Windows.h>


int main() {
	// CONFIG
	//srand(time(NULL)); // Generate seed for random
	Config config;
	Player* player = new Player();
	Map* map = new Map(player, config.height, config.width);
	player->setMapRef(map);
	bool win = false;

	const int FPS = 60;

	//GAMELOOP
	while (!win)
	{
		//INPUT
		player->movement();
		//UPDATE
		//RENDER
		system("CLS");
		map->printMap();
		//FRAME CONTROL
		Sleep(1000 / FPS);
	}
}