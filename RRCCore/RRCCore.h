#ifndef RRCCORE_H
#define RRCCORE_H
#include <memory>
#include <vector>

class KdTree;
class KdTreeWrapper;
class RandomTree;
class Node;
#include "RRCCommon/TreeType.h"

class RRCCore {
  public:
    RRCCore();
    ~RRCCore();

    void Run();
    int getNumOfNodes() const;

    void setShouldStop(bool shouldStop);

private:
    std::unique_ptr<KdTree> m_KdTree;
    std::unique_ptr<KdTreeWrapper> m_KdTreeWrapper;
    std::unique_ptr<RandomTree> m_randomTree;
    bool m_shouldStop;

    void onNewNodeAdded(Node *newNode) const;
    void startPlanning();
    void setupTree();

    void planningFinished();
};

#endif // RRCCORE_H
