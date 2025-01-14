#include "Map.h"
#include <QDebug>

Map::Map(QObject *parent, size_t width, size_t height) : QGraphicsScene(parent), width(width), height(height) {
    if (width < height){
        tileSize = width / ARRAY_WIDTH;
    } else {
        tileSize = height / ARRAY_HEIGHT;
    }
    this->width = width;
    this->height = height;
}

void Map::setupMap() {
    for (size_t i = 0; i < ARRAY_WIDTH; i++) {
        for (size_t j = 0; j < ARRAY_HEIGHT; j++) {
            if (map[i][j] == 1) {
                Wall *wall = new Wall(j, i, tileSize);
                addItem(wall);  
            }
        }
    }
    setBackgroundBrush(QBrush(Qt::black));
}

void Map::update() {
    for (Character *character : characters) {
        character->move();
    }
    qDebug() << "Game updated";

}

Map::MapTile::MapTile(unsigned int x, unsigned int y, unsigned int size) {
    this->x = x;
    this->y = y;
    this->size = size;
    setRect(x * size, y * size, size, size);
}
Map::Wall::Wall(unsigned int x, unsigned int y, unsigned int size) : MapTile(x, y, size) {
    setBrush(QBrush(Qt::blue));
    setPen(Qt::NoPen);
}
unsigned int Map::MapTile::getSize() {
    return size;
}

void Map::Wall::setTop(bool top) {
    this->top = top;
}
void Map::Wall::setRight(bool right) {
    this->right = right;
}
void Map::Wall::setBottom(bool bottom) {
    this->bottom = bottom;
}
void Map::Wall::setLeft(bool left) {
    this->left = left;
}

QVector<Character *> Map::getCharacters() {
    return characters;
}

void Map::addCharacter(Character *character) {
    characters.push_back(character);
}