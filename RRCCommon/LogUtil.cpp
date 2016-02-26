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

}

void LogUtil::error(const std::string &str) {

}

log4cplus::Logger LogUtil::initializeLogger() {
    initialize ();
    helpers::LogLog::getLogLog()->setInternalDebugging(true);
    SharedFileAppenderPtr appendPtr(
        new RollingFileAppender(LOG4CPLUS_TEXT("/home/lan/Documents/QtProjects/RRC/RRCLogging.txt"), 5*1024, 5, false, true));
    appendPtr->setLayout( std::auto_ptr<Layout>(new TTCCLayout()) );
    appendPtr->getloc();
    Logger::getRoot().addAppender(SharedAppenderPtr(appendPtr.get()));
    return Logger::getInstance(LOG4CPLUS_TEXT("RRCPlanning"));
}

