#ifndef UIMODEL_H
#define UIMODEL_H

#include <QGraphicsScene>
#include <RRCCommon/Area.h>
#include <vector>
#include "RRCCommon/TreeType.h"
#include "RRCCore/Field.h"

class QComboBox;
class QSpinBox;
class QPushButton;
class QLabel;
class QGraphicsEllipseItem;
class Node;

class UIModel : public QGraphicsScene {
    Q_OBJECT
  public slots:
    void slot_run();
    void slot_reset();

  public:
    UIModel(QObject *parent, QComboBox *treeType, QSpinBox *numSteps, QPushButton *run, QPushButton *reset, QLabel *currNumNodes);
    Area GetSceneSize();
    std::vector<Area> GetObstacles();
    void SetSceneSize();
    void AddObstacles();

    void onNewNodeAdded(Node *newNode);
    int numSteps() const;
    TreeType treeType() const;
    void planningFinished();
    void setCurrNumOfNodes(int currNumNodes) const;
    void drawNodeForDebug(Node *newNode, Node *nearestNode);
    void drawReturnedPath(const std::vector<Node *> &path);

    /**
     * @brief contextMenuEvent: the pop menu
     * @param event
     */
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);

    Position startPos();
    Position goalPos();

    Field field() const;

private:
    Area m_sceneSize;
    std::vector<Area> m_obstacles;
    Field m_field;

    QComboBox *m_treeType;
    QSpinBox *m_numSteps;
    QPushButton *m_runButton;
    QPushButton *m_resetButton;
    QLabel *m_currNumNodes;
    QGraphicsEllipseItem *m_startPos;
    QGraphicsEllipseItem *m_goalPos;
    bool m_shouldDrawNodeIdInGUI;

    void initializeUIModel();
    TreeType mapFromQcomboBoxTextToTreeType(const std::string &currStr) const;
    void runClickedEnableRelatedWidgets(bool value);
    void onNewPointAdded(float x, float y);
    void resetScene();
};

#endif // UIMODEL_H
