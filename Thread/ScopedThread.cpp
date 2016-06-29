#include "ScopedThread.h"

ScopedThread::ScopedThread(std::thread t) : m_thread(std::move(t))
{
    if (!m_thread.joinable())
    {
        throw std::logic_error("Thread passed into the constructor of scoped thread is not joinable");
    }
}

ScopedThread::~ScopedThread()
{
    m_thread.join();
}

