#include "Map.h"
#include <QDebug>
#include "Pac.h"


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
            Wall *wall = nullptr;
            Pac *pac = nullptr;
            switch (map[i][j]) {
                case 1:
                    wall = new Wall(j, i, tileSize);
                    addItem(wall);  
                    break;
                case 2:
                    pac = new Pac(j*tileSize, i*tileSize, 4, this, RIGHT, tileSize);
                    addItem(pac);
                    addCharacter(pac);
                    pac->setFocus();
                    break;
                default:
                    break;
            }
        }
    }
    setBackgroundBrush(QBrush(Qt::black));
}

void Map::update() {
    for (Character *character : characters) {
        character->move();
        character->changeDirection();
    }
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

TypeOfTile Map::MapTile::getType() {
    return type;
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


TypeOfTile Map::getTypeOfTopTile(int x, int y) {
    QList<QGraphicsItem*> itemsAtPoint = items(QPointF(x, y));
    if (!itemsAtPoint.isEmpty())
    {
        QGraphicsItem* topItem = itemsAtPoint.first();
        if (dynamic_cast<Wall*>(topItem))
        {
            return WALL;
        }
    }
    return NONE;
}

QGraphicsItem *Map::getCharacterAt(int x, int y) {
    QList<QGraphicsItem*> itemsAtPoint = items(QPointF(x, y));
    if (!itemsAtPoint.isEmpty())
    {
        QGraphicsItem* topItem = itemsAtPoint.first();
        if (dynamic_cast<Character*>(topItem))
        {
            return topItem;
        }
    }
    return nullptr;
}
