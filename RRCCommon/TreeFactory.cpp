#include "TreeFactory.h"
#include "RRCCore/RRTTree.h"
#include "RRCCore/RRTStarTree.h"
#include "RRCCore/RRCTree.h"
#include "RRCConfig/RRCConfig.h"
#include "RRCCore/Sensor.h"
#include "Monitor/Monitor.h"
#include "Monitor/MonitorWrapper.h"
#include <RRCCore/KalmanFilter.h>

TreeFactory::TreeFactory() {

}

std::unique_ptr<RandomTree> TreeFactory::newTree(TreeType treeType) {
    std::unique_ptr<RandomTree> res = nullptr;
    switch(treeType) {
    case TreeType::RandomRRTTree:
        res = std::unique_ptr<RandomTree>(new RRTTree());
        break;
    case TreeType::RandomRRTStarTree:
        res = std::unique_ptr<RandomTree>(new RRTStarTree());
        break;
    case TreeType::RandomRRCTree: {
        float sensorOutputScale = RRCConfig::Instance()->initializeFromConfig("Sensor", "sensorOutputScale", 20);
        float sensingRange = RRCConfig::Instance()->initializeFromConfig("Sensor", "sensingRange", 50);
        float sensorNoise = RRCConfig::Instance()->initializeFromConfig("Sensor", "sensorNoise", 15);
        Sensor newSensor(sensingRange, sensorOutputScale, sensorNoise);
        Field newField = MonitorWrapper::Instance()->getMonitor()->getField();
        KalmanFilter filter(newField, newSensor);
        res = std::unique_ptr<RandomTree>(new RRCTree(filter));
        break;
    }
    default:
        // do nothing
        break;
    }

    return res;
}

