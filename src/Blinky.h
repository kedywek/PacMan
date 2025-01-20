#pragma once 
#include "Ghost.h"

class Blinky : public Ghost {
    Q_OBJECT 
public:
    Blinky(int x, int y, int speed, Map *map, Direction direction, int size, int homeX, int homeY);
    void scatter() override;
    void chase() override;
};