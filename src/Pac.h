#pragma once
#include "Character.h"

class Pac : public Character {
    Q_OBJECT
public:
    Pac(int x, int y, int direction, int speed);

protected:
    void keyPressEvent(QKeyEvent *event) override;

public slots:
    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();
};