#pragma once
#include <QGraphicsPixmapItem>
#include <QVector>
#include <QPixmap>
#include <QObject>

class Map;
enum Direction {
    UP = 0,
    RIGHT = 1,
    DOWN = 2,
    LEFT = 3
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
    Map* map;
    int x, y, speed, currentSprite = 0;
    Direction direction, nextDirection;
    QVector<QPixmap> sprites;
    int size;
};