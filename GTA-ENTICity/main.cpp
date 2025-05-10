#include "map.h"
#include "player.h"
#include <Windows.h>


int main() {
	// CONFIG
	//srand(time(NULL)); // Generate seed for random
	Player* player = new Player();
	Map* map = new Map(player);
	bool win = false;

	const int FPS = 20;

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