#pragma once
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsTextItem>
#include <QVector>
#include <QPair>

class ScoreboardDisplay : public QGraphicsScene {
    Q_OBJECT

public:
    ScoreboardDisplay(const QVector<QPair<QString, int>> &scores, QGraphicsView *view, QObject *parent = nullptr);

private:
    QGraphicsView *view;
    QVector<QPair<QString, int>> scores;
    void updateScoreboard();
};