#pragma once
#include "Direction.h"
#include "Map.h"

class AStar {

protected:
    int size;
    struct AStarNode {
        int x, y, g, h, f;
        AStarNode* parent;
        Direction direction;
        int size;
        AStarNode(int x, int y, int g, int h, AStarNode* parent, Direction direction, int size);
        bool operator==(const AStarNode& other) const;
        bool operator<(const AStarNode& other) const;
        bool operator<=(const AStarNode& other) const;
        bool operator>(const AStarNode& other) const;
        bool operator>=(const AStarNode& other) const;
    };

    struct CompareNodes {
        bool operator()(AStarNode* a, AStarNode* b);
    };
    struct AStarNodeComparator {
        bool operator()(const AStar::AStarNode* a, const AStar::AStarNode* b) const;
    };
public:
    unsigned int getDistance(int x, int y, int targetX, int targetY);
    Direction findPath(int x, int y, int targetX, int targetY, Map* map, int size);
};