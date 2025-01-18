#include "Map.h"
#include <QDebug>
#include "Pac.h"


Map::Map(QObject *parent, size_t width, size_t height) : QGraphicsScene(parent), width(width), height(height) {
    if (width < height){
        tileSize = width / ARRAY_WIDTH;
    } else {
        tileSize = height / ARRAY_HEIGHT;
    }
    if (width > height)
    {
        this->width = height;
        this->height = height;
    }
    else{
        this->width = width;
        this->height = width;
    }
    
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
        teleportCharacter(character);
        character->changeDirection();
    }
    characters.at(0)->setFocus();
}

Map::MapTile::MapTile(unsigned int x, unsigned int y, unsigned int size) {
    this->x = x;
    this->y = y;
    this->size = size;
    this->type = NONE;
    QGraphicsRectItem *tile = new QGraphicsRectItem(x * size, y * size, size, size);
    tile->setBrush(QBrush(Qt::black));
    tile->setPen(QPen(Qt::NoPen));
    this->addToGroup(tile);
}
Map::Wall::Wall(unsigned int x, unsigned int y, unsigned int size) : MapTile(x, y, size) {
    this->setType(WALL);
    QGraphicsRectItem* wall = new QGraphicsRectItem(x * size, y * size, size, size);
    wall->setBrush(QBrush(Qt::blue));
    wall->setPen(QPen(Qt::NoPen));
    this->addToGroup(wall);
}

void Map::MapTile::setType(TypeOfTile type) {
    this->type = type;
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
    for (QGraphicsItem* item : itemsAtPoint) {
        if (MapTile* tile = dynamic_cast<MapTile*>(item)) {
            return tile->getType();
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

void Map::teleportCharacter(Character *character) {
    int x = character->getX();
    int y = character->getY();
    int signedWidth = static_cast<int>(width);
    int signedHeight = static_cast<int>(height);
    int signedTileSize = static_cast<int>(tileSize);
    if(x < - signedTileSize + character->getSpeed()){
        character->move(signedWidth + signedTileSize - character->getSpeed(), 0);
    }
    else if(x > signedWidth - character->getSpeed()){
        character->move(-signedWidth - signedTileSize  + character->getSpeed(), 0);
    }
    else if(y < -signedTileSize + character->getSpeed()){
        character->move(0, signedHeight + signedTileSize - character->getSpeed());
    }
    else if(y > signedHeight - character->getSpeed()){
        character->move(0, -signedHeight - signedTileSize + character->getSpeed());
    }
}