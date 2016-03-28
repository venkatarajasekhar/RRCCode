#include "RRCTree.h"
#include "RRCCommon/Node.h"
#include "RRCCore/PlanningUtil.h"
#include <limits>
#include <Exceptions/NotFoundNearestNeighborException.h>

RRCTree::RRCTree(const KalmanFilter &filter) : m_kalmanFilter(filter) {

}

Node *RRCTree::extend() {
    std::pair<std::shared_ptr<Node>, Node *> newNodeAndNearestNeighborPair = generateRandomNodeAndReturnNearestNode();
    std::shared_ptr<Node> newNode = newNodeAndNearestNeighborPair.first;
    Node *nearestNeighbor = newNodeAndNearestNeighborPair.second;

    // extend new node
    if (nearestNeighbor != nullptr) {
        // find nodes inside the ball centered at the newNode
        std::vector<Node *> nearNodes;
        float radius = calculateRadius();
        getNodesInNearBall(newNode.get(), radius, nearNodes);

        float minCost = std::numeric_limits<float>::max();
        std::vector<Node *> minCostPath;
        Node *minNode = nearestNeighbor;
        if (nearNodes.size() > 1) {
            for(unsigned int i = 0; i < nearNodes.size() - 1; ++i) {
                for(unsigned int j = i + 1; j < nearNodes.size(); ++j) {
                    if (PlanningUtil::isCollisionWithObs(newNode.get(), nearNodes[i]) == false && PlanningUtil::isCollisionWithObs(newNode.get(), nearNodes[j]) == false) {
                        std::vector<Node *> path;
                        if(getPathBetweenNodes(nearNodes[i], nearNodes[j], path) == false) throw std::logic_error("No path found between near nodes");

                        path.push_back(newNode.get()); // path should include the new node
                        float cost = calculateCycleCost(path);
                        if (cost < minCost) {
                            minCost = cost;
                            minCostPath = path;
                            // if any of them is the nearest neighbor, we choose to connect the nearest neighbor in order to extend the tree, otherwise, we can choose any one of them to connect
                            if (nearNodes[i] == nearestNeighbor || nearNodes[j] == nearestNeighbor) minNode = nearestNeighbor;
                            else minNode = nearNodes[i];
                        }
                    }
                }
            }

            // check whether the cycle found has lower cost than the currrent min cost cycle
            if (minCost < m_returnedPathCost) {
                m_returnedPathCost = minCost;
                m_returnedPath = minCostPath;
            }
        }

        // store and insert node to Kd tree after we finish the near neighbor search
        storeNodes(newNode);
        insertNodeToKdTree(newNode);

        newNode->setParent(minNode);
        minNode->addChild(newNode.get());

        return newNode.get();
    } else {
        throw NotFoundNearestNeighborException();
    }
}

float RRCTree::calculateCycleCost(const std::vector<Node *> &cyclePath) const {
    return m_kalmanFilter.estimationUncertainty(cyclePath);
}

bool RRCTree::getPathBetweenNodes(Node *node1, Node *node2, std::vector<Node *> &path) const {
    // first path to root
    Node *iter = node1;
    std::vector<Node *> path1;
    while(iter != nullptr) {
        path1.push_back(iter);
        iter = iter->getParent();
    }

    // second path to root
    std::vector<Node *> path2;
    iter = node2;
    while(iter != nullptr) {
        path2.push_back(iter);
        iter = iter->getParent();
    }

    Node *lca = nullptr; // lowest common ancestor
    std::vector<Node *>::const_reverse_iterator iter1 = path1.rbegin(), iter2 = path2.rbegin();
    for(; iter1 != path1.rend() && iter2 != path2.rend(); ++iter1, ++iter2) {
        if ((*iter1) != (*iter2)) {
            break;
        } else {
            lca = *iter1;
        }
    }

    if (lca == nullptr) {
        path.clear();
        return false; // no common ancestor
    } else {
        path = std::vector<Node *>(path1.begin(), path1.begin() + (path1.rend() - iter1));
        path.push_back(lca); // push common ancestor
        for(; iter2 != path2.rend(); ++iter2) {
            path.push_back(*iter2);
        }

        return true; // common ancestor is found
    }
}

