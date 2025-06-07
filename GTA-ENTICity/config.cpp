#include "Config.h"

Config::Config(){ }

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

	if (values.size() < 20) {
		std::cout << "ERROR: NOT ENOUGH VALUES (NEED 20 VALUES)" << std::endl;
		return;
	}

	// assign values
	width = values[0];
	height = values[1];

	playerMaxHealth = values[2];
	playerAttackPower = values[3];

	toll1Cost = values[4];
	toll2Cost = values[5];

	numPedestriansLosSantos = values[6];
	maxMoneyDropPedestriansLosSantos = values[7];
	pedestrianHealthLosSantos = values[8];
	damageToPlayerLosSantos = values[9];
	numCarsLosSantos = values[10];

	numPedestriansSanFierro = values[11];
	maxMoneyDropPedestriansSanFierro = values[12];
	pedestrianHealthSanFierro = values[13];
	damageToPlayerSanFierro = values[14];
	numCarsSanFierro = values[15];

	numPedestriansLasVenturas = values[16];
	maxMoneyDropPedestriansLasVenturas = values[17];
	pedestrianHealthLasVenturas = values[18];
	damageToPlayerLasVenturas = values[19];
	numCarsLasVenturas = values[20];
}
