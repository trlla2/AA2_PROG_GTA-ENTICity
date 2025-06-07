#include "Manager.h"
#include <iostream>
#include <conio.h>

Manager::Manager() {
	config = new Config("config.txt");

	playing = true;

	lastTime = GetTickCount64();
	deltaTime = 0.0f;
	stateTimer = 0;
	menuSelection = 0;
	keyPressed = false;

	actualScene = INIT;
}

Manager::~Manager() {
	delete config;
	if (map == nullptr)
		delete map;
	if (player == nullptr)
		delete player;
}

void Manager::GameLoop() {
	while (playing)
	{
		switch (actualScene)
		{
		case INIT:
			Init();
			break;
		case GAMEPLAY:
			Gameplay();
			break;
		case MENU:
			Menu();
			break;
		case GAMEOVER:
			GameOver();
			break;
		}

		//FRAME CONTROL
		Sleep(1000 / FPS);
	}
}

void Manager::Init() {
	system("CLS");

	std::cout << "========================================" << std::endl;
	std::cout << "                                        " << std::endl;
	std::cout << "           GTA SAN ANDREAS              " << std::endl;
	std::cout << "              CLONE GAME                " << std::endl;
	std::cout << "                                        " << std::endl;
	std::cout << "========================================" << std::endl;

	DWORD currentTime = GetTickCount64();
	deltaTime = (currentTime - lastTime) / 1000.0f;
	lastTime = currentTime;
	stateTimer += deltaTime;

	if (stateTimer >= 3.0f) {
		stateTimer = 0;
		actualScene = MENU;
	}
}

void Manager::Menu() {
	system("CLS");

	std::cout << "========================================" << std::endl;
	std::cout << "              MAIN MENU                 " << std::endl;
	std::cout << "========================================" << std::endl;
	std::cout << std::endl;


	if (menuSelection == 0) {
		std::cout << " > Play Game" << std::endl;
		std::cout << "   Exit" << std::endl;
	}
	else {
		std::cout << "   Play Game" << std::endl;
		std::cout << " > Exit" << std::endl;
	}

	std::cout << std::endl;
	std::cout << "Use UP/DOWN arrows to navigate, SPACE to select" << std::endl;


	if (GetAsyncKeyState(VK_UP)) {
		if (!keyPressed) {
			menuSelection = 0; //  Play 
			keyPressed = true;
		}
	}
	else if (GetAsyncKeyState(VK_DOWN)) {
		if (!keyPressed) {
			menuSelection = 1; // Exit
			keyPressed = true;
		}
	}
	else if (GetAsyncKeyState(VK_SPACE)) {
		if (!keyPressed) {
			if (menuSelection == 0) {
				if (map == nullptr)
					delete map;
				if (player == nullptr)
					delete player;

				player = new Player(config->playerMaxHealth, config->playerAttackPower);
				map = new Map(player, config->height, config->width, config->numPedestriansLosSantos, config->numPedestriansSanFierro, config->maxMoneyDropPedestriansLosSantos, config->maxMoneyDropPedestriansSanFierro, config->numCarsLosSantos, config->numCarsSanFierro, config->numCarsLasVenturas, config->damageToPlayerLosSantos, config->damageToPlayerSanFierro, config->pedestrianHealthLosSantos, config->pedestrianHealthSanFierro);
				player->setMapRef(map);

				actualScene = GAMEPLAY;

			}
			else {
				playing = false;// Exit
			}
			keyPressed = true;
		}
	}
	else {
		keyPressed = false;
	}
}

void Manager::Gameplay() {
	//INPUT
	player->movement();
	player->Attack();
	player->GetInCar();

	//UPDATE
	// Calculate delta time
	DWORD currentTime = GetTickCount64();
	deltaTime = (currentTime - lastTime) / 1000.0f;
	lastTime = currentTime;

	for (int i = 0; i < config->numPedestriansLosSantos; i++) {
		map->GetPeatonesLosSantos()[i].MovePeaton();
		map->GetPeatonesLosSantos()[i].UpdateAttackTimer(deltaTime);
	}

	for (int i = 0; i < config->numPedestriansSanFierro; i++) {
		map->GetPeatonesSanFierro()[i].MovePeaton();
		map->GetPeatonesSanFierro()[i].UpdateAttackTimer(deltaTime);
	}
	map->GetBigSmoke()->MoveBigSmoke();
	map->GetBigSmoke()->UpdateAttackTimer(deltaTime);

	if (!player->IsAlive()) {
		player->Respawn();
	}

	// Check game over conditions
	if (!map->GetBigSmoke()->IsAlive()) {
		actualScene = GAMEOVER;
		gameOverReason = "YOU WIN";
		stateTimer = 0;
	}
	else if (player->IsArrested()) {
		actualScene = GAMEOVER;
		gameOverReason = "ARRESTED";
		stateTimer = 0;
	}
	else if (!player->IsAlive() && player->GetHealth() <= 0) {
		actualScene = GAMEOVER;
		gameOverReason = "DEAD";
		stateTimer = 0;
	}

	//RENDER
	system("CLS");
	map->printMap();
	std::cout << "Current Health: " << player->GetHealth() << std::endl;

}

void Manager::GameOver() {
	system("CLS");

	std::cout << "========================================" << std::endl;
	std::cout << "              GAME OVER                 " << std::endl;
	std::cout << "========================================" << std::endl;
	std::cout << std::endl;
	std::cout << gameOverReason << std::endl;
	std::cout << std::endl;
	std::cout << "Final Stats:" << std::endl;
	std::cout << "Health: " << player->GetHealth() << std::endl;
	std::cout << "Money: $" << player->GetPlayerMoney() << std::endl;



	DWORD currentTime = GetTickCount64();
	deltaTime = (currentTime - lastTime) / 1000.0f;
	lastTime = currentTime;
	stateTimer += deltaTime;


	if (stateTimer >= 5.0f) {
		actualScene = MENU;
	}
}