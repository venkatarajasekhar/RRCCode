#include "Monitor.h"
#include <RRCCommon/Area.h>
#include <RRCCore/RRCCore.h>
#include <UI/UIModel.h>

//TODO: remove these two headers, this is just used as output new point position
#include <iostream>
#include <RRCCommon/Position.h>
#include <RRCCore/Field.h>


Monitor::Monitor(UIModel *uiModel, RRCCore *rrcCore) : m_UIModel(uiModel), m_rrcCore(rrcCore) {
}

Monitor::~Monitor() {

}

Area Monitor::getSceneSize() const {
    return m_UIModel->GetSceneSize();
}

Field Monitor::getField() const
{
    return m_UIModel->field();
}

std::vector<Area> Monitor::GetObstacles() const {
    return m_UIModel->GetObstacles();
}

void Monitor::onButtonRunClicked() {
    m_rrcCore->setShouldStop(false);
    m_rrcCore->Run();
}

void Monitor::onButtonResetClicked() {
    m_rrcCore->setShouldStop(true);
}

void Monitor::onNewNodeAdded(Node *newNode) {
    m_UIModel->onNewNodeAdded(newNode);
    m_UIModel->setCurrNumOfNodes(getNumOfNodes());
}

void Monitor::drawNodeForDebug(Node *newNode, Node *nearestNode) {
    m_UIModel->drawNodeForDebug(newNode, nearestNode);
}

int Monitor::getNumSteps() const {
    return m_UIModel->numSteps();
}

TreeType Monitor::getTreeType() const {
    return m_UIModel->treeType();
}

void Monitor::planningFinished() const {
    m_UIModel->planningFinished();
}

Position Monitor::startPos() const {
    return m_UIModel->startPos();
}

Position Monitor::goalPos() const {
    return m_UIModel->goalPos();
}

int Monitor::getNumOfNodes() const {
    return m_rrcCore->getNumOfNodes();
}

void Monitor::drawReturnedPath(const std::vector<Node *> &path) const {
    m_UIModel->drawReturnedPath(path);
}

