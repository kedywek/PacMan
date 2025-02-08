#include "Scoreboard.h"
#include "ScoreboardTable.h"
#include <QGraphicsTextItem>
#include <QGraphicsProxyWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QGraphicsWidget>

Scoreboard::Scoreboard(int score, QGraphicsView *view, QObject *parent)
    : QGraphicsScene(parent), score(score), view(view) {
        
    setBackgroundBrush(Qt::black);
    scoreText = new QGraphicsTextItem("Your Score: " + QString::number(score));
    scoreText->setFont(QFont("Arial", 24));
    scoreText->setDefaultTextColor(Qt::yellow);
    addItem(scoreText);
    scoreText->setPos(view->width() / 2 - scoreText->boundingRect().width() / 2, 50);

    QGraphicsTextItem *namePrompt = new QGraphicsTextItem("Enter your name:");
    namePrompt->setFont(QFont("Arial", 18));
    namePrompt->setDefaultTextColor(Qt::yellow);
    addItem(namePrompt);
    namePrompt->setPos(view->width() / 2 - namePrompt->boundingRect().width() / 2, 150);

    nameInput = new QLineEdit();
    nameInput->setFixedWidth(200);
    QGraphicsProxyWidget *proxy = addWidget(nameInput);
    proxy->setPos(view->width() / 2 - nameInput->width() / 2, 200);

    QPushButton *submitButton = new QPushButton("Submit");
    QGraphicsProxyWidget *buttonProxy = addWidget(submitButton);
    buttonProxy->setPos(view->width() / 2 - submitButton->width() / 2, 250);
    connect(submitButton, &QPushButton::clicked, this, &Scoreboard::submitName);

    loadScores();
}

void Scoreboard::submitName() {
    QString name = nameInput->text();
    if (!name.isEmpty()) {
        scores.append(qMakePair(name, score));
        saveScores();
        displayScoreboard();
    }
}

void Scoreboard::loadScores() {
    QFile file("scores.txt");
    if (!file.exists()) {
        file.open(QIODevice::WriteOnly);
        file.close();
    }
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        while (!in.atEnd()) {
            QString line = in.readLine();
            QStringList parts = line.split(",");
            if (parts.size() == 2) {
                bool ok;
                QString name = parts[0];
                int score = parts[1].toInt(&ok);
                if (ok) {
                    scores.append(qMakePair(name, score));
                }
            }
        }
        file.close();
    }
}

void Scoreboard::saveScores() {
    QFile file("scores.txt");
    if (file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) {
        QTextStream out(&file);
        for (const auto &score : scores) {
            out << score.first << "," << score.second << "\n";
        }
        file.close();
    }
}

void Scoreboard::displayScoreboard() {
    ScoreboardDisplay *scoreboardDisplay = new ScoreboardDisplay(scores, view);
    view->setScene(scoreboardDisplay);
}