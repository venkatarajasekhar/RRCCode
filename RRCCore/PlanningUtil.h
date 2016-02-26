#ifndef PLANNINGUTIL_H
#define PLANNINGUTIL_H

class Node;
class Position;
class Area;

class PlanningUtil
{
public:
    PlanningUtil();
    ~PlanningUtil();
    static bool isCollisionWithObs(Node *startNode, Node *endNode);

private:
    static const float collisionCheckingResolution;
    static bool isPositionCollideWithObs(const Area &obs, const Position &startPos, const Position &endPos);
};

#endif // PLANNINGUTIL_H
