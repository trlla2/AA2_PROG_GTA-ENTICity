#include "money.h"

Money::Money(Position p, int v) {
    pos = p;
    value = v;
}

int Money::GetValue() const {
    return value;
}

Position Money::GetPosition() const {
    return pos;
}
