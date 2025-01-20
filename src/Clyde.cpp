#include "Clyde.h"
#include "AStar.h"
#include <QDebug>

Clyde::Clyde(int x, int y, int speed, Map *map, Direction direction, int size, int homeX, int homeY) : Ghost(x, y, speed, map, direction, size) {
    qDebug() << "Initializing Clyde at position:" << x << y;
    for (int i = 0; i < 2; i++) {
        QPixmap pixmap(QString(":/assets/clyde/clyde%0.png").arg(i));
        if (pixmap.isNull()) {
            qDebug() << "Failed to load pixmap for clyde" << i;
            throw std::runtime_error("Failed to load pixmap for pac");
        } else {
            this->addSprite(pixmap);
        }
    }
    this->setSprite(0);
    this->state = GO_TO_CORNER;
    this->range = map->getTileSize() * 6;
    this->homeX = homeX;
    this->homeY = homeY;
}

void Clyde::scatter() {
    Ghost::scatter();
    AStar aStar;
    if (state == GO_TO_CORNER)
    {
        int targetX = map->getTileSize();
        int targetY = map->getHeight() - map->getTileSize() - map->getTileSize();
        Direction towardsCorner = aStar.findPath(x, y, targetX, targetY, map, map->getTileSize());
        this->nextDirection = towardsCorner;
        if(this->direction == LEFT && this->nextDirection == NO_DIRECTION){
            this->direction = RIGHT;
        }
    }
    if (state == SCATTER)
    {   
        this->setTarget();
        if(aStar.getDistance (x, y, target->getX(), target->getY()) > range){
            switch (this->direction){
                case UP:
                    this->nextDirection = LEFT;
                    break;
                case DOWN:
                    this->nextDirection = RIGHT;
                    break;
                case LEFT:
                    this->nextDirection = DOWN;
                    if (map->getTypeOfTopObject(x, y + speed + map->getTileSize()) == WALL && map->getTypeOfTopObject(x - speed, y) == WALL)
                    {
                        this->nextDirection = UP;
                    }
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

void Clyde::chase() {
    Ghost::chase();
    AStar aStar;
    if(aStar.getDistance (x, y, target->getX(), target->getY()) > range){
        this->state = GO_TO_CORNER;
    }
}