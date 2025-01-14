#include "Character.h"
#include <QDebug>

Character::Character(int x, int y, int direction, int speed, QVector<QPixmap> sprites)
    : QObject(), QGraphicsPixmapItem(), x(x), y(y), direction(direction), speed(speed), sprites(sprites) {
    setPixmap(sprites[0]);
    setPos(x, y);
}

void Character::move(int x, int y) {

    moveBy(x, y);
    this->x += x;
    this->y += y;
}

void Character::move() {
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

void Character::setDirection(int direction) {
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

