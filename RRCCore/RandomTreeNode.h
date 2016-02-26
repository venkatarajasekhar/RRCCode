#ifndef RANDOMTREENODE_H
#define RANDOMTREENODE_H

#include "RRCCommon/Node.h"

class RandomTreeNode : public Node {
  public:
    RandomTreeNode();
    RandomTreeNode(const State &state);

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
    std::unordered_set<Node *> m_children;
};

#endif // RANDOMTREENODE_H
