#include "RRCCore.h"
#include "Monitor/MonitorWrapper.h"
#include "Monitor/Monitor.h"
#include <RRCCommon/LogUtil.h>
#include <RRCCommon/Node.h>
#include <RRCCommon/NodeFactory.h>
#include <RRCCommon/NodeType.h>
#include <RRCCore/PlanningUtil.h>
#include <string>

RRCCore* RRCCore::ms_instance = 0;

RRCCore* RRCCore::Instance() {
    if (ms_instance == 0) {
        ms_instance = new RRCCore();
    }

    return ms_instance;
}

RRCCore::RRCCore() {

}

RRCCore::~RRCCore() {
    this->Release();
}

void RRCCore::Run() {
    std::unique_ptr<Node> node(nullptr);
    do {
        node = NodeFactory::NewNode(NodeType::UniformRandom);
    } while (PlanningUtil::isCollisionWithObs(node.get(), node.get()));

    LogUtil::info("New point is added - x: " + std::to_string(node->getState().getPos().x()) + ", y: " + std::to_string(node->getState().getPos().y()));
    OnNewPointAdded(node->getState().getPos().x(), node->getState().getPos().y());
}

void RRCCore::OnNewPointAdded(float x, float y) {
    MonitorWrapper::Instance()->GetMonitor()->OnNewPointAdded(x, y);
}

void RRCCore::Release() {
    if (ms_instance) {
        delete ms_instance;
    }

    ms_instance = 0;
}

