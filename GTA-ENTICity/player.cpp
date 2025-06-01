#include "Player.h"
#include "Car.h"
#include "Map.h" // incluyo player para evitar dependencia circular

Player::Player() {

    mapRef = nullptr;
    currentCar = nullptr;
	// debug set position
	pos.x = 4;
	pos.y = 4;
}

void Player::setMapRef(Map* map) {
    mapRef = map; // Get Map ref
}

void Player::movement() { // reads user input and moves the player accordingly
    
    if (GetAsyncKeyState(VK_UP))// arrow key up
    {
        Position newPos(pos.x - 1, pos.y);

        setNewPosition(newPos);
    }
    else if (GetAsyncKeyState(VK_DOWN))// arrow key down
    {
        Position newPos(pos.x + 1, pos.y);

        setNewPosition(newPos);
    }
    else if (GetAsyncKeyState(VK_LEFT))// arrow key left
    {
        Position newPos(pos.x, pos.y - 1);

        setNewPosition(newPos);
    }
    else if (GetAsyncKeyState(VK_RIGHT))// arrow key right
    {
        Position newPos(pos.x, pos.y + 1);

        setNewPosition(newPos);
    }
}

void Player::Attack()
{
    if (currentCar == nullptr) {
        for (int i = 0; i < mapRef->GetNumPeatonesLosSantos(); i++) {
            Peaton& p = mapRef->GetPeatonesLosSantos()[i];
            if (p.IsNearToPlayer() && GetAsyncKeyState(VK_SPACE)) {
                p.Respawn();  // M�todo nuevo
                break;  // Atacar solo a un peaton por frame
            }
        }

        for (int i = 0; i < mapRef->GetNumPeatonesSanFierro(); i++) {
            Peaton& p = mapRef->GetPeatonesSanFierro()[i];
            if (p.IsNearToPlayer() && GetAsyncKeyState(VK_SPACE)) {
                p.Respawn();
                break;
            }
        }
    }
}

void Player::GetInCar() {
    if (GetAsyncKeyState('E') && currentCar == nullptr) { // Como VK_E no esta definido en Windows.h utilizo 'E'
        currentCar = mapRef->FindNearestCar(pos);
    }
}

Car* Player::GetCurrentCar() const { return currentCar; }

void Player::setNewPosition(Position newPos) { // try to set the new position
    if (mapRef != nullptr) {
        playerMoney += mapRef->CollectMoney(newPos);

        if (mapRef->checkNewPlayerPosition(newPos)) {
            pos = newPos;
        }
    }
}

Position Player::GetPosition() const {
    return pos;
}

int Player::GetPlayerMoney() const { return playerMoney; }
