#include "Node.h"

Node::Node() : parent(0) {

}

Node::Node(Node *parent)
{
    this->parent = parent;
}

Node::Node(Node *parent, const State &state)
{
    this->parent = parent;
    this->state = state;
}

Node::Node(Node *parent, const State &state, const std::unordered_set<Node *> &children)
{
    this->parent = parent;
    this->state = state;
    this->children = children;
}

Node::~Node() {

}
Node *Node::getParent() const {
    return parent;
}

void Node::setParent(Node *value) {
    parent = value;
}

std::unordered_set<Node*>  Node::getChildren() const
{
    return children;
}

void Node::AddChild(Node *child) {
    if (children.find(child) == children.end()) {
        children.insert(child);
    }
}

void Node::RemoveChild(Node *child) {
    if (children.find(child) != children.end()) {
        children.erase(child);
    }
}

unsigned int Node::GetNumOfChildren() const
{
    return children.size();
}
State Node::getState() const
{
    return state;
}

void Node::setState(const State &value)
{
    state = value;
}



