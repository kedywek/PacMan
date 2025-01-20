#include "Ghost.h"
#include "Pac.h"
#include "AStar.h"
#include <QDebug>

Ghost::Ghost(int x, int y, int speed, Map *map, Direction direction, int size) : Character(x, y, speed, QVector<QPixmap>(), map, direction, size) {
    this->setSprite(0);
    this->state = WAIT;
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
    Direction towardsPacman = aStar.findPath(x, y, target->getX(), target->getY(), map, map->getTileSize());
    Direction awayFromPacman = NO_DIRECTION;
    switch (towardsPacman) {
        case UP:
            awayFromPacman = DOWN;
            break;
        case DOWN:
            awayFromPacman = UP;
            break;
        case LEFT:
            awayFromPacman = RIGHT;
            break;
        case RIGHT:
            awayFromPacman = LEFT;
            break;
        default:
            break;
    }
    if (awayFromPacman != NO_DIRECTION) {
        nextDirection = awayFromPacman;
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
    }
}
Ghost::GhostState Ghost::getState() {
    return state;
}