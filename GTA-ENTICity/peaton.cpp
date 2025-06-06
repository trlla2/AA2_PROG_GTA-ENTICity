#include "Peaton.h"

Peaton::Peaton()
{
	pos.x = 0;
	pos.y = 0;

	playerRef = nullptr;
	mapRef = nullptr;

	zone = Zone::LOS_SANTOS;  

	maxMoneyDrop = 10;  
	attackTimer = 0.0f;
}

Peaton::Peaton(Player* player, Map* map, Zone peatonZone, int maxMonDrop, int attackDMG, int hp)
{
	playerRef = player;
	mapRef = map;
	zone = peatonZone;
	maxMoneyDrop = maxMonDrop;
	damage = attackDMG;
	maxHealth = hp;
	health = maxHealth;
	attackTimer = 0.0f;
	behavior = (rand() % 2 == 0) ? NEUTRAL : AGGRESSIVE;
	int minJ = 0;
	int maxJ = 0;
	if (zone == Zone::LOS_SANTOS) {
		minJ = 1;
		maxJ = mapRef->getWidth() / 3 - 1; // Primer tercio
	}
	else if (zone == Zone::SAN_FIERRO) {
		minJ = mapRef->getWidth() / 3 + 1; // Segundo tercio
		maxJ = 2 * (mapRef->getWidth() / 3) - 1;
	}

	bool instancedPeaton = false;
	int checkPosX = 0;
	int checkPosY = 0;
	while (!instancedPeaton) {
		checkPosX = rand() % (mapRef->getHeight() - 2) + 1; // Evitar bordes
		checkPosY = rand() % (maxJ - minJ) + minJ; // J dentro de su zona
		
		if (mapRef->getBox()[checkPosX][checkPosY] != NULL) {
			if (mapRef->getBox()[checkPosX][checkPosY] == '.') {
				pos.x = checkPosX;
				pos.y = checkPosY;
				instancedPeaton = true;
			}
		}
	}
}

Peaton::~Peaton()
{
	// Generar nuevo peaton
	bool instancedPeaton = false;
	int checkPosX = 0;
	int checkPosY = 0;
	while (instancedPeaton == false) {
		checkPosX = rand() % mapRef->getWidth();
		checkPosY = rand() % mapRef->getHeight();

		if (mapRef->getBox()[pos.x][pos.y] == '.') {
			pos.x = checkPosX;
			pos.y = checkPosY;
			instancedPeaton = true;
		}
	}
}

void Peaton::SetNewPosition(Position p)
{
	pos = p;
}



Position Peaton::GetPosition() const
{
	return pos;
}

void Peaton::MovePeaton()
{
	bool shouldMove;

	if (IsNearToPlayer())
		shouldMove = false;
	else
		shouldMove = true;

	if (shouldMove) // move 
	{
		int randomMoveDirection = rand() % 4; // 0 = up // 1 = down // 2 = left // 3 = right

		if (randomMoveDirection == 0) {
			Position newPos(pos.x, pos.y - 1);
			if (mapRef->SetNewPeatonPosition(newPos, this))
				SetNewPosition(newPos);
		}
		else if (randomMoveDirection == 1)
		{
			Position newPos(pos.x, pos.y + 1);
			if (mapRef->SetNewPeatonPosition(newPos, this))
				SetNewPosition(newPos);
		}
		else if (randomMoveDirection == 2)
		{
			Position newPos(pos.x - 1, pos.y);
			if (mapRef->SetNewPeatonPosition(newPos, this))
				SetNewPosition(newPos);
		}
		else if (randomMoveDirection == 3)
		{
			Position newPos(pos.x + 1, pos.y);
			if (mapRef->SetNewPeatonPosition(newPos, this))
				SetNewPosition(newPos);
		}
	}
	else
	{
		// stop moving
	}
	
}


bool Peaton::IsNearToPlayer()
{
	Position playerPos = playerRef->GetPosition();
	int x = abs(playerPos.x - pos.x);
	int y = abs(playerPos.y - pos.y);

	if (x <= 1 && y <= 1)
		return true;
	else
		return false;
}

void Peaton::Respawn()
{
	int minJ = 0;
	int maxJ = 0;
	if (zone == Zone::LOS_SANTOS) {
		minJ = 1;
		maxJ = mapRef->getWidth() / 3 - 1;
	}
	else if (zone == Zone::SAN_FIERRO){
		minJ = mapRef->getWidth() / 3 + 1;
		maxJ = 2 * (mapRef->getWidth() / 3) - 1;
	}

	bool instancedPeaton = false;
	while (!instancedPeaton) {
		int newX = rand() % (mapRef->getHeight() - 2) + 1;
		int newY = rand() % (maxJ - minJ) + minJ;

		if (mapRef->getBox()[newX][newY] == '.') {
			Position oldPos = pos;

			// Generar dinero según zona
			int moneyValue = rand() % maxMoneyDrop + 1;
			

			mapRef->getBox()[oldPos.x][oldPos.y] = '$';
			mapRef->GetMoneyValues()[oldPos.x][oldPos.y] = moneyValue;

			pos.x = newX;
			pos.y = newY;
			mapRef->SetNewPeatonPosition(pos, this);
			instancedPeaton = true;
		}
	}
}

void Peaton::TakeDamage(int damage)
{
	health -= damage;
	if (health < 0) {
		health = 0;
	}

	
	if (behavior == AGGRESSIVE && IsNearToPlayer()) {
		isAttacking = true;
		attackTimer = 0.0f; 
	}
}

bool Peaton::IsAlive() const {	return health > 0; }

void Peaton::UpdateAttackTimer(float deltaTime)
{
	if (isAttacking && behavior == AGGRESSIVE && IsNearToPlayer()) {
		attackTimer += deltaTime;

		
		if (attackTimer >= 1.0f) {
			AttackPlayer();
			attackTimer = 0.0f; // Reset timer
		}
	}
	else {
		attackTimer = 0.0f;
		isAttacking = false;
	}
}

void Peaton::AttackPlayer()
{
 	if (behavior == AGGRESSIVE && IsNearToPlayer() && IsAlive()) {
		playerRef->TakeDamage(damage);
	}
}

PedestrianBehavior Peaton::GetBehavior() const
{
	return behavior;
}

int Peaton::GetHealth() const
{
	return health;
}

int Peaton::GetMaxHealth() const
{
	return maxHealth;
}