#pragma once

#include "Ghost.h"

class Clyde : public Ghost {
    Q_OBJECT
public:
    Clyde(int x, int y, int speed, Map *map, Direction direction, int size, int homeX, int homeY);
    void scatter() override;
    void chase() override;
};