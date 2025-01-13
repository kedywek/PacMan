#include "GameWindow.h"
#include <QApplication>
#include "Map.h"

GameWindow::GameWindow(QWidget *parent) : QGraphicsView(parent) {}

void GameWindow::setupGame(size_t width, size_t height) {
    map = new Map(this, width, height);
    setScene(map);
    setFixedSize(width, height);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setViewportMargins(0, 0, 0, 0);
    map->setupMap();
    show();
}

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    GameWindow game;
    game.setupGame(1000, 1000);
    return a.exec();
}