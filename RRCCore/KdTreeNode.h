#ifndef KDTREENODE_H
#define KDTREENODE_H

#include "RRCCommon/Node.h"
#include "RRCCommon/Range.h"

class KdTreeNode : public Node
{
public:
    KdTreeNode();
    KdTreeNode(const State &state);

    std::unordered_set<Node *> getChildren() const;
    void addChild(Node *child);
    void removeChild(Node *child);
    unsigned int getNumOfChildren() const;

    Node *getLeftNode() const;
    void setLeftNode(Node *leftNode);
    Node *getRightNode() const;
    void setRightNode(Node *rightNode);

    unsigned int getSplit() const;
    void setSplit(unsigned int split);

    Range getRange() const;
    void setRange(const Range &range);

private:
    Node *m_leftNode;
    Node *m_rightNode;
    unsigned int m_split;
    Range m_range;
};

#endif // KDTREENODE_H
