#include "BigSmoke.h"
#include "Player.h"
#include "Map.h"
#include "Utils.h"

BigSmoke::BigSmoke()
{
    pos.x = 0;
    pos.y = 0;
    playerRef = nullptr;
    mapRef = nullptr;
    maxHealth = 300; 
    health = maxHealth;
    damage = 50; 
    attackTimer = 0.0f;
    isAttacking = false;
    isAlive = true;
}

BigSmoke::BigSmoke(Player* player, Map* map)
{
    playerRef = player;
    mapRef = map;
    maxHealth = 30;
    health = maxHealth;
    damage = 10;
    attackTimer = 0.0f;
    isAttacking = false;
    isAlive = true;

    // Spawner en Las Venturas (tercera zona)
    int minY = 2 * (mapRef->getWidth() / 3) + 1;
    int maxY = mapRef->getWidth() - 2;

    bool bigSmokeSpawned = false;
    while (!bigSmokeSpawned) {
        int checkPosX = GenerateClampedRandom(1, mapRef->getHeight() - 2);
        int checkPosY = GenerateClampedRandom(minY, maxY);

        if (mapRef->getBox()[checkPosX][checkPosY] == '.') {
            pos.x = checkPosX;
            pos.y = checkPosY;
            bigSmokeSpawned = true;
        }
    }
}



void BigSmoke::SetNewPosition(Position p)
{
    pos = p;
}

Position BigSmoke::GetPosition() const
{
    return pos;
}

void BigSmoke::MoveBigSmoke()
{
    if (!isAlive) return;

    bool shouldMove;

    if (IsNearToPlayer())
        shouldMove = false;
    else
        shouldMove = true;

    if (shouldMove) {
        int randomMoveDirection = rand() % 4; // 0 = up, 1 = down, 2 = left, 3 = right
        Position newPos = pos;

        switch (randomMoveDirection) {
        case 0: newPos.y -= 1; break; // up
        case 1: newPos.y += 1; break; // down
        case 2: newPos.x -= 1; break; // left
        case 3: newPos.x += 1; break; // right
        }

        // Verificar que la nueva posición sea válida y dentro de Las Venturas
        int minY = 2 * (mapRef->getWidth() / 3) + 1;
        int maxY = mapRef->getWidth() - 2;

        if (newPos.x >= 1 && newPos.x < mapRef->getHeight() - 1 &&
            newPos.y >= minY && newPos.y <= maxY &&
            mapRef->getBox()[newPos.x][newPos.y] != 'X' &&
            mapRef->getBox()[newPos.x][newPos.y] != 'P' &&
            mapRef->getBox()[newPos.x][newPos.y] != 'C' &&
            (mapRef->getBox()[newPos.x][newPos.y] == '^' ||
             mapRef->getBox()[newPos.x][newPos.y] == 'v' ||
             mapRef->getBox()[newPos.x][newPos.y] == '<' ||
             mapRef->getBox()[newPos.x][newPos.y] == '>' ) ) {

            // Limpiar posición anterior
            mapRef->getBox()[pos.x][pos.y] = '.';

            // Establecer nueva posición
            SetNewPosition(newPos);
        }
    }
}

bool BigSmoke::IsNearToPlayer()
{
    Position playerPos = playerRef->GetPosition();
    int x = abs(playerPos.x - pos.x);
    int y = abs(playerPos.y - pos.y);

    if (x <= 1 && y <= 1)
        return true;
    else
        return false;
}

void BigSmoke::TakeDamage(int damageAmount)
{
    if (!isAlive) return;

    health -= damageAmount;
    if (health <= 0) {
        health = 0;
        isAlive = false;
        // Limpiar posición en el mapa
        mapRef->getBox()[pos.x][pos.y] = '.';
    }

    // Si está cerca del jugador, activar ataque
    if (isAlive && IsNearToPlayer()) {
        isAttacking = true;
        attackTimer = 0.0f;
    }
}

bool BigSmoke::IsAlive() const
{
    return isAlive;
}

void BigSmoke::UpdateAttackTimer(float deltaTime)
{
    if (!isAlive) return;

    if (isAttacking && IsNearToPlayer()) {
        attackTimer += deltaTime;

        // Atacar cada 0.8 segundos (más rápido que peatones normales)
        if (attackTimer >= 0.8f) {
            AttackPlayer();
            attackTimer = 0.0f;
        }
    }
    else {
        attackTimer = 0.0f;
        isAttacking = false;
    }
}

void BigSmoke::AttackPlayer()
{
    if (isAlive && IsNearToPlayer()) {
        playerRef->TakeDamage(damage);
    }
}

int BigSmoke::GetHealth() const
{
    return health;
}

int BigSmoke::GetMaxHealth() const
{
    return maxHealth;
}

bool BigSmoke::IsDead() const
{
    return !isAlive;
}