#pragma once
#include <QGraphicsItemGroup>
#include "Types.h"

class Collectible: public QGraphicsItemGroup{
    public:
        Collectible(unsigned int x, unsigned int y, unsigned int size);
        unsigned int getX();
        unsigned int getY();
        unsigned int getSize();
        TypeOfObject getType();
        void setType(TypeOfObject type);
    private:
        unsigned int x, y, size;
        TypeOfObject type;
    };