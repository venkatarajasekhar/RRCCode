#ifndef NODE_H
#define NODE_H

#include "State.h"
#include <unordered_set>

class Node
{
public:
    Node();
    Node(Node *parent);
    Node(Node *parent, const State &state);
    Node(Node *parent, const State &state, const std::unordered_set<Node*> &children);
    virtual ~Node();

    virtual Node *getParent() const;
    virtual void setParent(Node *value);
    virtual std::unordered_set<Node *> getChildren() const;

    virtual void AddChild(Node *child);
    virtual void RemoveChild(Node *child);
    virtual unsigned int GetNumOfChildren() const;

    virtual State getState() const;
    virtual void setState(const State &value);

protected:
    std::unordered_set<Node *> children;
    Node *parent;

    State state;
};

#endif // NODE_H
