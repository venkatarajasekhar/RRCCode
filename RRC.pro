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
    RRCCommon/State.cpp \
    RRCCommon/Position.cpp \
    RRCCommon/Node.cpp \
    RRCCommon/Area.cpp \
    RRCCore/PlanningUtil.cpp \
    RRCCommon/NodeFactory.cpp \
    RRCCommon/Tree.cpp \
    RRCCore/KdTree.cpp \
    RRCCore/RandomTreeNode.cpp \
    RRCCore/KdTreeNode.cpp \
    RRCCommon/LogUtil.cpp \
    RRCCommon/Range.cpp \
    Exceptions/NotImplementedException.cpp

HEADERS  += MainWindow.h \
    UI/UIView.h \
    UI/UIModel.h \
    RRCConfig/RRCConfig.h \
    Packages/pugixml/src/pugixml.hpp \
    Exceptions/FileLoadErrorException.h \
    Monitor/Monitor.h \
    RRCCore/RRCCore.h \
    Monitor/MonitorWrapper.h \
    RRCCommon/State.h \
    RRCCommon/Position.h \
    RRCCommon/Node.h \
    RRCCommon/Area.h \
    RRCCore/PlanningUtil.h \
    RRCCommon/NodeType.h \
    RRCCommon/NodeFactory.h \
    RRCCommon/Tree.h \
    RRCCore/KdTree.h \
    RRCCore/RandomTreeNode.h \
    RRCCore/KdTreeNode.h \
    RRCCommon/LogUtil.h \
    RRCCommon/Range.h \
    Exceptions/NotImplementedException.h

FORMS    +=

CONFIG += c++11

unix:!macx: LIBS += -L$$PWD/../../../../../usr/local/lib/ -llog4cplus

INCLUDEPATH += $$PWD/../../../../../usr/local/include
DEPENDPATH += $$PWD/../../../../../usr/local/include
