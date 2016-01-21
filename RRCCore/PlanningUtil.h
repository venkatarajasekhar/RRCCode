#ifndef PLANNINGUTIL_H
#define PLANNINGUTIL_H

class Node;

class PlanningUtil
{
public:
    PlanningUtil();
    ~PlanningUtil();
    static bool IsCollision(Node *startNode, Node *endNode);
};

#endif // PLANNINGUTIL_H
