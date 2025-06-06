#pragma once
#include "Position.h"
#include "Zones.h"

class Player;
class Map;

class BigSmoke
{
private:
    Position pos;
    Player* playerRef;
    Map* mapRef;
    int health;
    int maxHealth;
    int damage;
    float attackTimer;
    bool isAttacking;
    bool isAlive;

    void SetNewPosition(Position p);

public:
    BigSmoke();
    BigSmoke(Player* player, Map* map);
 

    Position GetPosition() const;
    void MoveBigSmoke();
    bool IsNearToPlayer();
    void TakeDamage(int damage);
    bool IsAlive() const;
    void UpdateAttackTimer(float deltaTime);
    void AttackPlayer();
    int GetHealth() const;
    int GetMaxHealth() const;
    bool IsDead() const;
};