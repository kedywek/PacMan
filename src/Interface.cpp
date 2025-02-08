#include "Interface.h"
#include <QFont>
#include <QPixmap>

Interface::Interface(int width, int height, QGraphicsItem* parent)
    : QGraphicsWidget(parent) {
    setGeometry(0, 0, width, height);

    scoreText = new QGraphicsTextItem("Score: 0", this);
    scoreText->setDefaultTextColor(Qt::white);
    scoreText->setFont(QFont("Arial", 16));
    scoreText->setPos(10, 10);

    for (int i = 0; i < maxLives; ++i) {
        QGraphicsPixmapItem* lifeIcon = new QGraphicsPixmapItem(QPixmap(":/assets/pac/pac0.png"), this);
        lifeIcon->setPos(10 + i * 40, 50);
        livesIcons.append(lifeIcon);
    }
}

void Interface::updateScore(int score) {
    scoreText->setPlainText("Score: " + QString::number(score));
}

void Interface::updateLives(int lives) {
    for (int i = 0; i < maxLives; ++i) {
        livesIcons[i]->setVisible(i < lives);
    }
}