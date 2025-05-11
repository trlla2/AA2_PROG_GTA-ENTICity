#pragma once
#include "position.h"

class Money
{
private:
	Position pos;
	int value;

	Money();
	~Money();
public:
	int GetMoneyValue();
};

