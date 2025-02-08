#include "GameWindow.h"
#include <QApplication>
#include "Map.h"
#include "Pac.h"
#include <QTimer>
#include <QDebug>


GameWindow::GameWindow(QWidget *parent) : QGraphicsView(parent), scoreboard(nullptr) {}

void GameWindow::setState(GameState state) {
    this->state = state;
}

GameState GameWindow::getState() {
    return state;
}

void GameWindow::setupGame(size_t width, size_t height) {
    map = new Map(this, width, height);
    setScene(map);
    setFixedSize(width + 2 * LEFT_MARGIN, height + TOP_MARGIN);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setViewportMargins(0, 0, 0, 0);
    map->setupMap();
    show();
}

void GameWindow::update() {
    if(map->getState() == WIN || map->getState() == GAME_OVER){
        showScoreboard();
    }else{
        map->update();
    }
}



void GameWindow::showScoreboard() {
    setState(GAME_STATE_GAMEOVER);
    if (scoreboard) {
        delete scoreboard;
    }
    scoreboard = new Scoreboard(map->getScore(), this);
    setScene(scoreboard);
}

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    GameWindow game;
    game.setupGame(1000, 800);
    game.setState(GAME_STATE_PLAY);
    QTimer timer;
    QObject::connect(&timer, &QTimer::timeout, [&]() {
        if (game.getState() == GAME_STATE_PLAY) {
            game.update();
        }
    });
    timer.start(50);

    return a.exec();
}