#pragma once
#include "Character.h"
#include "Pac.h"

class Ghost : public Character {
    Q_OBJECT
public:
    Ghost(int x, int y, int speed, Map *map, Direction direction, int size);
    bool checkCollisionWithPac();
    virtual void scatter();
    virtual void chase();
    virtual void setTarget(Character *target);
    virtual void runAway();
protected:
    int targetX, targetY;
    Pac *target;
};
