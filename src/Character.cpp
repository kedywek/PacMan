#include "Character.h"
#include <QDebug>
#include "Map.h"

Character::Character(int x, int y, int speed, QVector<QPixmap> sprites, Map *map, Direction direction,int size)
    : map(map), x(x), y(y), speed(speed), direction(direction), nextDirection(direction), sprites(sprites), size(size) {
    setPixmap(sprites[0]);
    setPos(x, y);
}

void Character::move(int x, int y) {
    moveBy(x, y);
    this->x += x;
    this->y += y;
}

void Character::move() {
    if (collidesWithWall(direction)) {
        return;
    }
    switch (direction) {
        case UP:
            move(0, - speed);
            break;
        case RIGHT:
            move(speed, 0);
            break;
        case DOWN:
            move(0,speed);
            break;
        case LEFT:
            move(- speed, 0);
            break;
    }
}

void Character::setDirection(Direction direction) {
    this->direction = direction;
}

void Character::setSpeed(int speed) {
    this->speed = speed;
}

void Character::setSprites(QVector<QPixmap> sprites) {
    this->sprites = sprites;
}

void Character::addSprite(QPixmap sprite) {
    sprites.push_back(sprite);
}

void Character::setSprite(int index) {
    try
    {
        setPixmap(sprites.at(index));
        this->currentSprite = index;
    }
    catch (const std::out_of_range &e)
    {
        qDebug() << "Sprite index out of range";
    }
}

void Character::setNextDirection(Direction direction) {
    this->nextDirection = direction;
}
int Character::getX() {
    return x;
}
int Character::getY() {
    return y;
}
int Character::getSpeed() {
    return speed;
}
Direction Character::getDirection() {
    return direction;
}
void Character::changeDirection() {
    if (nextDirection == direction) {
        return;
    }
    if (collidesWithWall(nextDirection)) {
        return;
    }
    direction = nextDirection;
}
int Character::getSize() {
    return size;
}
bool Character::collidesWithWall(Direction direction) {
    switch (direction) {
        case UP:
            return map->getTypeOfTopTile(x, y - speed) == WALL || map->getTypeOfTopTile(x + size - 1, y - speed) == WALL;
        case RIGHT:
            return map->getTypeOfTopTile(x + speed + size - 1, y) == WALL || map->getTypeOfTopTile(x + speed + size - 1, y + size - 1) == WALL;
        case DOWN:
            return map->getTypeOfTopTile(x, y + speed + size - 1) == WALL || map->getTypeOfTopTile(x + size - 1, y + speed + size - 1) == WALL;
        case LEFT:
            return map->getTypeOfTopTile(x - speed, y) == WALL || map->getTypeOfTopTile(x - speed, y + size - 1) == WALL;
    }
    return false;
}
