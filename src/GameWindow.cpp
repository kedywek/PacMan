#include "GameWindow.h"
#include <QApplication>
#include "Map.h"
#include "Pac.h"
#include <QTimer>


GameWindow::GameWindow(QWidget *parent) : QGraphicsView(parent) {}

void GameWindow::setState(State state) {
    this->state = state;
}

State GameWindow::getState() {
    return state;
}

void GameWindow::setupGame(size_t width, size_t height) {
    map = new Map(this, width, height);
    setScene(map);
    setFixedSize(width, height);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setViewportMargins(0, 0, 0, 0);
    map->setupMap();
    Pac *pac = new Pac(0, 0, 0, 5);
    map->addItem(pac);
    map->addCharacter(pac);
    pac->setFocus();
    show();
}

void GameWindow::update() {
    map->update();
}

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    GameWindow game;
    game.setupGame(1000, 800);
    game.setState(PLAYING);
    QTimer timer;
    QObject::connect(&timer, &QTimer::timeout, [&]() {
        if (game.getState() == PLAYING) {
            game.update();
        }
    });
    timer.start(1000);

    return a.exec();
}