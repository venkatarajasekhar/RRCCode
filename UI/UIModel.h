#ifndef UIMODEL_H
#define UIMODEL_H

#include <QGraphicsScene>
#include <RRCCommon/Area.h>
#include <vector>


class UIModel : public QGraphicsScene {
    Q_OBJECT

  public:
    UIModel(QObject *parent);
    Area GetSceneSize();
    std::vector<Area> GetObstacles();
    void SetSceneSize();
    void AddObstacles();

    void OnNewPointAdded(float x, float y);
public slots:
    void slot_run();

  private:
    void InitializeUIModel();

    Area sceneSize;
    std::vector<Area> obstacles;

  signals:
    void signal_dataAdded();
};

#endif // UIMODEL_H
