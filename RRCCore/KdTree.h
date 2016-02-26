#ifndef KDTREE_H
#define KDTREE_H

#include <RRCCommon/Tree.h>
#include <vector>

class KdTree : public Tree
{
public:
    KdTree();

    void insert(Node *newNode);

    /**
     * @brief reBalanceKdTree: rebalance KdTree;
     */
    void reBalanceKdTree();

    /**
     * @brief nearestNeighbor: search for nearest neighbor in the tree
     * @param node
     * @return
     */
    Node *nearestNeighbor(Node *node) const;

    /**
     * @brief nearNeighbor: search for near neighbors
     * @param node
     * @return
     */
    std::vector<Node *> nearNeighbor(Node *node);

private:
    /**
     * @brief insertHelper: insert new node into tree
     * @param root
     * @param newNode
     * @param depth
     * @return new root
     */
    Node *insertHelper(Node *root, Node *newNode, unsigned int depth);

    Node *nearestNeighborHelper(Node *root, Node *queryNode) const;
};

#endif // KDTREE_H
