#pragma once

#include "Ghost.h"

class Pinky : public Ghost {
    Q_OBJECT
public:
    Pinky(int x, int y, int speed, Map *map, Direction direction, int size, int homeX, int homeY);
    void scatter() override;
    void chase() override;
private:
};
