#ifndef SCOPEDTHREAD_H
#define SCOPEDTHREAD_H
#include <thread>

class ScopedThread
{
public:
    explicit ScopedThread(std::thread t);
    ~ScopedThread();
    ScopedThread(const ScopedThread &t)=delete;
    ScopedThread & operator=(const ScopedThread &t)=delete;

private:
    std::thread m_thread;
};

#endif // SCOPEDTHREAD_H
