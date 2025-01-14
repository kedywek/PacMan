#pragma once

#include <QGraphicsView>
#include <QGraphicsScene>
#include "Map.h"
enum State {
    PLAYING,
    PAUSED,
    GAME_OVER
};

class GameWindow : public QGraphicsView {
    Q_OBJECT

public:
    GameWindow(QWidget *parent = nullptr);
    void setupGame(size_t width, size_t height);
    State getState();
    void update();
    void setState(State state);

private:
    State state;
    Map *map;
};