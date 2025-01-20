#pragma once
#include <QGraphicsItemGroup>
#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QVector>
#include "Character.h"
#include "Collectible.h"
#include "Types.h"
#include "Direction.h"

#define ARRAY_WIDTH 25
#define ARRAY_HEIGHT 25

#define MAP_ARRAY {\
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},\
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},\
    {1, 0, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 0, 1},\
    {1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1},\
    {1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1},\
    {1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1},\
    {1, 0, 0, 0, 1, 1, 1, 0, 1, 0, 1, 1, 0, 1, 1, 0, 0, 0, 1, 1, 1, 0, 1, 0, 1},\
    {1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1},\
    {1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1},\
    {1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1},\
    {1, 0, 0, 0, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 0, 0, 0, 1},\
    {1, 1, 1, 1, 1, 0, 0, 0, 1, 0, 1, 1, 0, 1, 1, 0, 1, 0, 0, 0, 1, 1, 1, 1, 1},\
    {0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0},\
    {1, 1, 1, 1, 1, 0, 0, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 0, 0, 1, 1, 1, 1, 1},\
    {1, 0, 0, 0, 1, 0, 1, 1, 1, 0, 0, 0, 2, 0, 0, 0, 1, 1, 1, 0, 1, 0, 0, 0, 1},\
    {1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1},\
    {1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1},\
    {1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1},\
    {1, 0, 0, 0, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 1, 0, 0, 0, 1},\
    {1, 0, 1, 0, 0, 0, 1, 0, 1, 1, 0, 1, 0, 1, 0, 1, 1, 0, 1, 0, 0, 0, 1, 0, 1},\
    {1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1},\
    {1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1},\
    {1, 0, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 0, 1},\
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},\
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},\
}

class Character;
class Collectible;

class Map: public QGraphicsScene{
    Q_OBJECT

public:
    Map(QObject *parent = nullptr, size_t width = 800, size_t height = 600);
    class MapTile: public QGraphicsItemGroup{
    public:
        MapTile(unsigned int x,unsigned int y, unsigned int size);
        TypeOfObject getType();
        void setType(TypeOfObject type);
        unsigned int getX();
        unsigned int getY();
        unsigned int getSize();
    private:
        unsigned int x, y, size;
        TypeOfObject type;
    };
    class Wall: public MapTile{
    public:
        Wall(unsigned int x,unsigned int y, unsigned int size);
        void setNeighours(bool neighbours[8]);
    private:
        bool neighbours[8] = {false, false, false, false, false, false, false, false};
    };
    void setupMap();
    void update();
    QVector<Character*> getCharacters();
    QVector<Collectible*> getCollectibles();
    void addCharacter(Character* character);
    void addCollectible(Collectible* collectible);
    TypeOfObject getTypeOfTopObject(int x, int y);
    QGraphicsItem* getCharacterAt(int x, int y);
    QGraphicsItem* getCollectibleAt(int x, int y);
    void teleportCharacter(Character* character);
    void removeCollectible(Collectible* collectible);
    Direction findPath(Character* character, int targetX, int targetY);
    int getWidth();
    int getHeight();
    int getTileSize();
private:
    unsigned int width, height, tileSize, arrayWidth = ARRAY_WIDTH, arrayHeight = ARRAY_HEIGHT;
    unsigned int map[ARRAY_WIDTH][ARRAY_HEIGHT] = MAP_ARRAY;
    QVector<Character*> characters;
    QVector<Collectible*> collectibles;
    void setNeighbours(Wall* wall);
    void spawnPoints(unsigned int x, unsigned int y, unsigned int size);
};