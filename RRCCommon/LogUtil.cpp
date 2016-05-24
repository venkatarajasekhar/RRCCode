#include "LogUtil.h"
#include <log4cplus/fileappender.h>
#include <log4cplus/layout.h>
#include <log4cplus/helpers/loglog.h>
#include <log4cplus/loggingmacros.h>

using namespace log4cplus;

const log4cplus::Logger LogUtil::ms_logger = LogUtil::initializeLogger();

LogUtil::LogUtil() {

}

void LogUtil::info(const std::string &str) {
    LOG4CPLUS_INFO(ms_logger, str);
}

void LogUtil::warn(const std::string &str) {
    LOG4CPLUS_WARN(ms_logger, str);
}

void LogUtil::error(const std::string &str) {
    LOG4CPLUS_ERROR(ms_logger, str);
}

log4cplus::Logger LogUtil::initializeLogger() {
    initialize ();
    helpers::LogLog::getLogLog()->setInternalDebugging(true);
    SharedFileAppenderPtr appendPtr(
        new RollingFileAppender(LOG4CPLUS_TEXT("RRCLog.txt"), 10 *1024 *1024, 5, true));
    std::auto_ptr<Layout> layout = std::auto_ptr<Layout>(new TTCCLayout(true));
    appendPtr->setLayout(layout);
    appendPtr->getloc();
    Logger::getRoot().addAppender(SharedAppenderPtr(appendPtr.get()));
    return Logger::getInstance(LOG4CPLUS_TEXT("RRCPlanning"));
}

