#include "RandomTreeNode.h"

#include <Exceptions/NotImplementedException.h>
#include <RRCCommon/Range.h>

RandomTreeNode::RandomTreeNode()
{

}

RandomTreeNode::RandomTreeNode(const State &state) : Node(state)
{

}

std::unordered_set<Node *> RandomTreeNode::getChildren() const
{
    return m_children;
}

void RandomTreeNode::addChild(Node *child) {
    if (m_children.find(child) == m_children.end()) {
        m_children.insert(child);
    }
}

void RandomTreeNode::removeChild(Node *child) {
    if (m_children.find(child) != m_children.end()) {
        m_children.erase(child);
    }
}

unsigned int RandomTreeNode::getNumOfChildren() const
{
    return m_children.size();
}

Node *RandomTreeNode::getLeftNode() const
{
    return nullptr;
}

void RandomTreeNode::setLeftNode(Node *leftNode)
{

}
Node *RandomTreeNode::getRightNode() const
{
    return nullptr;
}

void RandomTreeNode::setRightNode(Node *rightNode)
{

}

unsigned int RandomTreeNode::getSplit() const
{
    throw NotImplementedException();
}

void RandomTreeNode::setSplit(unsigned int split)
{
    throw NotImplementedException();
}

Range RandomTreeNode::getRange() const
{
    throw NotImplementedException();
}

void RandomTreeNode::setRange(const Range &range)
{
    throw NotImplementedException();
}
