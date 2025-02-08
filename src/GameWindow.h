#pragma once

#include <QGraphicsView>
#include <QGraphicsScene>
#include "Map.h"
#include "GameState.h"
#include "Scoreboard.h"

class GameWindow : public QGraphicsView {
    Q_OBJECT

public:
    GameWindow(QWidget *parent = nullptr);
    void setupGame(size_t width, size_t height);
    GameState getState();
    void update();
    void setState(GameState GameState);
    void showScoreboard();

private:
    GameState state;
    Map *map;
    Scoreboard *scoreboard;
};