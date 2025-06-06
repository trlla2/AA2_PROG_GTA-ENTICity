#include "Config.h"

Config::Config(std::string fileName) {
	// Read de config.txt file
	std::vector<int> values;

	std::ifstream archive(fileName);

	if (!archive.is_open()) {
		std::cout << "ERROR: NO CONFIG FILE";
		return;
	}

	std::string line;
	// read line by line
	while (std::getline(archive, line)) {
		std::stringstream ss(line);
		std::string token;

		// read the values 
		while (std::getline(ss, token, ';')) {
			if (!token.empty()) {  // Ignorar tokens vacíos
				values.push_back(stoi(token));
			}
		}
	}
	archive.close();

	if (values.size() < 11) {
		std::cout << "ERROR: NOT ENOUGH VALUES (NEED 11 VALUES)" << std::endl;
		return;
	}

	// assign values
	width = values[0];
	height = values[1];
	
	numPedastriansSantos = values[2];
	moneyToGoSanFierro = values[3];
	maxMoneyDropPedastriansSantos = values[4];

	numPedastriansSanFierro = values[5];
	moneyToGoVenturas = values[6];
	maxMoneyDropPedastriansSanFerro = values[7];
	
	numCarsLosSantos = values[8];     
	numCarsSanFierro = values[9];      
	numCarsLasVenturas = values[10];
	
	pedestrianHealthLosSantos = values[11];
	pedestrianHealthSanFierro = values[12];
	
	damageToPlayerLosSantos = values[13];
	damageToPlayerSanFierro = values[14];
	
	playerAttackPower = values[15];
	playerMaxHealth = values[16];
}
