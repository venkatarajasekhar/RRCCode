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
void KdTree::reBalanceKdTree()
{

}

Node *KdTree::nearestNeighbor(Node *node) const
{
    return nearestNeighborHelper(m_root, node);
}

Node *KdTree::insertHelper(Node *root, Node *newNode, unsigned int depth) {
     if (newNode == nullptr) return root;

    // Calculate current dimension
    unsigned int currentDimension =  depth % 2; // 2-D point

    if (root == nullptr)
    {
        newNode->setLeftNode(nullptr);
        newNode->setRightNode(nullptr);
        newNode->setSplit(depth);
        newNode->getRange().updateRange(newNode->getPos());
        return newNode;
    }

    // update root's range since we insert a new node to its subtree
    root->getRange().updateRange(newNode->getPos());

    Position newPos = newNode->getPos();
    Position rootPos = root->getPos();
    // Compare the new point with root on current dimension
    // and decide the left or right subtree
    if (newPos[currentDimension] < rootPos[currentDimension]) {
        root->setLeftNode(insertHelper(root->getLeftNode(), newNode, depth + 1)) ;
    } else {
        root->setRightNode(insertHelper(root->getRightNode(), newNode, depth + 1));
    }

    return root;
}

Node *KdTree::nearestNeighborHelper(Node *root, Node *queryNode) const {
    if (root == nullptr || queryNode == nullptr) return nullptr;

    Node *currNode = root;
    std::stack<Node *> searchPath;

    // find the current best
    while(currNode != nullptr) {
        searchPath.push(currNode);

        unsigned int currNodeSplitDim = currNode->getSplit();
        if (queryNode->getPos()[currNodeSplitDim] <= currNode->getPos()[currNodeSplitDim]) {
            // search left
            currNode = currNode->getLeftNode();
        } else {
            // search right
            currNode = currNode->getRightNode();
        }
    }

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
                    currNode = currNode->getLeftNode();
                } else {
                    currNode = currNode->getRightNode();
                }
                if (currNode != nullptr) {
                    searchPath.push(currNode);
                }
            }
        }
    }

    return nearestNode;
}

