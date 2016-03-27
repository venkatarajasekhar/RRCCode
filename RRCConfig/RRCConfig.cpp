#include "RRCConfig.h"
#include <Exceptions/FileLoadErrorException.h>
#include <Packages/pugixml/src/pugixml.hpp>
#include <RRCCommon/Area.h>
#include <iostream>
#include "RRCCommon/LogUtil.h"
#include <sstream>
#include <stdexcept>

RRCConfig* RRCConfig::ms_instance = 0;
const std::string RRCConfig::configFilePath = "/home/lan/Documents/QtProjects/RRC/Config.xml";

RRCConfig::RRCConfig() {

}

RRCConfig::~RRCConfig() {
    Release();
}

std::string RRCConfig::getElementValue(std::string sectionName, std::string configName) const {
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file(configFilePath.c_str());

    if (!result) {
        throw FileLoadErrorException();
    } else {
        pugi::xml_node nodes = doc.child("configuration").child(sectionName.c_str());
        std::string value = nodes.find_child_by_attribute("key", configName.c_str()).attribute("value").value();

        return value;
    }
}

std::vector<float> RRCConfig::extractValueFromString(const std::string &str) const {
    if (! validateMatrixElementValue(str)) throw std::invalid_argument("Matrix element is not valid");
    std::vector<float> res;
    unsigned int pos = 0;
    for(unsigned int i = 0; i < str.size(); ++i) {
        if (str[i] == ',' || str[i] == ' ') {
            if (pos < i) {
                std::string value = str.substr(pos, i - pos);
                res.push_back(std::stof(value));
            }
            pos = i + 1;
        } else if (i == str.size() -1) {
            std::string value = str.substr(pos, i - pos + 1);
            res.push_back(std::stof(value));
        }
    }

    return res;
}

bool RRCConfig::validateMatrixElementValue(const std::string &str) const {
    bool isStrValid = true;
    for(std::string::const_iterator iter = str.begin(); iter != str.end(); ++iter) {
        if ( ! ((*iter - '0' >= 0 && *iter - '0' <= 9) || *iter == '.' || *iter == ',' || *iter == ' ') ) {
            isStrValid = false;
            break;
        }
    }

    return isStrValid;
}

unsigned int RRCConfig::sqrtHelper(unsigned int val) const {
    if (val == 0) return 0;
    unsigned int low = 1, high = val, mid = 0, lastMid = 0;
    while(low <= high) {
        mid = low + (high - low) / 2;
        if (mid == val / mid) return mid;
        if (mid < val / mid) {
            low = mid + 1;
            lastMid = mid;
        } else {
            high = mid - 1;
        }
    }

    return lastMid;
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

std::string RRCConfig::GetConfigFilePath() const {
    return configFilePath;
}

int RRCConfig::initializeFromConfig(const std::string &sectionName, const std::string &configName, int defaultValue) const {
    try {
        std::string value = getElementValue(sectionName, configName);
        return std::stoi(value);
    } catch (const std::exception &exp) {
        std::stringstream ss;
        ss << "Exceptions thrown while processing RRCConfig: " << sectionName << " : " << configName << ", defaultValue = " << defaultValue << " will be used!" << std::string(exp.what());
        LogUtil::error(ss.str());

        return defaultValue;
    }
}

bool RRCConfig::initializeFromConfig(const std::string &sectionName, const std::string &configName, bool defaultValue) const {
    try {
        std::string value = getElementValue(sectionName, configName);
        if (value == "false") {
            return false;
        } else if (value == "true") {
            return true;
        } else {
            throw std::invalid_argument("initializeFromConfig");
        }
    } catch (const std::exception &exp) {
        std::stringstream ss;
        ss << "Exceptions thrown while processing RRCConfig: " << sectionName << " : " << configName << ", defaultValue = " << defaultValue << " will be used!" << std::string(exp.what());
        LogUtil::error(ss.str());

        return defaultValue;
    }
}

Eigen::MatrixXd RRCConfig::initializeFromConfig(const std::string &sectionName, const std::string &configName, const Eigen::MatrixXd &defaultValue) const {
    try {
        std::string str = getElementValue(sectionName, configName);
        std::vector<float> elements = extractValueFromString(str);

        unsigned int numElements = elements.size();
        unsigned int sqrtOfNumElements = sqrtHelper(numElements);
        if (sqrtOfNumElements * sqrtOfNumElements != numElements) throw std::invalid_argument("In config file, the number of elments for matrix should be a square of an interger.");

        Eigen::MatrixXd  res(sqrtOfNumElements, sqrtOfNumElements);
        for(unsigned int i = 0; i < sqrtOfNumElements; ++i) {
            for(unsigned int j = 0; j < sqrtOfNumElements; ++j) {
                res(i, j) = elements[i * sqrtOfNumElements + j];
            }
        }

        return res;
    } catch (const std::exception &exp) {
        std::stringstream ss;
        ss << "Exceptions thrown while processing RRCConfig: " << sectionName << " : " << configName << ", defaultValue = " << defaultValue << " will be used!" << std::string(exp.what());
        LogUtil::error(ss.str());

        return defaultValue;
    }
}


std::vector<Area> RRCConfig::initializeObstaclesFromConfig() const {
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
    } catch (const std::exception &exp) {
         LogUtil::error("Exceptions thrown while loading obstacles from config file!" + std::string(exp.what()));
        return std::vector<Area>();
    }
}

std::vector<Position> RRCConfig::initializeBasesFromConfig() const
{
    try {
        std::vector<Position> res;
        pugi::xml_document doc;
        pugi::xml_parse_result result = doc.load_file(configFilePath.c_str());

        if (!result) {
            throw FileLoadErrorException();
        } else {
            pugi::xml_node nodes = doc.child("configuration").child("Field");

            for (pugi::xml_node_iterator it = nodes.begin(); it != nodes.end(); ++it) {
                if (std::string(it->name()) == "basis") {
                    Position basisPos;
                    basisPos.setX(std::stof( it->find_child_by_attribute("key", "basisPosX").attribute("value").value()));
                    basisPos.setY(std::stof( it->find_child_by_attribute("key", "basisPosY").attribute("value").value()));

                    res.push_back(basisPos);
                }
            }

            return res;
        }
    } catch (const std::exception &exp) {
        LogUtil::error("Exceptions thrown while loading bases from config file!" + std::string(exp.what()));
        throw;
    }
}
