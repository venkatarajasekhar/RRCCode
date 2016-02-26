#ifndef LOGUTIL_H
#define LOGUTIL_H

#include <string>
#include <log4cplus/logger.h>

class LogUtil
{
public:
    LogUtil();
    static void info(const std::string &str);
    static void warn(const std::string &str);
    static void error(const std::string &str);

private:
    static const log4cplus::Logger ms_logger;
    static log4cplus::Logger initializeLogger();
};

#endif // LOGUTIL_H
