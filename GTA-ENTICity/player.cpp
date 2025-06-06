#include "Player.h"
#include "Car.h"
#include "Map.h" // incluyo player para evitar dependencia circular

Player::Player(int maxHP, int attackPwr) {

    mapRef = nullptr;
    currentCar = nullptr;
    health = maxHP;
    maxHealth = maxHP;
    attackPower = attackPwr;
    arrested = false;
    // debug set position
    pos.x = 4;
    pos.y = 4;
}

void Player::setMapRef(Map* map) {
    mapRef = map; // Get Map ref
}

void Player::movement() { // reads user input and moves the player accordingly

    if (currentCar != nullptr) {
        // Car movement logic
        Position currentCarPos = currentCar->GetPosition();
        Position newCarPos = currentCarPos;

        if (GetAsyncKeyState(VK_UP)) {
            newCarPos = Position(currentCarPos.x - 1, currentCarPos.y);
            if (mapRef->checkNewCarPosition(newCarPos)) {
                // Verificar si hay peatón en la nueva posición antes de mover
                mapRef->HandleCarPedestrianCollision(newCarPos);
                currentCar->SetNewPosition(newCarPos);
            }
        }
        else if (GetAsyncKeyState(VK_DOWN)) {
            newCarPos = Position(currentCarPos.x + 1, currentCarPos.y);
            if (mapRef->checkNewCarPosition(newCarPos)) {
                mapRef->HandleCarPedestrianCollision(newCarPos);
                currentCar->SetNewPosition(newCarPos);
            }
        }
        else if (GetAsyncKeyState(VK_LEFT)) {
            newCarPos = Position(currentCarPos.x, currentCarPos.y - 1);
            if (mapRef->checkNewCarPosition(newCarPos)) {
                mapRef->HandleCarPedestrianCollision(newCarPos);
                currentCar->SetNewPosition(newCarPos);
            }
        }
        else if (GetAsyncKeyState(VK_RIGHT)) {
            newCarPos = Position(currentCarPos.x, currentCarPos.y + 1);
            if (mapRef->checkNewCarPosition(newCarPos)) {
                mapRef->HandleCarPedestrianCollision(newCarPos);
                currentCar->SetNewPosition(newCarPos);
            }
        }
    }
    else {
        if (GetAsyncKeyState(VK_UP)) {
            Position newPos(pos.x - 1, pos.y);
            setNewPosition(newPos);
        }
        else if (GetAsyncKeyState(VK_DOWN)) {
            Position newPos(pos.x + 1, pos.y);
            setNewPosition(newPos);
        }
        else if (GetAsyncKeyState(VK_LEFT)) {
            Position newPos(pos.x, pos.y - 1);
            setNewPosition(newPos);
        }
        else if (GetAsyncKeyState(VK_RIGHT)) {
            Position newPos(pos.x, pos.y + 1);
            setNewPosition(newPos);
        }
    }
}

void Player::Attack()
{
    if (currentCar == nullptr) {
        for (int i = 0; i < mapRef->GetNumPeatonesLosSantos(); i++) {
            Peaton& p = mapRef->GetPeatonesLosSantos()[i];
            if (p.IsNearToPlayer() && GetAsyncKeyState(VK_SPACE)) {
                p.TakeDamage(attackPower);
                if (!p.IsAlive()) {
                    p.Respawn(); 
                }
                break;  // Atacar solo a un peaton por frame
            }
        }

        for (int i = 0; i < mapRef->GetNumPeatonesSanFierro(); i++) {
            Peaton& p = mapRef->GetPeatonesSanFierro()[i];
            if (p.IsNearToPlayer() && GetAsyncKeyState(VK_SPACE)) {
                p.TakeDamage(attackPower);
                if (!p.IsAlive()) {
                    p.Respawn();  
                }
                break;
            }
        }

        // Atacar a BigSmoke si está cerca
        if (mapRef->GetBigSmoke() != nullptr && mapRef->GetBigSmoke()->IsAlive()) {
            if (mapRef->GetBigSmoke()->IsNearToPlayer() && GetAsyncKeyState(VK_SPACE)) {
                mapRef->GetBigSmoke()->TakeDamage(attackPower);
                
                return;
            }
        }
    }
}

void Player::GetInCar() {
    if (GetAsyncKeyState('E')) { // Como VK_E no esta definido en Windows.h utilizo 'E'
        if (currentCar == nullptr) {
            currentCar = mapRef->FindNearestCar(pos);

            // Ocultar al jugador del mapa cuando se sube al coche
            mapRef->getBox()[pos.x][pos.y] = '.';
        }
        else {
            Position exitPos = currentCar->ExitCar();
            if (exitPos.x != -1 && exitPos.y != -1) {
                pos = exitPos;
                mapRef->checkNewPlayerPosition(exitPos); // Update player on map
                currentCar = nullptr;
            }
        }
    }
}

Car* Player::GetCurrentCar() const { return currentCar; }

bool Player::IsInCar() const {
    return currentCar != nullptr;
}

void Player::setNewPosition(Position newPos) { // try to set the new position
    if (mapRef != nullptr) {
        // Solo recoger dinero si no está en coche
        if (currentCar == nullptr) {
            playerMoney += mapRef->CollectMoney(newPos);
        }

        if (mapRef->checkNewPlayerPosition(newPos)) {
            pos = newPos;
        }
    }
}

Position Player::GetPosition() const {
    return pos;
}

int Player::GetPlayerMoney() const { return playerMoney; }

void Player::RestPlayerMoney(int rest) {
    playerMoney -= rest;
}

void Player::TakeDamage(int damage) {
    health -= damage;
    if (health < 0) {
        health = 0;
    }
}

void Player::Respawn() {
    pos.x = 4;
    pos.y = 4;
    health = maxHealth;
}

bool Player::IsAlive() const {
    return health > 0;
}

int Player::GetHealth() const {
    return health;
}

int Player::GetMaxHealth() const {
    return maxHealth;
}

int Player::GetAttackPower() const {
    return attackPower;
}

bool Player::IsArrested() const { return arrested; }

void Player::SetIsArrested() { arrested = true; }