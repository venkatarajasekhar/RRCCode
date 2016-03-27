#include "RandomTree.h"
#include "RRCConfig/RRCConfig.h"
#include "Exceptions/NotImplementedException.h"
#include <RRCCommon/NodeFactory.h>
#include "RRCCore/PlanningUtil.h"
#include <stdexcept>
#include "RRCCommon/Node.h"
#include "RRCCommon/LogUtil.h"
#include "KdTreeWrapper.h"
#include "KdTree.h"
#include <iostream>
#include <utility>
#include <ctime>
#include <limits>
#include <Monitor/Monitor.h>
#include <Monitor/MonitorWrapper.h>
#include <math.h>
#include <algorithm>
#include <vector>

RandomTree::RandomTree() : m_startNode(nullptr), m_goalNode(nullptr) , m_returnedPathCost(std::numeric_limits<float>::max()) {
    m_planningTimeOutInSeconds = RRCConfig::Instance()->initializeFromConfig("Planning", "PlanningTimeOutInSeconds", 5);
    m_randomTreeSegmentLength = RRCConfig::Instance()->initializeFromConfig("Planning", "RandomTreeSegmentLength", 5);
}

RandomTree::~RandomTree() {

}

Node *RandomTree::extend() {
    throw NotImplementedException();
}

void RandomTree::setupStartingNode(const std::shared_ptr<Node> &startNode) {
    m_startNode = startNode;
    storeNodesAndInsertNodeToKdTree(startNode);
    setRoot(startNode.get());
}

void RandomTree::setupGoalNode(const std::shared_ptr<Node> &goalNode) {
    m_goalNode = goalNode;
    updateReturnedPath(m_startNode.get()); // update the path in case the startNode are too close to the goal node
}

int RandomTree::getNumOfNodes() const {
    return m_nodes.size();
}
std::vector<Node *> RandomTree::getReturnedPath() const {
    return m_returnedPath;
}


std::shared_ptr<Node> RandomTree::generateRandomNode() const {
    std::shared_ptr<Node> node(nullptr);
    do {
        node = NodeFactory::NewNode(NodeType::UniformRandom);
    } while (PlanningUtil::isCollisionWithObs(node.get(), node.get()) || node == nullptr);

    return node;
}

std::shared_ptr<Node> RandomTree::getNewNodeBasedOnRandomNodeAndNearestNode(Node *randomNode, Node *nearestNeighbor, float randomTreeSegmentLength) const {
    if (randomNode == nullptr || randomTreeSegmentLength <= 0) throw std::invalid_argument("Invalid argument when calling getNewNodeBasedOnRandomNodeAndNearestNode");
    if (nearestNeighbor == nullptr || randomNode->distToOtherNode(nearestNeighbor) <= randomTreeSegmentLength) return std::shared_ptr<Node>(new Node(randomNode->getState()));

    Position directionVec = randomNode->getPos() - nearestNeighbor->getPos();
    directionVec = directionVec * (1.0 / directionVec.distToOtherPos(Position(0, 0))); // unit direction vec
    Position newNodePos;
    newNodePos = nearestNeighbor->getPos() + directionVec * randomTreeSegmentLength;

    return std::shared_ptr<Node>(new Node(State(newNodePos)));
}

void RandomTree::storeNodesAndInsertNodeToKdTree(const std::shared_ptr<Node> &node) {
    storeNodes(node);
    insertNodeToKdTree(node);
}

void RandomTree::storeNodes(const std::shared_ptr<Node> &node) {
    m_nodes.push_back(node);
}

void RandomTree::insertNodeToKdTree(const std::shared_ptr<Node> &node) const {
    // insert node to kdtree
    KdTreeWrapper::instance()->getKdTree()->insert(node.get());
    std::cout << "Current Number of nodes: " << m_nodes.size() << std::endl;
}

std::pair<std::shared_ptr<Node>, Node *> RandomTree::generateRandomNodeAndReturnNearestNode() {
    Node *nearestNeighbor = nullptr;
    std::shared_ptr<Node> newNode(nullptr);

    time_t start, end; // a stop watch
    std::time(&start);
    while(1) {
        std::shared_ptr<Node> randomNode = generateRandomNode();
        nearestNeighbor = KdTreeWrapper::instance()->getKdTree()->nearestNeighbor(randomNode.get());
//        nearestNeighbor = getNearestNodeByBruteForce(randomNode.get());
        newNode = getNewNodeBasedOnRandomNodeAndNearestNode(randomNode.get(), nearestNeighbor, m_randomTreeSegmentLength);

        std::time(&end);
        if (PlanningUtil::isCollisionWithObs(nearestNeighbor, newNode.get()) == false) {
//            MonitorWrapper::Instance()->getMonitor()->drawNodeForDebug(randomNode.get(), nearestNeighbor); // TODO: used for debug, remove later
            break;
        }

        if (std::difftime(end, start) > m_planningTimeOutInSeconds) {
            LogUtil::warn("Timeout when generating new node! Configured timeout limit is " + std::to_string(m_planningTimeOutInSeconds) + " seconds, while " + std::to_string(std::difftime(end, start)) + " seconds elapsed!");
            break;
        }
    }

    // set node Id
    newNode->setId(m_nodes.size());
    std::pair<std::shared_ptr<Node>, Node *> res(newNode, nearestNeighbor);
    return res;
}

Node *RandomTree::getNearestNodeByBruteForce(Node *randomNode) const {
    if (randomNode == nullptr) throw std::invalid_argument("Searching for nearest node, the node can not be null.");
    Node *nearest = nullptr;
    float dist = std::numeric_limits<float>::max();
    for(unsigned int i = 0; i < m_nodes.size(); ++i) {
        float currDist = randomNode->distToOtherNode(m_nodes[i].get());
        if (currDist < dist) {
            dist = currDist;
            nearest = m_nodes[i].get();
        }
    }

    return nearest;
}

float RandomTree::calculatePathCost(Node *node, std::vector<Node *> &path) const {
    if (node == nullptr || node->distToOtherNode(m_goalNode.get()) > m_randomTreeSegmentLength) {
        throw std::invalid_argument("To calculate path cost, the distance between the node and the goal node must be smaller than or equal to " + std::to_string(m_randomTreeSegmentLength));
    }

    path.clear();
    path.push_back(m_goalNode.get());
    float res = node->distToOtherNode(m_goalNode.get());
    while (node != nullptr && node->getParent() != nullptr) {
        path.push_back(node);
        res += node->distToOtherNode(node->getParent());
        node = node->getParent();
    }
    path.push_back(node); // push_back root

    return res;
}

void RandomTree::getNodesInNearBallBruteForce(const Node *newNode, float radius, std::vector<Node *> &nearNodes) const {
    if (newNode == nullptr) throw std::invalid_argument("Searching for nodes inside ball, the node can not be null.");

    for(std::vector<std::shared_ptr<Node> >::const_iterator iter = m_nodes.begin(); iter != m_nodes.end(); ++iter) {
        if ((*iter).get()->distSquaredToOtherNode(newNode) <= radius * radius) {
            nearNodes.push_back((*iter).get());
        }
    }
}

void RandomTree::updateReturnedPath(Node *newNode) {
    if (newNode->distToOtherNode(m_goalNode.get()) <= m_randomTreeSegmentLength) {
        std::vector<Node *> currPath;
        float currPathCost = calculatePathCost(newNode, currPath);
        if (currPathCost < m_returnedPathCost) {
            m_returnedPathCost = currPathCost;
            m_returnedPath = currPath;
        }
    }
}

void RandomTree::getNodesInNearBall(const Node *newNode, float radius, std::vector<Node *> &nearNodes) const {
    KdTreeWrapper::instance()->getKdTree()->nearNeighbor(newNode, radius, nearNodes);
//    getNodesInNearBallBruteForce(newNode, radius, nearNodes);
}

float RandomTree::calculateRadius() const {
    float gama = 2 * pow(1 + 1.0 / 2, 1.0 / 2) * pow(PlanningUtil::sceneVolume() / M_PI, 1.0 / 2);
    float numNodes = (float)getNumOfNodes();
    float shrinkingRadius = gama * pow(log(numNodes) / numNodes, 1.0 / 2);
    return std::min(m_randomTreeSegmentLength, shrinkingRadius);
}

float RandomTree::calculateNodeCost(const Node *node) const {
    float res = 0;
    while (node != nullptr && node->getParent() != nullptr) {
        res += node->distToOtherNode(node->getParent());
        node = node->getParent();
    }

    return res;
}
