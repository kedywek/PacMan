#pragma once
#include "Character.h"
#include "Pac.h"

class Ghost : public Character {
    Q_OBJECT
public:
    Ghost(int x, int y, int speed, Map *map, Direction direction, int size);
    void checkCollisionWithPac();
    void scatter();
    void chase();
    void setTarget(Character *target);
    void runAway();
private:
    int targetX, targetY;
    Pac *target;
};
