#include "AStar.h"
#include <set>
#include <queue>


AStar::AStarNode::AStarNode(int x, int y, int g, int h, AStarNode* parent, Direction direction, int size) : x(x), y(y), g(g), h(h), parent(parent), direction(direction), size(size) {
    f = g + h;
}

bool AStar::AStarNode::operator==(const AStarNode& other) const {
    return x == other.x && y == other.y;
}

bool AStar::AStarNode::operator<(const AStarNode& other) const{
    return f < other.f;
}

bool AStar::AStarNode::operator<=(const AStarNode& other) const{
    return f <= other.f;
}

bool AStar::AStarNode::operator>(const AStarNode& other) const{
    return f > other.f;
}

bool AStar::AStarNode::operator>=(const AStarNode& other) const{
    return f >= other.f;
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

bool AStar::AStarNodeComparator::operator()(const AStar::AStarNode* a, const AStar::AStarNode* b) const {
        if (a->x < b->x){
            return true;
        }
        if (a->x > b->x) {
            return false;
        }
        return a->y < b->y;
}


Direction AStar::findPath(int x, int y, int targetX, int targetY, Map* map, int size) {
    std::priority_queue<AStarNode*, std::vector<AStarNode*>, CompareNodes> open;
    std::set<AStarNode*, AStarNodeComparator> closed;
    AStarNode* start = new AStarNode(x, y, 0, getDistance(x, y, targetX, targetY), nullptr, NO_DIRECTION, size);
    open.push(start);

    while (!open.empty()) {
        AStarNode* current = open.top();
        AStarNode* node;
        AStarNode* neighbour;
        open.pop();
        if (current->x >= targetX && current->x < targetX + size && current->y >= targetY && current->y < targetY + size) {
            Direction direction = current->direction;
            while (current->parent != nullptr && current->parent->parent != nullptr) {
                current = current->parent;
                direction = current->direction;
            }
            delete current;
            return direction;
        }       
        closed.insert(current);
        for (int i = 0; i < 4; i++) {
            int newX = current->x;
            int newY = current->y;
            Direction direction = static_cast<Direction>(i);
            switch (direction) {
                case UP:
                    newY -= size;
                    break;
                case RIGHT:
                    newX += size;
                    break;
                case DOWN:
                    newY += size;
                    break;
                case LEFT:
                    newX -= size;
                    break;
                case NO_DIRECTION:
                    break;
            }
            if ((newX < 0 || newY < 0 || newX >= map->getWidth() || newY >= map->getHeight())) {
                continue;
            }
            if (map->getTypeOfTopObject(newX, newY) == WALL) {
                continue;
            }
            int newG = current->g + size;
            int newH = getDistance(newX, newY, targetX, targetY);
            neighbour = new AStarNode(newX, newY, newG, newH, current, direction, size);
            if (closed.find(neighbour) != closed.end()) {
                delete neighbour;
                continue;
            }
            bool inOpenList = false;
            std::vector<AStarNode*> tempOpen;
            while (!open.empty()) {
                node = open.top();
                open.pop();
                if (*node == *neighbour) {
                    inOpenList = true;
                    if (*neighbour < *node) {
                        node->g = neighbour->g;
                        node->f = neighbour->f;
                        node->parent = neighbour->parent;
                        node->direction = neighbour->direction;
                    }
                    tempOpen.push_back(node);
                    delete neighbour;
                    break;
                }
                tempOpen.push_back(node);
            }
            for (AStarNode* nodeInTemp : tempOpen) {
                open.push(nodeInTemp);
            }
            if (!inOpenList) {
                open.push(neighbour);
            }
        }
    }

    while (!open.empty()) {
        delete open.top();
        open.pop();
    }
    for (AStarNode* node : closed) {
        delete node;
    }

    return NO_DIRECTION;
}