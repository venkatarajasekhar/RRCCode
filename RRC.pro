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
    RRCCommon/LogUtil.cpp \
    RRCCommon/Range.cpp \
    Exceptions/NotImplementedException.cpp \
    RRCCore/RRTTree.cpp \
    RRCCore/KdTreeWrapper.cpp \
    RRCCommon/TreeFactory.cpp \
    RRCCore/RandomTree.cpp \
    Exceptions/NotFoundNearestNeighborException.cpp \
    RRCCore/RRTStarTree.cpp \
    RRCCore/RRCTree.cpp \
    RRCCore/Field.cpp \
    RRCCore/KalmanFilter.cpp \
    RRCCore/Sensor.cpp \
    RRCCommon/EigenVectorXdUtil.cpp \
    Thread/ScopedThread.cpp

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
    RRCCommon/LogUtil.h \
    RRCCommon/Range.h \
    Exceptions/NotImplementedException.h \
    RRCCore/RRTTree.h \
    RRCCore/KdTreeWrapper.h \
    RRCCommon/TreeType.h \
    RRCCommon/TreeFactory.h \
    RRCCore/RandomTree.h \
    Exceptions/NotFoundNearestNeighborException.h \
    RRCCore/RRTStarTree.h \
    RRCCore/RRCTree.h \
    RRCCore/Field.h \
    RRCCore/KalmanFilter.h \
    RRCCore/Sensor.h \
    RRCCommon/EigenVectorXdUtil.h \
    Thread/ScopedThread.h


FORMS    +=

CONFIG += c++11

LIBS += -L/usr/local/lib/ -llog4cplus
