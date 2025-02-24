#pragma once
#include "Character.h"

class Pac : public Character {
    Q_OBJECT
public:
    Pac(int x, int y, int speed, Map *map, Direction direction, int size);
    void checkCollisionWithCollectibles();
    void changeDirection() override;
    void move() override;
    void rotatePac(Direction direction);
protected:
    void keyPressEvent(QKeyEvent *event) override;

public slots:
    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();
};