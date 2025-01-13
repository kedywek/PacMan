#pragma once

#include <QGraphicsView>
#include <QGraphicsScene>
#include "Map.h"


class GameWindow : public QGraphicsView {
    Q_OBJECT

public:
    GameWindow(QWidget *parent = nullptr);
    void setupGame(size_t width, size_t height);

private:
    Map *map;
};