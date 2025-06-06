#pragma once
#include "Position.h"
#include <Windows.h>


class Map; // declaracion anticipada para evitar dependencia circular
class Car;

class Player
{
private:
	int playerMoney = 0;
	int health;
	int maxHealth;
	int attackPower;
	enum PlayerMovement {EMPTY, UP, DOWN, LEFT, RIGHT};
	Position pos;
	Car* currentCar;

	Map* mapRef;

	void setNewPosition(Position newPos);

public:
	Player(int maxHP, int attackPwr);
	void setMapRef(Map* map);
	void movement();
	void Attack();
	void GetInCar();
	Car* GetCurrentCar() const;
	bool IsInCar() const;
	Position GetPosition() const;
	int GetPlayerMoney() const;
	void TakeDamage(int damage);
	void Respawn();
	bool IsAlive() const;
	int GetHealth() const;
	int GetMaxHealth() const;
	int GetAttackPower() const;
};

