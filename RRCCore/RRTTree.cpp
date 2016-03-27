#include "KdTreeWrapper.h"
#include "KdTree.h"
#include "RRTTree.h"
#include "RRCCommon/Node.h"
#include "RRCCore/PlanningUtil.h"
#include "Exceptions/NotFoundNearestNeighborException.h"
#include "RRCCommon/LogUtil.h"
#include "Monitor/Monitor.h"
#include "Monitor/MonitorWrapper.h" //TODO: remove this, this is used for debug, RRTTree should not call Monitor

RRTTree::RRTTree() {

}

Node *RRTTree::extend() {
    std::pair<std::shared_ptr<Node>, Node *> newNodeAndNearestNeighborPair = generateRandomNodeAndReturnNearestNode();
    std::shared_ptr<Node> newNode = newNodeAndNearestNeighborPair.first;
    Node *nearestNeighbor = newNodeAndNearestNeighborPair.second;

    // extend new node
    if (nearestNeighbor != nullptr) {
        // store nodes and insert node to Kd tree
        storeNodesAndInsertNodeToKdTree(newNode);

        newNode->setParent(nearestNeighbor);
        nearestNeighbor->addChild(newNode.get());
        updateReturnedPath(newNode.get());

        LogUtil::info("NewNode generated: " + newNode->toString() + "; its nearest neighbor is: " + nearestNeighbor->toString());

        return newNode.get();
    } else {
        throw NotFoundNearestNeighborException();
    }
}
