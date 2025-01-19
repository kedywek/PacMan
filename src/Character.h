#pragma once
#include <QGraphicsPixmapItem>
#include <QVector>
#include <QPixmap>
#include <QObject>
#include "Map.h"

class Map;
enum Direction {
    UP = 0,
    RIGHT = 1,
    DOWN = 2,
    LEFT = 3,
    NO_DIRECTION = 4
};

class Character : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
    Character(int x, int y, int speed, QVector<QPixmap> sprites, Map* map, Direction direction, int size);
    void move(int x, int y);
    void move();
    void setDirection(Direction direction);
    void setSpeed(int speed);
    void setSprites(QVector<QPixmap> sprites);
    void nextSprite();
    void addSprite(QPixmap sprite);
    void setSprite(int index);
    void setNextDirection(Direction direction); 
    void changeDirection();
    int getX();
    int getY();
    int getSpeed();
    Direction getDirection();
    bool collidesWithWall(Direction direction);
    int getSize();

private:
    Direction direction, nextDirection;
    QVector<QPixmap> sprites;

protected:
    Map* map;
    int x, y, speed, currentSprite = 0, size;
};