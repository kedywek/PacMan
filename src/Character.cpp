#include "Character.h"
#include <QDebug>

Character::Character(int x, int y, int speed, QVector<QPixmap> sprites, Map *map, Direction direction, int size)
    : sprites(sprites), direction(direction), nextDirection(direction), map(map), x(x), y(y), speed(speed), size(size) {
    setPixmap(sprites[0]);
    setPos(x, y);
    this->homeX = x;
    this->homeY = y;
    this->setZValue(1);
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
            this->nextSprite();
            break;
        case RIGHT:
            move(speed, 0);
            this->nextSprite();
            break;
        case DOWN:
            move(0,speed);
            this->nextSprite();
            break;
        case LEFT:
            move(- speed, 0);
            this->nextSprite();
            break;
        case NO_DIRECTION:
            qDebug() << "No direction";
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
    if (nextDirection == NO_DIRECTION) {
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
            return map->getTypeOfTopObject(x, y - speed) == WALL || map->getTypeOfTopObject(x + size - 1, y - speed) == WALL;
        case RIGHT:
            return map->getTypeOfTopObject(x + speed + size - 1, y) == WALL || map->getTypeOfTopObject(x + speed + size - 1, y + size - 1) == WALL;
        case DOWN:
            return map->getTypeOfTopObject(x, y + speed + size - 1) == WALL || map->getTypeOfTopObject(x + size - 1, y + speed + size - 1) == WALL;
        case LEFT:
            return map->getTypeOfTopObject(x - speed, y) == WALL || map->getTypeOfTopObject(x - speed, y + size - 1) == WALL;
        case NO_DIRECTION:
            return false;
    }
    return false;
}

void Character::nextSprite() {
    this->currentSprite = (this->currentSprite + 1) % this->sprites.size();
    setPixmap(sprites[this->currentSprite]);
}

int Character::getHomeX() {
    return homeX;
}

int Character::getHomeY() {
    return homeY;
}