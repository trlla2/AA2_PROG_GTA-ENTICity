#pragma once
#include "Map.h"
#include "Player.h"
#include "Config.h"
#include <Windows.h>
#include <string>

enum Scenes { INIT, GAMEPLAY, MENU, GAMEOVER };

struct Manager
{
	Scenes actualScene;

	Config* config;
	Player* player;
	Map* map;
	bool playing;
	const int FPS = 30;
	DWORD lastTime;
	float deltaTime;
	float stateTimer;  
	int menuSelection;  // 0 = Play 1 = Exit
	bool keyPressed;    
	std::string gameOverReason;

	Manager();
	~Manager();

	void GameLoop();

	void Init();
	void Gameplay();
	void Menu();
	void GameOver();
};