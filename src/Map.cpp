#include "Map.h"
#include <QDebug>
#include "Pac.h"
#include "Point.h"


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
                case 0:
                    spawnPoints(j, i, tileSize/4);
                    break;
                case 1:
                    wall = new Wall(j, i, tileSize);
                    this -> setNeighbours(wall);
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

void Map::MapTile::setType(TypeOfObject type) {
    this->type = type;
}

unsigned int Map::MapTile::getSize() {
    return size;
}

TypeOfObject Map::MapTile::getType() {
    return type;
}

unsigned int Map::MapTile::getX() {
    return x;
}
unsigned int Map::MapTile::getY() {
    return y;
}

void Map::setNeighbours(Wall* wall){
    int x = wall->getX();
    int y = wall->getY();
    bool neighbour[8] = {false, false, false, false, false, false, false, false};
    if (y > 0){
        neighbour[0] = map[x][y - 1] == 1;
    }
    if (y > 0 && x < ARRAY_WIDTH - 1){
        neighbour[1] = map[x + 1][y - 1] == 1;
    }
    if (x < ARRAY_WIDTH - 1){
        neighbour[2] = map[x + 1][y] == 1;
    }
    if (x < ARRAY_WIDTH - 1 && y < ARRAY_HEIGHT - 1){
        neighbour[3] = map[x + 1][y + 1] == 1;
    }
    if (y < ARRAY_HEIGHT - 1){
        neighbour[4] = map[x][y + 1] == 1;
    }
    if (y < ARRAY_HEIGHT - 1 && x > 0){
        neighbour[5] = map[x - 1][y + 1] == 1;
    }
    if (x > 0){
        neighbour[6] = map[x - 1][y] == 1;
    }
    if (x > 0 && y > 0){
        neighbour[7] = map[x - 1][y - 1] == 1;
    }
    wall->setNeighours(neighbour);
}
void Map::Wall::setNeighours(bool neighbours[8]){
    for (int i = 0; i < 8; i++){
        this->neighbours[i] = neighbours[i];
    }
} 

QVector<Character *> Map::getCharacters() {
    return characters;
}

QVector<Collectible *> Map::getCollectibles() {
    return collectibles;
}
void Map::addCharacter(Character *character) {
    characters.push_back(character);
}


TypeOfObject Map::getTypeOfTopObject(int x, int y) {
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

QGraphicsItem *Map::getCollectibleAt(int x, int y) {
    QList<QGraphicsItem*> itemsAtPoint = items(QPointF(x, y));
    for (QGraphicsItem* item : itemsAtPoint) {
        if (Collectible* collectible = dynamic_cast<Collectible*>(item)) {
            return collectible;
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

void Map::addCollectible(Collectible *collectible) {
    collectibles.push_back(collectible);
}
void Map::spawnPoints(unsigned int x, unsigned int y, unsigned int size) {
    Point *point = new Point(x * tileSize + tileSize / 2 - size / 2 + 1, y * tileSize + tileSize /2 - size / 2 + 1, size);
    if(x < arrayWidth - 1){
        if(map[y][x + 1] == 0){
            Point *point = new Point(x * tileSize + tileSize - size / 2 + 1, y * tileSize + tileSize /2 - size / 2 + 1, size);
            addItem(point);
            collectibles.push_back(point);
        }
    }
    if(y < arrayHeight - 1){
        if(map[y + 1][x] == 0){
            Point *point = new Point(x * tileSize + tileSize / 2 - size / 2 + 1, y * tileSize + tileSize - size / 2 + 1, size);
            addItem(point);
            collectibles.push_back(point);
        }
    }
    
    addItem(point);
    collectibles.push_back(point);
}

void Map::removeCollectible(Collectible *collectible) {
    collectibles.removeOne(collectible);
    this->removeItem(collectible);
}

int Map::getWidth() {
    return width;
}

int Map::getHeight() {
    return height;
}

int Map::getTileSize() {
    return tileSize;
}

