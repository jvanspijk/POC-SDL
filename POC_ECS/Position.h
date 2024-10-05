#pragma once
#include "Component.h"

class Position : public Component {
public:
    int x, y;
    Position(int x, int y) : x(x), y(y) {}
};

