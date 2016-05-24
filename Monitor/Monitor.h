#ifndef MONITOR_H
#define MONITOR_H

#include <vector>
#include "RRCCommon/TreeType.h"

class UIModel;
class RRCCore;
class Area;
class Position;
class Node;
class Field;

class Monitor
{
public:
    Monitor(UIModel *uiModel, RRCCore *rrcCore);
    virtual ~Monitor();

    Area getSceneSize() const;
    Field getField() const;
    std::vector<Area> getObstacles() const;
    void onButtonRunClicked();
    void onButtonResetClicked();
    void onNewNodeAdded(Node *newNode);
    void drawNodeForDebug(Node *newNode, Node *nearestNode);
    int getNumSteps() const;
    TreeType getTreeType() const;
    void planningFinished() const;
    Position startPos() const;
    Position goalPos() const;
    int getNumOfNodes() const;
    void drawReturnedPath(const std::vector<Node *> &path) const;

private:
    UIModel *m_UIModel;
    RRCCore *m_rrcCore;
};

#endif // MONITOR_H
