#include "RRCConfig.h"
#include <Exceptions/FileLoadErrorException.h>
#include <Packages/pugixml/src/pugixml.hpp>
#include <iostream>
#include <string>

RRCConfig* RRCConfig::ms_instance = 0;
const std::string RRCConfig::configFilePath = "/home/lan/Documents/QtProjects/RRC/Config.xml";

RRCConfig::RRCConfig() {

}

RRCConfig::~RRCConfig() {
    this->Release();
}

RRCConfig* RRCConfig::Instance() {
    if (ms_instance == 0) {
        ms_instance = new RRCConfig();
    }

    return ms_instance;
}

void RRCConfig::Release() {
    if (ms_instance) {
        delete ms_instance;
    }
    ms_instance = 0;
}

std::string RRCConfig::GetConfigFilePath() {
    return configFilePath;
}

float RRCConfig::InitializeFromConfig(std::string sectionName, std::string configName, float defaultValue) {
    try {
        pugi::xml_document doc;
        pugi::xml_parse_result result = doc.load_file(configFilePath.c_str());

        if (!result) {
            throw FileLoadErrorException();
        } else {
            pugi::xml_node nodes = doc.child("configuration").child(sectionName.c_str());
            std::string value = nodes.find_child_by_attribute("key", configName.c_str()).attribute("value").value();

            return std::stof(value);
        }
    } catch (std::exception &exp) {
        std::cout << "Exceptions thrown while processing RRCConfig: " << sectionName << " : " << configName << ", defaultValue = " << defaultValue << " will be used" << std::endl;
        std::cout << exp.what() << std::endl;
        return defaultValue;
    }
}


std::vector<Area> RRCConfig::InitializeObstaclesFromConfig() {
    try {
        std::vector<Area> res;
        pugi::xml_document doc;
        pugi::xml_parse_result result = doc.load_file(configFilePath.c_str());

        if (!result) {
            throw FileLoadErrorException();
        } else {
            pugi::xml_node nodes = doc.child("configuration").child("worldSettings");

            for (pugi::xml_node_iterator it = nodes.begin(); it != nodes.end(); ++it) {
                if (std::string(it->name()) == "obstacle") {
                    Area rect;
                    rect.setX(std::stof( it->find_child_by_attribute("key", "obstacleSWCornerX").attribute("value").value()));
                    rect.setY(std::stof( it->find_child_by_attribute("key", "obstacleSWCornerY").attribute("value").value()));
                    rect.setWidth(std::stof( it->find_child_by_attribute("key", "width").attribute("value").value()));
                    rect.setHeight(std::stof( it->find_child_by_attribute("key", "height").attribute("value").value()));
                    res.push_back(rect);
                }
            }

            return res;
        }
    } catch (std::exception &exp) {
        std::cout << "Exceptions thrown while processing RRCConfig!" << std::endl;
        std::cout << exp.what() << std::endl;
        return std::vector<Area>();
    }
}
