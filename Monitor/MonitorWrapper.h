#ifndef MONITORWRAPPER_H
#define MONITORWRAPPER_H

class Monitor;

class MonitorWrapper
{
public:
    MonitorWrapper(Monitor *monitor);
    virtual ~MonitorWrapper();
    static MonitorWrapper *Instance();
    Monitor *getMonitor() const;

private:
    static MonitorWrapper *ms_instance;
    Monitor *m_monitor;
};

#endif // MONITORWRAPPER_H
