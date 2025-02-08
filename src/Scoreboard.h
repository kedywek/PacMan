#pragma once

#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QLineEdit>
#include <QGraphicsView>
#include <QFile>
#include <QTextStream>
#include <QVector>
#include <QPair>

class Scoreboard : public QGraphicsScene {
    Q_OBJECT

public:
    Scoreboard(int score, QGraphicsView *view, QObject *parent = nullptr);
    void displayScoreboard();

private slots:
    void submitName();

private:
    int score;
    QGraphicsView *view;
    QGraphicsTextItem *scoreText;
    QLineEdit *nameInput;
    QVector<QPair<QString, int>> scores;

    void loadScores();
    void saveScores();
};