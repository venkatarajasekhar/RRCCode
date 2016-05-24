#include "KdTree.h"
#include "RRCCommon/Node.h"
#include <math.h>
#include <stack>
#include <float.h>
#include <RRCCommon/Range.h>

KdTree::KdTree() {

}

void KdTree::insert(Node *newNode) {
    Node *newRoot = insertHelper(getRoot(), newNode, 0);
    setRoot(newRoot);
}

//TODO: implement this method
void KdTree::reBalanceKdTree() {

}

Node *KdTree::insertHelper(Node *root, Node *newNode, unsigned int depth) {
    if (newNode == nullptr) return root;

    // Calculate current dimension
    unsigned int currentDimension =  depth % 2; // 2-D point

    if (root == nullptr) {
        newNode->setLeftNode(nullptr);
        newNode->setRightNode(nullptr);
        newNode->setSplit(currentDimension);
        newNode->getRange().updateRange(newNode->getPos());
        return newNode;
    }

    // update root's range since we insert a new node to its subtree
    root->getRange().updateRange(newNode->getPos());

    Position newPos = newNode->getPos();
    Position rootPos = root->getPos();
    // Compare the new point with root on current dimension
    // and decide the left or right subtree
    if (newPos[currentDimension] <= rootPos[currentDimension]) {
        root->setLeftNode(insertHelper(root->getLeftNode(), newNode, depth + 1)) ;
    } else {
        root->setRightNode(insertHelper(root->getRightNode(), newNode, depth + 1));
    }

    return root;
}

Node *KdTree::nearestNeighbor(Node *node) const {
    return nearestNeighborHelper(m_root, node);
}

void KdTree::nearNeighbor(const Node *node, float radius, std::vector<Node *> &nearNodes) const {
    nearNeighborHelper(m_root, node, radius, nearNodes);
//    nearNeighborHelper2(m_root, node, radius, nearNodes);
}

void KdTree::nearNeighborHelper(Node *root, const Node *target, float radius, std::vector<Node *> &nearNodes) const {
    if(root == nullptr) return;
    float currDist = root->distToOtherNode(target);

    if(currDist <= radius) {
        nearNodes.push_back(root);
    }

    float dx = target->getPos()[root->getSplit()] - root->getPos()[root->getSplit()];
    nearNeighborHelper(dx <= 0.0 ? root->getLeftNode() : root->getRightNode(), target, radius, nearNodes); // search left or right subtree
    if(fabs(dx) <= radius) {
        nearNeighborHelper(dx <= 0.0 ? root->getRightNode(): root->getLeftNode(), target, radius, nearNodes);
    }
}

void KdTree::nearNeighborHelper2(Node *root, const Node *target, float radius, std::vector<Node *> &nearNodes) const {
    if(root == nullptr) return;
    if (root->isNodeRangeIntersectWithBall(target, radius)) {
        float currDistSquare = root->squaredDistToOtherNode(target);
        if(currDistSquare <= radius * radius) {
            nearNodes.push_back(root);
        }

        nearNeighborHelper2(root->getLeftNode(), target, radius, nearNodes);
        nearNeighborHelper2(root->getRightNode(), target, radius, nearNodes);
    }
}

Node *KdTree::nearestNeighborHelper(Node *root, Node *queryNode) const {
    if (root == nullptr) return queryNode;
    if (queryNode == nullptr) return nullptr;

    Node *currNode = root;
    std::stack<Node *> searchPath;

    // find the current best
    findLeafNodeClosestToQueryNode(currNode, queryNode, searchPath);

    Node *nearestNode = searchPath.top();
    float nearestDist = nearestNode->distToOtherNode(queryNode);
    searchPath.pop();

    // backtracking
    while(!searchPath.empty()) {
        currNode = searchPath.top();
        searchPath.pop();

        // if leaf node
        if (currNode->getLeftNode() == nullptr && currNode->getRightNode() == nullptr) {
            float leafDistToQueryNode = currNode->distToOtherNode(queryNode);
            if ( leafDistToQueryNode < nearestDist) {
                nearestDist = leafDistToQueryNode;
                nearestNode = currNode;
            }
        } else {
            // continue search
            unsigned int currNodeSplitDim = currNode->getSplit();
            if (fabs(currNode->getPos()[currNodeSplitDim] - queryNode->getPos()[currNodeSplitDim]) < nearestDist) {
                if (currNode->distToOtherNode(queryNode) < nearestDist) {
                    nearestDist = currNode->distToOtherNode(queryNode);
                    nearestNode = currNode;
                }

                if (queryNode->getPos()[currNodeSplitDim] <= currNode->getPos()[currNodeSplitDim]) {
                    currNode = currNode->getRightNode();
                } else {
                    currNode = currNode->getLeftNode();
                }

                findLeafNodeClosestToQueryNode(currNode, queryNode, searchPath);
            }
        }
    }

    return nearestNode;
}

void KdTree::findLeafNodeClosestToQueryNode(Node *currNode, Node* queryNode, std::stack<Node *> &searchPath) const {
    if (currNode == nullptr) return;

    searchPath.push(currNode);
    if (currNode->getLeftNode() != nullptr && currNode->getRightNode() != nullptr) {
        unsigned int currNodeSplitDim = currNode->getSplit();
        if (queryNode->getPos()[currNodeSplitDim] <= currNode->getPos()[currNodeSplitDim]) {
            // search left
            currNode = currNode->getLeftNode();
        } else {
            // search right
            currNode = currNode->getRightNode();
        }
    } else {
        currNode->getLeftNode() == nullptr? currNode = currNode->getRightNode() : currNode = currNode->getLeftNode();
    }

    findLeafNodeClosestToQueryNode(currNode, queryNode, searchPath);
}

void KdTree::findLeafNodeClosestToQueryNodeIterative(Node *currNode, Node* queryNode, std::stack<Node *> &searchPath) const {
    while(currNode != nullptr) {
        searchPath.push(currNode);
        if (currNode->getLeftNode() != nullptr && currNode->getRightNode() != nullptr) {
            unsigned int currNodeSplitDim = currNode->getSplit();
            if (queryNode->getPos()[currNodeSplitDim] <= currNode->getPos()[currNodeSplitDim]) {
                // search left
                currNode = currNode->getLeftNode();
            } else {
                // search right
                currNode = currNode->getRightNode();
            }
        } else {
            currNode->getLeftNode() == nullptr? currNode = currNode->getRightNode() : currNode = currNode->getLeftNode();
        }
    }
}
