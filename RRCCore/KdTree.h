#ifndef KDTREE_H
#define KDTREE_H

#include <RRCCommon/Tree.h>
#include <vector>
#include <stack>

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
     * @return null if node is null, otherwise, returns a pointer to a non-null node
     */
    Node *nearestNeighbor(Node *node) const;

    /**
     * @brief nearNeighbor: search for near neighbors
     * @param node
     * @return
     */
    void nearNeighbor(const Node *node, float radius, std::vector<Node *> &nearNodes) const;

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
    void nearNeighborHelper(Node *root, const Node *node, float radius, std::vector<Node *> &nearNodes) const;
    void nearNeighborHelper2(Node *root, const Node *target, float radius, std::vector<Node *> &nearNodes) const;

    void findLeafNodeClosestToQueryNode(Node *currNode, Node *queryNode, std::stack<Node *> &searchPath) const;
    void findLeafNodeClosestToQueryNodeIterative(Node *currNode, Node* queryNode, std::stack<Node *> &searchPath) const;
};

#endif // KDTREE_H
