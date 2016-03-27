#ifndef RRTTREE_H
#define RRTTREE_H
#include "RRCCore/RandomTree.h"

class RRTTree : public RandomTree
{
public:
    RRTTree();
    Node *extend();
};

#endif // RRTTREE_H
