#include "Node.h"

Node::Node() : m_parent(nullptr)
{
    m_state = State(Position(0,0));
}

Node::Node(const State &state) : m_parent(nullptr), m_state(state)
{

}

Node::~Node() {

}
Node* Node::getParent() const {
    return m_parent;
}

void Node::setParent(Node *value) {
    m_parent = value;
}


State Node::getState() const
{
    return m_state;
}

void Node::setState(const State &value)
{
    m_state = value;
}

float Node::distToOtherNode(Node *neighbor)
{
    return m_state.getPos().distToOtherPos(neighbor->getState().getPos());
}

Position Node::getPos() const
{
    return m_state.getPos();
}







