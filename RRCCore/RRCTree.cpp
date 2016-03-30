#include "RRCTree.h"
#include "RRCCommon/Node.h"
#include "RRCCore/PlanningUtil.h"
#include <limits>
#include <Exceptions/NotFoundNearestNeighborException.h>
#include <chrono>
#include <iostream>

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

        // find nodes inside the near ball that is connectable to the newNode
        std::vector<Node *> collisionFreeNearNodes;
        for(std::vector<Node *>::const_iterator iter = nearNodes.begin(); iter != nearNodes.end(); ++iter) {
            if (PlanningUtil::isCollisionWithObs(newNode.get(), *iter) == false) {
                collisionFreeNearNodes.push_back(*iter);
            }
        }

        float minCost = std::numeric_limits<float>::max();
        std::vector<Node *> minCostPath;
        Node *minNode = nearestNeighbor;
        if (collisionFreeNearNodes.size() > 1) {
            for(unsigned int i = 0; i < collisionFreeNearNodes.size() - 1; ++i) {
                for(unsigned int j = i + 1; j < collisionFreeNearNodes.size(); ++j) {
                    std::vector<Node *> path;
                    if(getPathBetweenNodes(collisionFreeNearNodes[i], collisionFreeNearNodes[j], path) == false) throw std::logic_error("No path found between near nodes");

                    path.push_back(newNode.get()); // path should include the new node

//                    std::chrono::time_point<std::chrono::system_clock> start, end;
//                    start = std::chrono::system_clock::now();
                    float cost = calculateCycleCost(path);
//                    end = std::chrono::system_clock::now();
//                    std::chrono::duration<double> elapsed = end - start;
//                    std::cout << "Time elapsed to calculate cycle cost is " << elapsed.count() << std::endl;
                    if (cost < minCost) {
                        minCost = cost;
                        minCostPath = path;
                        // if any of them is the nearest neighbor, we choose to connect the nearest neighbor in order to extend the tree, otherwise, we can choose any one of them to connect
                        if (collisionFreeNearNodes[i] == nearestNeighbor || collisionFreeNearNodes[j] == nearestNeighbor) minNode = nearestNeighbor;
                        else minNode = collisionFreeNearNodes[i];
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

