#pragma once
#include <QGraphicsPixmapItem>
#include <QVector>
#include <QPixmap>
#include <QObject>

enum Direction {
    UP = 0,
    RIGHT = 1,
    DOWN = 2,
    LEFT = 3
};

class Character : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
    Character(int x, int y, int direction, int speed, QVector<QPixmap> sprites);
    void move(int x, int y);
    void move();
    void setDirection(int direction);
    void setSpeed(int speed);
    void setSprites(QVector<QPixmap> sprites);
    void addSprite(QPixmap sprite);
    void setSprite(int index);

private:
    int x, y, direction, speed, currentSprite = 0;
    QVector<QPixmap> sprites;
};