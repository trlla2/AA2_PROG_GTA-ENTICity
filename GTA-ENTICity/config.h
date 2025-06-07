#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iostream>

struct Config
{
	int width;
	int height;

	int playerMaxHealth;
	int playerAttackPower;

	int toll1Cost; 
	int toll2Cost; 

	int numPedestriansLosSantos;
	int maxMoneyDropPedestriansLosSantos;
	int pedestrianHealthLosSantos;
	int damageToPlayerLosSantos;
	int numCarsLosSantos;

	int numPedestriansSanFierro;
	int maxMoneyDropPedestriansSanFierro;
	int pedestrianHealthSanFierro;
	int damageToPlayerSanFierro;
	int numCarsSanFierro;

	int numPedestriansLasVenturas;
	int maxMoneyDropPedestriansLasVenturas;
	int pedestrianHealthLasVenturas;
	int damageToPlayerLasVenturas;
	int numCarsLasVenturas;

	Config();
	Config(std::string fileName);
};