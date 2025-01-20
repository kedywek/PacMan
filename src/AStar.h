#pragma once
#include "Direction.h"
#include "Map.h"

class AStar {
protected:
    struct AStarNode{
        int x, y, g, h, f;
        AStarNode* parent;
        Direction direction;
        AStarNode(int x, int y, int g, int h, AStarNode* parent, Direction direction);
        bool operator==(const AStarNode& other);
        bool operator<(const AStarNode& other);
        bool operator>(const AStarNode& other);
    };
    struct CompareNodes {
        bool operator()(AStarNode* a, AStarNode* b);
    };
private:
    unsigned int getDistance(int x, int y, int targetX, int targetY);
public:
    AStar();
    Direction findPath(int x, int y, int targetX, int targetY, Map* map);
};
    
