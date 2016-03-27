#include "NodeFactory.h"
#include "Monitor/Monitor.h"
#include "Monitor/MonitorWrapper.h"
#include "RRCCommon/Area.h"
#include <stdlib.h>
#include <RRCCommon/Node.h>

std::shared_ptr<Node> NodeFactory::NewNode(NodeType nodeType) {
    switch(nodeType) {
    case NodeType::OriginNode:
        return std::shared_ptr<Node>(new Node());

    case NodeType::UniformRandom: {
        Area area = MonitorWrapper::Instance()->getMonitor()->getSceneSize();
        float randX = area.x() + area.width() * (((float)rand()) / RAND_MAX);
        float randY = area.y() + area.height() * (((float)rand()) / RAND_MAX);
        State randState(Position(randX, randY));
        return std::shared_ptr<Node>(new Node(randState));
    }
    default:
       return std::shared_ptr<Node>(nullptr);
    }
}
