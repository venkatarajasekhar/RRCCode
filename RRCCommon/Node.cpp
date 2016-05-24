#include "LogUtil.h"
#include "Node.h"
#include "ostream"
#include "sstream"

Node::Node() : m_Id(0), m_parent(nullptr), m_leftNode(nullptr), m_rightNode(nullptr), m_split(0) {
    m_state = State(Position(0,0));
    m_range = Range(m_state.getPos(), m_state.getPos());
}

Node::Node(const State &state) : m_Id(0), m_parent(nullptr), m_state(state), m_leftNode(nullptr), m_rightNode(nullptr), m_split(0) {
    m_range = Range(m_state.getPos(), m_state.getPos());
}

Node::~Node() {

}

int Node::getId() const {
    return m_Id;
}

Node* Node::getParent() const {
    return m_parent;
}

void Node::setParent(Node *value) {
    m_parent = value;
}


State Node::getState() const {
    return m_state;
}

void Node::setState(const State &value) {
    m_state = value;
}

float Node::distToOtherNode(const Node *neighbor) const {
    return m_state.getPos().distToOtherPos(neighbor->getState().getPos());
}

float Node::squaredDistToOtherNode(const Node *neighbor) const {
    return m_state.getPos().squaredDistToOtherPos(neighbor->getState().getPos());
}

Position Node::getPos() const {
    return m_state.getPos();
}

std::unordered_set<Node *> Node::getChildren() const {
    return m_children;
}

void Node::addChild(Node *child) {
    if (m_children.find(child) == m_children.end()) {
        m_children.insert(child);
    } else {
        std::stringstream ss;
        ss << "Trying to add " << child << "to " << this << ", but it already exists.";
        LogUtil::warn(ss.str());
    }
}

void Node::removeChild(Node *child) {
    if (m_children.find(child) != m_children.end()) {
        m_children.erase(child);
    }
}

unsigned int Node::getNumOfChildren() const {
    return m_children.size();
}

Node *Node::getLeftNode() const {
    return m_leftNode;
}

void Node::setLeftNode(Node *leftNode) {
    m_leftNode = leftNode;
}
Node *Node::getRightNode() const {
    return m_rightNode;
}

void Node::setRightNode(Node *rightNode) {
    m_rightNode = rightNode;
}

unsigned int Node::getSplit() const {
    return m_split;
}

void Node::setSplit(unsigned int split) {
    m_split = split;
}
Range Node::getRange() const {
    return m_range;
}

void Node::setRange(const Range &range) {
    m_range = range;
}

bool Node::isNodeRangeIntersectWithBall(const Node *node, float radius) const {
    Position minPos = m_range.min();
    Position rangeCenter = (m_range.max() + minPos) * 0.5;
    float rangeRadius = rangeCenter.distToOtherPos(minPos);
    return rangeCenter.distToOtherPos(node->getPos()) <= (rangeRadius + radius);
}

std::string Node::toString() {
    std::stringstream ss;
    ss << this;
    return ss.str();
}

std::stringstream &operator<<(std::stringstream &ss, const Node *node) {
    ss << "[Node: Id = " << node->getId() << ", " << node->getState() << "; ";

    // left node info
    if (node->getLeftNode() != nullptr) {
        ss << "KdTreeInfo: leftNodeId: " << node->getLeftNode()->getId() << ", ";
    } else {
        ss << "KdTreeInfo: leftNodeId: null, ";
    }

    // right node info
    if (node->getRightNode() != nullptr) {
        ss << "rightNodeId: " << node->getRightNode()->getId() << "; ";
    } else {
        ss << "rightNodeId: null; ";
    }

    // Random tree info
    ss << "RandomTreeInfo: ";
    if (node->getParent() != nullptr) {
        ss << "Parent: "<< node->getParent()->getId() << ", ";
    } else {
        ss << "Parent: null, ";
    }

    // children info
    ss << "Children: ";
    std::unordered_set<Node *> children = node->getChildren();
    for(std::unordered_set<Node *>::iterator iter = children.begin(); iter != children.end(); ++iter) {
        ss << (*iter)->getId() << ", ";
    }

    ss << "]";

    return ss;
}

void Node::setId(int Id) {
    m_Id = Id;
}


std::ostream &operator<<(std::ostream &os, const Node *node) {
    std::stringstream ss;
    ss << node;
    os << ss.str();
    return os;
}







