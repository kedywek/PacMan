#include "Pinky.h"
#include "AStar.h"
#include <QDebug>

Pinky::Pinky(int x, int y, int speed, Map *map, Direction direction, int size, int homeX, int homeY) : Ghost(x, y, speed, map, direction, size) {
    qDebug() << "Initializing Pinky at position:" << x << y;
    for (int i = 0; i < 2; i++) {
        QPixmap pixmap(QString(":/assets/pinky/pinky%0.png").arg(i));
        if (pixmap.isNull()) {
            qDebug() << "Failed to load pixmap for pinky" << i;
            throw std::runtime_error("Failed to load pixmap for pac");
        } else {
            this->addSprite(pixmap);
        }
    }
    this->setSprite(0);
    this->startTimer = 5000;
    this->setState(BEGINING);
    this->range = map->getTileSize() * 6;
    this->homeX = homeX;
    this->homeY = homeY;
}

void Pinky::scatter() {
    Ghost::scatter();
    AStar aStar;
    if (state == GO_TO_CORNER)
    {
        int targetX = map->getWidth() - map->getTileSize() - map->getTileSize();
        int targetY = map->getHeight() - map->getTileSize() - map->getTileSize();
        Direction towardsCorner = aStar.findPath(x, y, targetX, targetY, map, map->getTileSize());
        this->nextDirection = towardsCorner;
        if (this->direction == RIGHT && this->nextDirection == NO_DIRECTION)
        {
            this->direction = LEFT;
        }
    }
    if (state == SCATTER || state == FRIGHTENED)
    {
        this->setTarget();
        if(aStar.getDistance (x, y, target->getX(), target->getY()) > range){
            switch (this->direction){
                case UP:
                    this->nextDirection = RIGHT;
                    break;
                case DOWN:
                    this->nextDirection = LEFT;
                    break;
                case LEFT:
                    this->nextDirection = UP;
                    break;
                case RIGHT:
                    this->nextDirection = DOWN;
                    if (map->getTypeOfTopObject(x + speed + map->getTileSize(), y) == WALL && map->getTypeOfTopObject(x, y + speed + map->getTileSize()) == WALL){
                        this->nextDirection = UP;
                    }
                    break;
                case NO_DIRECTION:
                    break;
            }
        }else{
            this->state = CHASE;
        }
    }
}


void Pinky::chase() {
    Ghost::chase();
    AStar aStar;
    if(aStar.getDistance (x, y, target->getX(), target->getY()) > range){
        this->state = GO_TO_CORNER;
    }
}