#ifndef RRCTREE_H
#define RRCTREE_H
#include "RRCCore/RandomTree.h"
#include "KalmanFilter.h"

class RRCTree : public RandomTree
{
public:
    RRCTree(const KalmanFilter &filter);
    Node *extend();

private:
    KalmanFilter m_kalmanFilter;
    float calculateCycleCost(const std::vector<Node *> &cyclePath) const;
    bool getPathBetweenNodes(Node *node1, Node *node2, std::vector<Node *> &path) const;
};

#endif // RRCTREE_H
