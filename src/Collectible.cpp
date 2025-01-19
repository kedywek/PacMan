#include "Collectible.h"


Collectible::Collectible(unsigned int x, unsigned int y, unsigned int size) {
    this->x = x;
    this->y = y;
    this->size = size;
}

unsigned int Collectible::getX() {
    return x;
}

unsigned int Collectible::getY() {
    return y;
}

unsigned int Collectible::getSize() {
    return size;
}

TypeOfObject Collectible::getType() {
    return type;
}

void Collectible::setType(TypeOfObject type) {
    this->type = type;
}
