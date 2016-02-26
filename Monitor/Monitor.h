#ifndef MONITOR_H
#define MONITOR_H

#include <vector>

class UIModel;
class RRCCore;
class Area;

class Monitor
{
public:
    Monitor(UIModel *uiModel, RRCCore *rrcCore);
    virtual ~Monitor();

    Area GetSceneSize() const;
    std::vector<Area> GetObstacles() const;
    void OnButtonRunClicked();

    void OnNewPointAdded(float x, float y);

private:
    UIModel *m_uiModel;
    RRCCore *m_rrcCore;
};

#endif // MONITOR_H
