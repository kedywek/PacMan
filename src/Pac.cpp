#include "Pac.h"
#include <QKeyEvent>
#include <QDebug>

Pac::Pac(int x, int y, int speed, Map* map, Direction direction, int size) : Character(x, y, speed, QVector<QPixmap>(), map, direction, size) {
    for (int i = 0; i < 1; i++) {
        QPixmap pixmap(QString(":/assets/pac/pac%0.png").arg(i));
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

void Pac::checkCollisionWithCollectibles() {
    QGraphicsItem *item = nullptr;
    QGraphicsItem *itemTop = nullptr;
    QGraphicsItem *itemBottom = nullptr;
    switch (this->getDirection()) {
        case UP:
            for (size_t i = this->speed; i > 0; i--) {
                item = map->getCollectibleAt(x + this->size/2, y + i);
                if (Collectible* collectible = dynamic_cast<Collectible*>(item)) {
                    map->removeCollectible(collectible);
                    delete collectible;
                }
                itemTop = map->getCollectibleAt(x, y + i + this->size/2);
                if (Collectible* collectible = dynamic_cast<Collectible*>(itemTop)) {
                    map->removeCollectible(collectible);
                    delete collectible;
                }
                itemBottom = map->getCollectibleAt(x + this->size, y + i + this->size/2);
                if (Collectible* collectible = dynamic_cast<Collectible*>(itemBottom)) {
                    map->removeCollectible(collectible);
                    delete collectible;
                }
            }
            break;
        case RIGHT:
            for (size_t i = this->speed; i > 0; i--) {
                item = map->getCollectibleAt(x + this->size - i, y + this->size/2);
                if (Collectible* collectible = dynamic_cast<Collectible*>(item)) {
                    map->removeCollectible(collectible);
                    delete collectible;
                }
                itemTop = map->getCollectibleAt(x + this->size/2 - i, y);
                if (Collectible* collectible = dynamic_cast<Collectible*>(itemTop)) {
                    map->removeCollectible(collectible);
                    delete collectible;
                }
                itemBottom = map->getCollectibleAt(x + this->size/2 - i, y + this->size);
                if (Collectible* collectible = dynamic_cast<Collectible*>(itemBottom)) {
                    map->removeCollectible(collectible);
                    delete collectible;
                }
            }
            break;
        case DOWN:
            for (size_t i = this->speed; i > 0; i--) {
                item = map->getCollectibleAt(x + this->size/2, y + this->size - i);
                if (Collectible* collectible = dynamic_cast<Collectible*>(item)) {
                    map->removeCollectible(collectible);
                    delete collectible;
                }
                itemTop = map->getCollectibleAt(x, y + this->size/2 - i );
                if (Collectible* collectible = dynamic_cast<Collectible*>(itemTop)) {
                    map->removeCollectible(collectible);
                    delete collectible;
                }
                itemBottom = map->getCollectibleAt(x + this->size, y + this->size/2 - i);
                if (Collectible* collectible = dynamic_cast<Collectible*>(itemBottom)) {
                    map->removeCollectible(collectible);
                    delete collectible;
                }
            }
            break;
        case LEFT:
            for (size_t i = this->speed; i > 0; i--) {
                item = map->getCollectibleAt(x + i, y + this->size/2);
                if (Collectible* collectible = dynamic_cast<Collectible*>(item)) {
                    map->removeCollectible(collectible);
                    delete collectible;
                }
                itemTop = map->getCollectibleAt(x + i + this->size/2, y);
                if (Collectible* collectible = dynamic_cast<Collectible*>(itemTop)) {
                    map->removeCollectible(collectible);
                    delete collectible;
                }
                itemBottom = map->getCollectibleAt(x + i + this->size/2, y + this->size);
                if (Collectible* collectible = dynamic_cast<Collectible*>(itemBottom)) {
                    map->removeCollectible(collectible);
                    delete collectible;
                }
            }
            break;
    }
}