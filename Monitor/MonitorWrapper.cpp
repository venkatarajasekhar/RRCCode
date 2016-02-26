#include "MonitorWrapper.h"
#include "Monitor.h"

MonitorWrapper* MonitorWrapper::ms_instance = 0;

MonitorWrapper::MonitorWrapper(Monitor *monitor) : m_monitor(monitor)
{
    ms_instance = this;
}

MonitorWrapper::~MonitorWrapper() {

}

MonitorWrapper *MonitorWrapper::Instance() {
    return ms_instance;
}

Monitor *MonitorWrapper::GetMonitor() const {
    return m_monitor;
}



