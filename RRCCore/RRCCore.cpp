#include "RRCCore.h"
#include "Monitor/MonitorWrapper.h"
#include "Monitor/Monitor.h"
#include <RRCCommon/LogUtil.h>
#include <RRCCommon/Node.h>
#include <RRCCommon/NodeType.h>
#include <RRCCore/PlanningUtil.h>
#include <string>
#include "KdTree.h"
#include "KdTreeWrapper.h"
#include "RRCCommon/TreeFactory.h"
#include <stdexcept>
#include "RRCCore/RandomTree.h"
#include <memory>
#include <stdlib.h> //srand TODO: remove, random seed used for debug, remove later

RRCCore::RRCCore() : m_KdTree(nullptr), m_KdTreeWrapper(nullptr), m_randomTree(nullptr), m_shouldStop(false) {

}

RRCCore::~RRCCore() {

}

void RRCCore::Run() {
    setupTree();
    setupStartAndGoalNode();
    startPlanning();
}

int RRCCore::getNumOfNodes() const {
    return m_randomTree->getNumOfNodes();
}

void RRCCore::setShouldStop(bool shouldStop) {
    m_shouldStop = shouldStop;
}

void RRCCore::onNewNodeAdded(Node *newNode) const {
    MonitorWrapper::Instance()->getMonitor()->onNewNodeAdded(newNode);
}

void RRCCore::setupTree() {
    TreeType treeType = MonitorWrapper::Instance()->getMonitor()->getTreeType();
    m_KdTree = std::unique_ptr<KdTree>(new KdTree());
    m_KdTreeWrapper = std::unique_ptr<KdTreeWrapper>(new KdTreeWrapper(m_KdTree.get()));
    m_randomTree = TreeFactory::newTree(treeType);
}

void RRCCore::startPlanning() {
    std::srand(5000); //TODO: remove later
    int numSteps = MonitorWrapper::Instance()->getMonitor()->getNumSteps();

    try {
        for (int i = 1; i <= numSteps; ++i) {
            if (m_shouldStop) break;
            Node *node = m_randomTree->extend();
            onNewNodeAdded(node);
        }
    } catch(const std::exception &ex) {
        LogUtil::error("Exception thrown when planning: " + std::string(ex.what()));
    }

    planningFinished(); // finish planning
}

void RRCCore::planningFinished() {
    std::vector<Node *> path = m_randomTree->getReturnedPath();
    MonitorWrapper::Instance()->getMonitor()->drawReturnedPath(path);
    MonitorWrapper::Instance()->getMonitor()->planningFinished();
}

void RRCCore::setupStartAndGoalNode() {
    Position pos = MonitorWrapper::Instance()->getMonitor()->startPos();
    std::shared_ptr<Node> startNode = std::shared_ptr<Node>(new Node(State(pos)));
    m_randomTree->setupStartingNode(startNode);
    onNewNodeAdded(startNode.get());

    pos = MonitorWrapper::Instance()->getMonitor()->goalPos();
    std::shared_ptr<Node> goalNode = std::shared_ptr<Node>(new Node(State(pos)));
    m_randomTree->setupGoalNode(goalNode);
    onNewNodeAdded(goalNode.get());
}

