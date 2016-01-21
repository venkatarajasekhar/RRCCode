#-------------------------------------------------
#
# Project created by QtCreator 2015-12-27T12:45:07
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = RRC
TEMPLATE = app


SOURCES += main.cpp\
        MainWindow.cpp \
    UI/UIView.cpp \
    UI/UIModel.cpp \
    RRCConfig/RRCConfig.cpp \
    Packages/pugixml/src/pugixml.cpp \
    Exceptions/FileLoadErrorException.cpp \
    Monitor/Monitor.cpp \
    RRCCore/RRCCore.cpp \
    Monitor/MonitorWrapper.cpp \
    RRCCore/RRCPlanner.cpp \
    RRCCommon/State.cpp \
    RRCCommon/Position.cpp \
    RRCCommon/Node.cpp \
    RRCCommon/Area.cpp \
    RRCCommon/PositionRandom.cpp \
    RRCCommon/PositionFactory.cpp \
    RRCCore/PlanningUtil.cpp

HEADERS  += MainWindow.h \
    UI/UIView.h \
    UI/UIModel.h \
    RRCConfig/RRCConfig.h \
    Packages/pugixml/src/pugixml.hpp \
    Exceptions/FileLoadErrorException.h \
    Monitor/Monitor.h \
    RRCCore/RRCCore.h \
    Monitor/MonitorWrapper.h \
    RRCCore/RRCPlanner.h \
    RRCCommon/State.h \
    RRCCommon/Position.h \
    RRCCommon/Node.h \
    RRCCommon/Area.h \
    RRCCommon/PositionRandom.h \
    RRCCommon/PositionFactory.h \
    RRCCommon/PositionType.h \
    RRCCore/PlanningUtil.h

FORMS    +=

CONFIG += c++11
