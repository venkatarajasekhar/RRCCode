#ifndef RANDOMTREE_H
#define RANDOMTREE_H
#include "RRCCommon/Tree.h"

class RandomTree : public Tree {
  public:
    RandomTree();
    virtual ~RandomTree();
    virtual Node *extend();
    void setupStartingNode(const std::shared_ptr<Node> &startNode);
    void setupGoalNode(const std::shared_ptr<Node> &goalNode);
    int getNumOfNodes() const;

    std::vector<Node *> getReturnedPath() const;

  protected:
    std::shared_ptr<Node> m_startNode;
    std::shared_ptr<Node> m_goalNode;
    float m_returnedPathCost;
    double m_planningTimeOutInSeconds;
    float m_randomTreeSegmentLength;
    std::vector<std::shared_ptr<Node> > m_nodes;
    std::vector<Node *> m_returnedPath;

    std::shared_ptr<Node> generateRandomNode() const;
    std::shared_ptr<Node> getNewNodeBasedOnRandomNodeAndNearestNode(Node *randomNode, Node *nearestNeighbor, float randomTreeSegmentLength) const;
    std::pair<std::shared_ptr<Node>, Node *> generateRandomNodeAndReturnNearestNode();

    void storeNodesAndInsertNodeToKdTree(const std::shared_ptr<Node> &node);
    void storeNodes(const std::shared_ptr<Node> &node);
    void insertNodeToKdTree(const std::shared_ptr<Node> &node) const;

    void updateReturnedPath(Node *newNode);

    void getNodesInNearBall(const Node *newNode, float radius, std::vector<Node *> &nearNodes) const;

    float calculateRadius() const;

    float calculateNodeCost(const Node *node) const;

  private:
    /**
     * @brief getNearestNodeByBruteForce: used for debug
     * @param randomNode
     * @return
     */
    Node *getNearestNodeByBruteForce(Node *randomNode) const;

    float calculatePathCost(Node *node, std::vector<Node *> &path) const;

    /**
     * @brief getNodesInNearBallBruteForce: used for debug
     * @param newNode
     * @param radius
     * @param nearNodes
     */
    void getNodesInNearBallBruteForce(const Node *newNode, float radius, std::vector<Node *> &nearNodes) const;
};

#endif // RANDOMTREE_H
