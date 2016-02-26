#ifndef NODE_H
#define NODE_H

#include "State.h"
#include <unordered_set>
class Range;

class Node {
  public:
    Node();
    Node(const State &state);
    virtual ~Node();

    Node *getParent() const;
    void setParent(Node *value);

    State getState() const;
    void setState(const State &value);

    float distToOtherNode(Node *neighbor);
    Position getPos() const;

    virtual std::unordered_set<Node *> getChildren() const = 0;
    virtual void addChild(Node *child) = 0;
    virtual void removeChild(Node *child) = 0;
    virtual unsigned int getNumOfChildren() const = 0;

    virtual Node *getLeftNode() const = 0;
    virtual void setLeftNode(Node *leftNode) = 0;
    virtual Node *getRightNode() const = 0;
    virtual void setRightNode(Node *rightNode) = 0;

    virtual unsigned int getSplit() const = 0;
    virtual void setSplit(unsigned int split) = 0;

    virtual Range getRange() const = 0;
    virtual void setRange(const Range &range) =0;

protected:
    Node *m_parent;
    State m_state;
};

#endif // NODE_H
