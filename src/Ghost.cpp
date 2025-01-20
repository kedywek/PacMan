#include "Ghost.h"

Ghost::Ghost(int x, int y, int speed, Map *map, Direction direction, int size) : Character(x, y, speed, QVector<QPixmap>(), map, direction, size) {
    this->setSprite(0);
}

bool Ghost::checkCollisionWithPac() {
    if (this->collidesWithItem(map->getCharacters().at(0))) {
        return true;
    }
    return false;
}

void Ghost::scatter() {
    return;
}

void Ghost::chase() {
    return;
}
void Ghost::setTarget(Character *target) {
    return;
}

void Ghost::runAway() {
    return;
}


