#pragma once
#include "Character.h"
#include "Pac.h"
#include <QGraphicsColorizeEffect>

class Ghost : public Character {
    Q_OBJECT

public:
    Ghost(int x, int y, int speed, Map *map, Direction direction, int size);
    bool checkCollisionWithPac();
    virtual void chase();
    void setTarget();
    virtual void scatter();
    void runAway();
    void returnHome();
    void ai();
    enum GhostState {
        WAIT,
        GO_TO_CORNER,
        CHASE,
        SCATTER,
        FRIGHTENED,
        DEAD,
        BEGINING
    };
    GhostState getState();
    void setState(GhostState state);
protected:
    int targetX, targetY;
    unsigned int range, startTimer;
    Pac *target;
    GhostState state;
    void updateAppearance();
    QGraphicsColorizeEffect *colorizeEffect;
};
