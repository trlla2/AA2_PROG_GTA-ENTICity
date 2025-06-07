#pragma once
#include "Position.h"
#include <Windows.h>


class Map; // declaracion anticipada para evitar dependencia circular
class Car;

class Player
{
private:
	enum Direction { UP, DOWN, LEFT, RIGHT };
	Direction currentDirection;
	int playerMoney = 0;
	int health;
	int maxHealth;
	int attackPower;
	bool arrested;
	Position pos;
	Car* currentCar;

	Map* mapRef;

	void setNewPosition(Position newPos);

public:
	Player(int maxHP, int attackPwr);
	void SetMapRef(Map* map);
	void Movement();
	void Attack();
	void GetInCar();
	Car* GetCurrentCar() const;
	bool IsInCar() const;
	Position GetPosition() const;
	int GetPlayerMoney() const;
	void RestPlayerMoney(int rest);
	void TakeDamage(int damage);
	void Respawn();
	bool IsAlive() const;
	int GetHealth() const;
	int GetMaxHealth() const;
	int GetAttackPower() const;
	bool IsArrested() const;
	void SetIsArrested();

	char GetPlayerSymbol() const;
};

