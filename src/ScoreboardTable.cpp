#include "ScoreboardTable.h"
#include <QGraphicsTextItem>

ScoreboardDisplay::ScoreboardDisplay(const QVector<QPair<QString, int>> &scores, QGraphicsView *view, QObject *parent)
    : QGraphicsScene(parent), view(view), scores(scores) {
    updateScoreboard();
}

void ScoreboardDisplay::updateScoreboard() {
    setBackgroundBrush(Qt::black);

    QGraphicsTextItem *title = new QGraphicsTextItem("Scoreboard");
    title->setFont(QFont("Arial", 24));
    title->setDefaultTextColor(Qt::yellow);
    addItem(title);
    title->setPos(view->width() / 2 - title->boundingRect().width() / 2, 50);

    int yOffset = 100;
    int count = 0;
    for (const auto &score : scores) {
        QGraphicsTextItem *scoreItem = new QGraphicsTextItem(QString::number(count + 1) + ". " + score.first + ": " + QString::number(score.second));
        scoreItem->setFont(QFont("Arial", 18));
        scoreItem->setDefaultTextColor(Qt::white);
        addItem(scoreItem);
        scoreItem->setPos(view->width() / 2 - scoreItem->boundingRect().width() / 2, yOffset);
        yOffset += 30;
        count++;
    }
}