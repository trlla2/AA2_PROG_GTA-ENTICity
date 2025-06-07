#include "Manager.h"



int main() {
	// CONFIG
	srand(time(NULL)); // Generate seed for random
	Manager manager;

	manager.GameLoop();
}