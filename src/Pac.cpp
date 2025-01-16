#include "Pac.h"
#include <QKeyEvent>
#include <QDebug>

Pac::Pac(int x, int y, int speed, Map* map, Direction direction, int size) : Character(x, y, speed, QVector<QPixmap>(), map, direction, size) {
    for (int i = 0; i < 1; i++) {
        QPixmap pixmap(QString(":/assets/pac%0.png").arg(i));
        if (pixmap.isNull()) {
            qDebug() << "Failed to load pixmap for pac" << i;
            throw std::runtime_error("Failed to load pixmap for pac");
        } else {
            this->addSprite(pixmap);
        }
    }
    this->setSprite(0);
    setFlag(QGraphicsItem::ItemIsFocusable);
    setFocus();
    qDebug() << "Pac initialized at position:" << x << y;
}

void Pac::keyPressEvent(QKeyEvent *event) {
    switch (event->key()) {
        case Qt::Key_Up:
            moveUp();
            break;
        case Qt::Key_Down:
            moveDown();
            break;
        case Qt::Key_Left:
            moveLeft();
            break;
        case Qt::Key_Right:
            moveRight();
            break;
    }
}
void Pac::moveUp() {
    setNextDirection(UP);
}
void Pac::moveDown() {
    setNextDirection(DOWN);
}
void Pac::moveLeft() {
    setNextDirection(LEFT);
}
void Pac::moveRight() {
    setNextDirection(RIGHT);
}