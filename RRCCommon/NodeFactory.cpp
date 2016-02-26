#include "RRCCore/RandomTreeNode.h"
#include "NodeFactory.h"
#include "Monitor/Monitor.h"
#include "Monitor/MonitorWrapper.h"
#include "RRCCommon/Area.h"
#include <stdlib.h>

std::unique_ptr<Node> NodeFactory::NewNode(NodeType nodeType) {
    switch(nodeType) {
    case NodeType::OriginNode:
        return std::unique_ptr<Node>(new RandomTreeNode());

    case NodeType::UniformRandom: {
        Area area = MonitorWrapper::Instance()->GetMonitor()->GetSceneSize();
        float randX = area.x() + area.width() * (((float)rand()) / RAND_MAX);
        float randY = area.y() + area.height() * (((float)rand()) / RAND_MAX);
        State randState(Position(randX, randY));
        return std::unique_ptr<Node>(new RandomTreeNode(randState));
    }
    default:
       return std::unique_ptr<Node>(nullptr);
    }
}
