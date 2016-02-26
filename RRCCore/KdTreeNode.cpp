#include "KdTreeNode.h"
#include <Exceptions/NotImplementedException.h>

KdTreeNode::KdTreeNode() : Node(), m_leftNode(nullptr), m_rightNode(nullptr), m_split(0)
{
    m_range = Range(m_state.getPos(), m_state.getPos());
}

KdTreeNode::KdTreeNode(const State &state) : Node(state), m_leftNode(nullptr), m_rightNode(nullptr), m_split(0)
{
    m_range = Range(m_state.getPos(), m_state.getPos());
}

std::unordered_set<Node*>  KdTreeNode::getChildren() const
{
    throw NotImplementedException();
}

void KdTreeNode::addChild(Node *child) {
    throw NotImplementedException();
}

void KdTreeNode::removeChild(Node *child) {
    throw NotImplementedException();
}

unsigned int KdTreeNode::getNumOfChildren() const
{
    return 2;
}

Node *KdTreeNode::getLeftNode() const
{
    return m_leftNode;
}

void KdTreeNode::setLeftNode(Node *leftNode)
{
    m_leftNode = leftNode;
}
Node *KdTreeNode::getRightNode() const
{
    return m_rightNode;
}

void KdTreeNode::setRightNode(Node *rightNode)
{
    m_rightNode = rightNode;
}

unsigned int KdTreeNode::getSplit() const
{
    return m_split;
}

void KdTreeNode::setSplit(unsigned int split)
{
    m_split = split;
}
Range KdTreeNode::getRange() const
{
    return m_range;
}

void KdTreeNode::setRange(const Range &range)
{
    m_range = range;
}
