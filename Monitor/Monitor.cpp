#include "Monitor.h"
#include <RRCCommon/Area.h>
#include <UI/UIModel.h>

Monitor::Monitor(UIModel *uiModel, RRCCore *rrcCore) {
    this->uiModel = uiModel;
    this->rrcCore = rrcCore;
}

Monitor::~Monitor() {

}

Area Monitor::GetSceneSize() const {
    return this->uiModel->GetSceneSize();
}

void Monitor::OnButtonRunClicked()
{
    rrcCore->Run();
}

void Monitor::OnNewPointAdded(float x, float y)
{
    uiModel->OnNewPointAdded(x, y);
}
