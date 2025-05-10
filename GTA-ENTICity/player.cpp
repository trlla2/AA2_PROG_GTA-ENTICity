#include "player.h"

Player::Player() {

    mapRef = nullptr;
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

void Player::setNewPosition(Position newPos) { // try to set the new position
    if (mapRef != nullptr && mapRef->setNewPlayerPosition(newPos)) {
        pos = newPos;
    }
}

Position Player::getPosition() {
    return pos;
}