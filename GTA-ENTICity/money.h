#pragma once
#include "position.h"

class Money
{
private:
    Position pos;
    int value;
public:
    Money(Position p, int v);
    int GetValue() const;
    Position GetPosition() const;
};

