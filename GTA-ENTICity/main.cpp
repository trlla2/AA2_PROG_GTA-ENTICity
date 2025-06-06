#include "Map.h"
#include "Player.h"
#include "Config.h"
#include <Windows.h>



int main() {
	// CONFIG
	srand(time(NULL)); // Generate seed for random
	Config config("config.txt");
	Player* player = new Player(config.playerMaxHealth, config.playerAttackPower);
	Map* map = new Map(player, config.height, config.width, config.numPedastriansSantos, config.numPedastriansSanFierro, config.maxMoneyDropPedastriansSantos, config.maxMoneyDropPedastriansSanFerro, config.numCarsLosSantos, config.numCarsSanFierro, config.numCarsLasVenturas, config.damageToPlayerLosSantos, config.damageToPlayerSanFierro, config.pedestrianHealthLosSantos, config.pedestrianHealthSanFierro);
	
	player->setMapRef(map);
	bool playing = false;

	const int FPS = 30;

	DWORD lastTime = GetTickCount64();
	float deltaTime = 0.0f;

	//GAMELOOP
	while (!playing)
	{
		//INPUT
		player->movement();
		player->Attack();
		player->GetInCar();
		//UPDATE
		// Calculate delta time
		DWORD currentTime = GetTickCount64();
		deltaTime = (currentTime - lastTime) / 1000.0f;
		lastTime = currentTime;

		for (int i = 0; i < config.numPedastriansSantos; i++) {
			map->GetPeatonesLosSantos()[i].MovePeaton();
			map->GetPeatonesLosSantos()[i].UpdateAttackTimer(deltaTime);
		}

		for (int i = 0; i < config.numPedastriansSanFierro; i++) {
			map->GetPeatonesSanFierro()[i].MovePeaton();
			map->GetPeatonesSanFierro()[i].UpdateAttackTimer(deltaTime);
		}
		map->GetBigSmoke()->MoveBigSmoke();
		map->GetBigSmoke()->UpdateAttackTimer(deltaTime);

		if (!player->IsAlive()) {
			player->Respawn();
		}

		if (map->GetBigSmoke()->IsAlive()) {
			playing = true;
		}

		//RENDER
		system("CLS");
		map->printMap();
		std::cout << "Current Health: " << player->GetHealth() << std::endl;
		std::cout << map->GetBigSmoke()->IsAlive();

		
		//FRAME CONTROL
		Sleep(1000 / FPS);
	}
}