#ifndef RRTSTARTREE_H
#define RRTSTARTREE_H
#include "RRCCore/RandomTree.h"

class RRTStarTree : public RandomTree
{
public:
    RRTStarTree();
    Node *extend();

private:
    void rewireTree(std::vector<Node *> &nearNodes, Node *minNode);
};

#endif // RRTSTARTREE_H
