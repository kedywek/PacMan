#include "Blinky.h"
#include "AStar.h"
#include <QDebug>

Blinky::Blinky(int x, int y, int speed, Map *map, Direction direction, int size, int homeX, int homeY) : Ghost(x, y, speed, map, direction, size) {
    qDebug() << "Initializing Blinky at position:" << x << y;
    for (int i = 0; i < 2; i++) {
        QPixmap pixmap(QString(":/assets/blinky/blinky%0.png").arg(i));
        if (pixmap.isNull()) {
            qDebug() << "Failed to load pixmap for blinky" << i;
            throw std::runtime_error("Failed to load pixmap for pac");
        } else {
            this->addSprite(pixmap);
        }
    }
    this->setSprite(0);
    this->startTimer = 10000;
    this->setState(BEGINING);
    this->range = map->getTileSize() * 4;
    this->homeX = homeX;
    this->homeY = homeY;
}

void Blinky::scatter() {
    Ghost::scatter();
    AStar aStar;
    if (state == GO_TO_CORNER)
    {
        Direction towardsCorner = aStar.findPath(x, y, map->getTileSize(), map->getTileSize(), map, map->getTileSize());
        this->nextDirection = towardsCorner;
        if (this->direction == UP && this->nextDirection == NO_DIRECTION)
        {
            this->direction = DOWN;
        }
    }
    if (state == SCATTER || state == FRIGHTENED)
    {
        this->setTarget();
        if(aStar.getDistance (x, y, target->getX(), target->getY()) > range){
            switch (this->direction){
                case UP:
                    this->nextDirection = LEFT;
                    if (map->getTypeOfTopObject(x - speed, y) == WALL && map->getTypeOfTopObject(x, y - speed) == WALL){
                        this->nextDirection = RIGHT;
                    }
                    break;
                case DOWN:
                    this->nextDirection = RIGHT;
                    break;
                case LEFT:
                    this->nextDirection = DOWN;
                    break;
                case RIGHT:
                    this->nextDirection = UP;
                    break;
                case NO_DIRECTION:
                    break;
            }
        }else{
            this->state = CHASE;
        }
    }
}

void Blinky::chase() {
    Ghost::chase();
    AStar aStar;
    if(aStar.getDistance (x, y, target->getX(), target->getY()) > range){
        this->state = GO_TO_CORNER;
    }
}