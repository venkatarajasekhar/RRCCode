#ifndef MONITOR_H
#define MONITOR_H

#include <RRCCore/RRCCore.h>


class UIModel;
class RRCCore;
class Area;

class Monitor
{
public:
    Monitor(UIModel *uiModel, RRCCore *rrcCore);
    virtual ~Monitor();
    Area GetSceneSize() const;
    void OnButtonRunClicked();

    void OnNewPointAdded(float x, float y);

private:
    UIModel *uiModel;
    RRCCore *rrcCore;
};

#endif // MONITOR_H
