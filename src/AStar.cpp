#include "AStar.h"
#include <queue>
#include <QSet>


AStar::AStarNode::AStarNode(int x, int y, int g, int h, AStarNode* parent, Direction direction) : x(x), y(y), g(g), h(h), parent(parent), direction(direction) {
    f = g + h;
}

bool AStar::AStarNode::operator==(const AStarNode& other) {
    return x == other.x && y == other.y;
}

bool AStar::AStarNode::operator<(const AStarNode& other) {
    return f < other.f;
}

bool AStar::AStarNode::operator>(const AStarNode& other) {
    return f > other.f;
}

unsigned int getDistance(int x, int y, int targetX, int targetY) {
    return abs(targetX - x) + abs(targetY - y);
}

bool AStar::CompareNodes::operator()(AStarNode* a, AStarNode* b) {
    return *a > *b;
}
unsigned int AStar::getDistance(int x, int y, int targetX, int targetY) {
    return abs(targetX - x) + abs(targetY - y);
}
Direction AStar::findPath(int x, int y, int targetX, int targetY, Map* map){
    std::priority_queue<AStarNode*, std::vector<AStarNode*>, CompareNodes> open;
    QSet<AStarNode*> closed;
    AStarNode start(x, y, 0, getDistance(x, y, targetX, targetY), nullptr, NO_DIRECTION);
    open.push(&start);

    while (!open.empty()) {
        AStarNode* current = open.top();
        open.pop();
        if (current->x == targetX && current->y == targetY) {
            while (current->parent->parent != nullptr) {
                current = current->parent;
            }
            return current->direction;
        }
        closed.insert(current);
        for (int i = 0; i < 4; i++) {
            int newX = current->x;
            int newY = current->y;
            int tileSize = map->getTileSize();
            Direction direction = static_cast<Direction>(i);
            switch (direction) {
                case UP:
                    newY -= tileSize;
                    break;
                case RIGHT:
                    newX -= tileSize;
                    break;
                case DOWN:
                    newY -= tileSize;
                    break;
                case LEFT:
                    newX += tileSize;
                    break;
                case NO_DIRECTION:
                    break;
            }
            if ((newX < -tileSize || newY < -tileSize || newX >= map->getWidth() + tileSize || newY >= map->getHeight() + tileSize) || map->getTypeOfTopObject(newX, newY) == WALL) {
                continue;
            }
        }

    }
    

}

