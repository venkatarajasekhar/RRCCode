#ifndef PLANNINGUTIL_H
#define PLANNINGUTIL_H

#include <vector>

class Node;
class Position;
class Area;

class PlanningUtil {
  public:
    PlanningUtil();
    ~PlanningUtil();
    static bool isCollisionWithObs(Node *startNode, Node *endNode);
    static bool isPositionCollideWithObs(const Area &obs, const Position &startPos, const Position &endPos);
    static float sceneVolume();

  private:
    static const float collisionCheckingResolution;
};

#endif // PLANNINGUTIL_H
