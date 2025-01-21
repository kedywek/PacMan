#include "Star.h"
#include <QPolygonF>
#include <QBrush>
#include <QPen>
#include <cmath>

Star::Star(unsigned int x, unsigned int y, unsigned int size) : Collectible(x, y, size) {
    QPolygonF starPolygon;
    double angle = 0;
    double angleStep = M_PI / 4; 

    for (int i = 0; i < 8; ++i) {
        double radius = (i % 2 == 0) ? size / 2.0 : size / 4.0;
        double px = x + size / 2.0 + radius * cos(angle);
        double py = y + size / 2.0 + radius * sin(angle);
        starPolygon << QPointF(px, py);
        angle += angleStep;
    }
    QGraphicsPolygonItem *star = new QGraphicsPolygonItem(starPolygon);
    star->setBrush(QBrush(Qt::white));
    star->setPen(QPen(Qt::NoPen));
    this->addToGroup(star);
    this->setType(STAR);
}

