#include "PlanningUtil.h"
#include <RRCCommon/Node.h>
#include <Monitor/MonitorWrapper.h>
#include <Monitor/Monitor.h>
#include <RRCCommon/Area.h>

const float PlanningUtil::collisionCheckingResolution = 1;

PlanningUtil::PlanningUtil() {

}

PlanningUtil::~PlanningUtil() {

}

bool PlanningUtil::isCollisionWithObs(Node *startNode, Node *endNode) {
    Position startPos(startNode->getState().getPos());
    Position endPos(endNode->getState().getPos());

    std::vector<Area> obs = MonitorWrapper::Instance()->getMonitor()->getObstacles();

    for(unsigned int i = 0; i < obs.size(); ++i) {
        if (isPositionCollideWithObs(obs[i], startPos, endPos)) return true;
    }

    return false;
}

bool PlanningUtil::isPositionCollideWithObs(const Area &obs, const Position &startPos, const Position &endPos) {
    if (obs.isInsideArea(startPos) || obs.isInsideArea(endPos)) return true;

    if (startPos.distToOtherPos(endPos) <= collisionCheckingResolution ) {
        return false;
    } else {
        Position midPos((startPos + endPos) * 0.5);
        return isPositionCollideWithObs(obs, startPos, midPos) || isPositionCollideWithObs(obs, midPos, endPos);
    }
}

float PlanningUtil::sceneVolume() {
    float width = MonitorWrapper::Instance()->getMonitor()->getSceneSize().width();
    float height = MonitorWrapper::Instance()->getMonitor()->getSceneSize().height();

    return width * height;
}


