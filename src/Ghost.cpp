#include "Ghost.h"
#include "Pac.h"
#include "AStar.h"
#include <QDebug>
#include <QTimer>
#include <cstdlib>
#include <ctime>

Ghost::Ghost(int x, int y, int speed, Map *map, Direction direction, int size) : Character(x, y, speed, QVector<QPixmap>(), map, direction, size) {
    this->state = WAIT;
    colorizeEffect = new QGraphicsColorizeEffect(this);
    colorizeEffect->setColor(Qt::white);  
    colorizeEffect->setStrength(0);
    this->setGraphicsEffect(colorizeEffect);
    updateAppearance();
}

bool Ghost::checkCollisionWithPac() {
    if (this->collidesWithItem(target)) {
        return true;
    }
    return false;
}

void Ghost::chase() {
    this->setTarget();
    AStar aStar;
    Direction towardsPacman = aStar.findPath(x, y, target->getX(), target->getY(), map, map->getTileSize());
    if (towardsPacman != NO_DIRECTION) {
        nextDirection = towardsPacman;
    }
}

void Ghost::setTarget() {
    for(Character* character : map->getCharacters()){
        if(dynamic_cast<Pac*>(character)){
            target = dynamic_cast<Pac*>(character);
        }
    }
}

void Ghost::runAway() {
    AStar aStar;
    
    if(aStar.getDistance(x, y, target->getX(), target->getY()) > range){
        this->scatter();
        return;
    }
    Direction towardsPacman = aStar.findPath(x, y, target->getX(), target->getY(), map, map->getTileSize());
    std::srand(std::time(nullptr));

    std::vector<Direction> directions = {UP, DOWN, LEFT, RIGHT};

    directions.erase(std::remove(directions.begin(), directions.end(), towardsPacman), directions.end());

    while (!directions.empty()) {
        int randomIndex = std::rand() % directions.size();
        Direction randomDirection = directions[randomIndex];

        int newX = x;
        int newY = y;
        switch (randomDirection) {
            case UP:
                newY -= map->getTileSize();
                break;
            case DOWN:
                newY += map->getTileSize();
                break;
            case LEFT:
                newX -= map->getTileSize();
                break;
            case RIGHT:
                newX += map->getTileSize();
                break;
            default:
                break;
        }

        if (newX >= 0 && newY >= 0 && newX < map->getWidth() && newY < map->getHeight() && map->getTypeOfTopObject(newX, newY) != WALL) {
            nextDirection = randomDirection;
            return;
        } else {
            directions.erase(directions.begin() + randomIndex);
        }
        nextDirection = NO_DIRECTION;

    }
}
    


void Ghost::scatter() {
    if(this->nextDirection == NO_DIRECTION){
        this->state = SCATTER;
        this->nextDirection = this->direction;
    }
}

void Ghost::returnHome() {
    AStar aStar;
    Direction towardsHome = aStar.findPath(x, y, homeX, homeY, map, map->getTileSize());
    nextDirection = towardsHome;
    if (nextDirection == NO_DIRECTION)
    {
        this->setState(WAIT);
        this->nextDirection = this->direction;
    }
}

void Ghost::ai(){
    switch (state) {
        case WAIT:
            break;
        case GO_TO_CORNER:
            scatter();
            break;
        case CHASE:
            chase();
            break;
        case SCATTER:
            scatter();
            break;
        case FRIGHTENED:
            runAway();
            break;
        case DEAD:
            returnHome();
            break;
        case BEGINING:
            break;
    }
}
Ghost::GhostState Ghost::getState() {
    return state;
}

void Ghost::setState(GhostState state) {
    this->state = state;
    updateAppearance();
    if (state == FRIGHTENED)
    {
        QTimer::singleShot(5000, this, [=](){
            if (this->state == FRIGHTENED) {
                this->setState(CHASE);
            }
        });
    }
    if(state == WAIT){
        QTimer::singleShot(3000, this, [=](){
            this->setState(CHASE);
        });
    }
    if(state == BEGINING){
        QTimer::singleShot(this->startTimer, this, [=](){
            this->setState(GO_TO_CORNER);
        });
    }
    
}
void Ghost::updateAppearance() {
    switch (state) {
        case FRIGHTENED: 
            colorizeEffect->setStrength(0.5);
            break;
        case DEAD:
            colorizeEffect->setStrength(0.95);
            break;
        default:
            colorizeEffect->setStrength(0);
            break;
    }
}