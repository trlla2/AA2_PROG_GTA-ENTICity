#pragma once
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iostream>
struct Config
{
	int height;
	int width;

	int numPedastriansSantos;
	int moneyToGoSanFierro;
	int maxMoneyDropPedastriansSantos;
	int numPedastriansSanFierro;
	int moneyToGoVenturas;
	int maxMoneyDropPedastriansSanFerro;
	int numCarsLosSantos;
	int numCarsSanFierro;
	int numCarsLasVenturas;
	int pedestrianHealthLosSantos;
	int pedestrianHealthSanFierro;
	int damageToPlayerLosSantos;
	int damageToPlayerSanFierro;

	int playerAttackPower;
	int playerMaxHealth;

	Config();
	Config(std::string fileName);
};
