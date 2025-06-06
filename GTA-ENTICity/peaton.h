#pragma once
#include <Windows.h>
#include "position.h"
#include "player.h"
#include "map.h"
#include "zones.h"

//class Map;

enum PedestrianBehavior {
	NEUTRAL,
	AGGRESSIVE
};

class Peaton
{
private:
	Position pos;
	Player* playerRef;
	Map* mapRef;
	Zone zone;
	int maxMoneyDrop;
	int health;
	int maxHealth;
	PedestrianBehavior behavior;
	float attackTimer;
	bool isAttacking;
	int damage;


	void SetNewPosition(Position p);

public:
	Peaton();
	Peaton(Player* player, Map* map, Zone peatonZone, int maxMonDrop, int attackDMG, int hp);
	~Peaton();
	Position GetPosition() const;
	void MovePeaton();
	bool IsNearToPlayer();
	void Respawn();
	void TakeDamage(int damage);
	bool IsAlive() const;
	void UpdateAttackTimer(float deltaTime);
	void AttackPlayer();
	PedestrianBehavior GetBehavior() const;
	int GetHealth() const;
	int GetMaxHealth() const;
};

