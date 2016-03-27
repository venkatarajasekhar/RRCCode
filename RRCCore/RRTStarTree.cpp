#include "RRTStarTree.h"
#include "RRCCommon/Node.h"
#include "RRCCommon/LogUtil.h"
#include "Exceptions/NotFoundNearestNeighborException.h"
#include "RRCCore/PlanningUtil.h"

RRTStarTree::RRTStarTree() {

}

Node *RRTStarTree::extend() {
    std::pair<std::shared_ptr<Node>, Node *> newNodeAndNearestNeighborPair = generateRandomNodeAndReturnNearestNode();
    std::shared_ptr<Node> newNode = newNodeAndNearestNeighborPair.first;
    Node *nearestNeighbor = newNodeAndNearestNeighborPair.second;

    // extend new node
    if (nearestNeighbor != nullptr) {
        // find nodes inside the ball centered at the newNode
        std::vector<Node *> nearNodes;
        float radius = calculateRadius();
        getNodesInNearBall(newNode.get(), radius, nearNodes);

        float minDist = calculateNodeCost(nearestNeighbor) + nearestNeighbor->distToOtherNode(newNode.get());
        Node *minNode = nearestNeighbor;
        for(std::vector<Node *>::const_iterator iter = nearNodes.begin(); iter != nearNodes.end(); ++iter) {
            if (PlanningUtil::isCollisionWithObs(newNode.get(), *iter) == false) {
                float currDist = calculateNodeCost(*iter) + (*iter)->distToOtherNode(newNode.get());
                if (currDist < minDist) {
                    minDist = currDist;
                    minNode = *iter;
                }
            }
        }

        // store and insert node to Kd tree after we finish the near neighbor search
        storeNodes(newNode);
        insertNodeToKdTree(newNode);

        newNode->setParent(minNode);
        minNode->addChild(newNode.get());

        // rewire tree
        rewireTree(nearNodes, minNode);

        updateReturnedPath(newNode.get());
        LogUtil::info("NewNode generated: " + newNode->toString() + "; its nearest neighbor is: " + nearestNeighbor->toString());

        return newNode.get();
    } else {
        throw NotFoundNearestNeighborException();
    }
}

void RRTStarTree::rewireTree(std::vector<Node *> &nearNodes, Node *minNode) {
    float minNodeCost = calculateNodeCost(minNode);
    for(std::vector<Node *>::iterator iter = nearNodes.begin(); iter != nearNodes.end(); ++iter) {
        if (*iter != minNode && PlanningUtil::isCollisionWithObs(*iter, minNode) == false) {
            if (minNodeCost + minNode->distToOtherNode(*iter) < calculateNodeCost(*iter)) {
                Node *oldParent = (*iter)->getParent();
                oldParent->getChildren().erase(*iter); // remove the node from its old parent's children list

                (*iter)->setParent(minNode);
                minNode->addChild(*iter);
            }
        }
    }
}

