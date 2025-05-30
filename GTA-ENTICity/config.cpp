#include "Config.h"

Config::Config() {
	// Read de config.txt file
	std::vector<int> values;

	std::ifstream archive("config.txt");

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

	if (values.size() < 8) {
		std::cout << "ERROR: NOT ENOUGH VALUES" << std::endl;
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
}
