#include "Point.h"
#include <QGraphicsEllipseItem>
#include <QBrush>
#include <QPen>


Point::Point(unsigned int x, unsigned int y, unsigned int size) : Collectible(x, y, size) {
    QGraphicsEllipseItem *point = new QGraphicsEllipseItem(x, y, size, size);
    point->setBrush(QBrush(Qt::yellow));
    point->setPen(QPen(Qt::NoPen));
    this->addToGroup(point);
    this->setType(POINT);
}
