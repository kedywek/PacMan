#include "Inky.h"
#include "AStar.h"
#include <QDebug>

Inky::Inky(int x, int y, int speed, Map *map, Direction direction, int size, int homeX, int homeY) : Ghost(x, y, speed, map, direction, size) {
    qDebug() << "Initializing Inky at position:" << x << y;
    for (int i = 0; i < 2; i++) {
        QPixmap pixmap(QString(":/assets/inky/inky%0.png").arg(i));
        if (pixmap.isNull()) {
            qDebug() << "Failed to load pixmap for inky" << i;
            throw std::runtime_error("Failed to load pixmap for pac");
        } else {
            this->addSprite(pixmap);
        }
    }
    this->setSprite(0);
    this->startTimer = 3000;
    this->setState(BEGINING);
    this->range = map->getTileSize() * 10;
    this->homeX = homeX;
    this->homeY = homeY;
}

void Inky::scatter() {
    Ghost::scatter();
    AStar aStar;
    if (state == GO_TO_CORNER)
    {
        int targetX = map->getWidth() - map->getTileSize() - map->getTileSize();
        int targetY = map->getTileSize();
        Direction towardsCorner = aStar.findPath(x, y, targetX, targetY, map, map->getTileSize());
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
                    this->nextDirection = RIGHT;
                    if (map->getTypeOfTopObject(x + speed + map->getTileSize(), y) == WALL && map->getTypeOfTopObject(x, y - speed) == WALL){
                        this->nextDirection = LEFT;
                    }
                    break;
                case DOWN:
                    this->nextDirection = LEFT;
                    break;
                case LEFT:
                    this->nextDirection = UP;
                    break;
                case RIGHT:
                    this->nextDirection = DOWN;
                    break;
                case NO_DIRECTION:
                    break;
            }
        }else{
            this->state = CHASE;
        }
    }
}

void Inky::chase() {
    Ghost::chase();
    AStar aStar;
    if(aStar.getDistance (x, y, target->getX(), target->getY()) > range){
        this->state = GO_TO_CORNER;
    }
}