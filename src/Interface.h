#pragma once
#include <QGraphicsTextItem>
#include <QGraphicsWidget>
#include <QGraphicsPixmapItem>
#include <QVector>

class Interface : public QGraphicsWidget {
    
public:
    Interface(int width, int height, QGraphicsItem* parent = nullptr);

    void updateScore(int score);
    void updateLives(int lives);

private:
    QGraphicsTextItem* scoreText;
    QVector<QGraphicsPixmapItem*> livesIcons;
    int maxLives = 3;
};