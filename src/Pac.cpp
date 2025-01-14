#include "Pac.h"
#include <QKeyEvent>
#include <QDebug>

Pac::Pac(int x, int y, int direction, int speed) : Character(x, y, direction, speed, QVector<QPixmap>()) {
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
            qDebug() << "Pac moved up";
            break;
        case Qt::Key_Down:
            moveDown();
            qDebug() << "Pac moved down";
            break;
        case Qt::Key_Left:
            moveLeft();
            qDebug() << "Pac moved left";
            break;
        case Qt::Key_Right:
            moveRight();
            qDebug() << "Pac moved right";
            break;
    }
}
void Pac::moveUp() {
    setDirection(UP);
}
void Pac::moveDown() {
    setDirection(DOWN);
}
void Pac::moveLeft() {
    setDirection(LEFT);
}
void Pac::moveRight() {
    setDirection(RIGHT);
}