#ifndef NODE_H
#define NODE_H

#include "State.h"
#include <unordered_set>
#include <RRCCommon/Range.h>
#include <iostream>
#include <sstream>

class Node {
  public:
    Node();
    Node(const State &state);
    virtual ~Node();

    int getId() const;
    void setId(int Id);

    Node *getParent() const;
    void setParent(Node *value);

    State getState() const;
    void setState(const State &value);

    float distToOtherNode(const Node *neighbor) const;
    float distSquaredToOtherNode(const Node *neighbor) const;
    Position getPos() const;

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
    bool isNodRangeIntersectWithBall(const Node *node, float radius) const;

    std::string toString();
    friend std::ostream &operator<<(std::ostream &os, const Node *node);
    friend std::stringstream &operator<<(std::stringstream &ss, const Node *node);

  private:
    int m_Id; // starting from 1
    Node *m_parent;
    State m_state;

    // Used for Kd tree
    Node *m_leftNode;
    Node *m_rightNode;
    unsigned int m_split;
    Range m_range;

    // Used for Random tree
    std::unordered_set<Node *> m_children;
};

#endif // NODE_H
