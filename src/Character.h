#pragma once
#include <QGraphicsPixmapItem>
#include <QVector>
#include <QPixmap>
#include <QObject>
#include "Map.h"
#include "Direction.h"  

class Map;


class Character : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
    Character(int x, int y, int speed, QVector<QPixmap> sprites, Map* map, Direction direction, int size);
    void move(int x, int y);
    virtual void move();
    void setDirection(Direction direction);
    void setSpeed(int speed);
    void setSprites(QVector<QPixmap> sprites);
    void nextSprite();
    void addSprite(QPixmap sprite);
    void setSprite(int index);
    void setNextDirection(Direction direction); 
    virtual void changeDirection();
    int getX();
    int getY();
    int getSpeed();
    Direction getDirection();
    bool collidesWithWall(Direction direction);
    int getSize();

private:
    QVector<QPixmap> sprites;

protected:
    Direction direction, nextDirection;
    Map* map;
    int x, y, speed, currentSprite = 0, size;
};