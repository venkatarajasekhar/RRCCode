#ifndef RRCCONFIG_H
#define RRCCONFIG_H

#include <string>
#include <vector>
#include "Packages/Eigen/Core"

class Area;
class Position;

class RRCConfig {
    static RRCConfig* ms_instance;

  public:
    static RRCConfig* Instance();
    static void Release();

    /**
     * @brief GetConfigFilePath
     * @return
     */
    std::string GetConfigFilePath() const;

    /**
     * @brief InitializeFromConfig
     * @param sectionName
     * @param configName
     * @param defaultValue
     * @return
     */
    int initializeFromConfig(const std::string &sectionName, const std::string &configName, int defaultValue) const;
    bool initializeFromConfig(const std::string &sectionName, const std::string &configName, bool defaultValue) const;
    Eigen::MatrixXf initializeFromConfig(const std::string &sectionName, const std::string &configName, const Eigen::MatrixXf &defaultValue) const;

    /**
     * @brief InitializeObstaclesFromConfig
     * @return
     */
    std::vector<Area> initializeObstaclesFromConfig() const;
    std::vector<Position> initializeBasesFromConfig() const;

  private:
    RRCConfig();
    ~RRCConfig();
    const static std::string configFilePath;

    std::string getElementValue(std::string sectionName, std::string configName) const;

    /**
     * @brief extractValueFromString: extract float number from a string, two numbers are sepearted by ',' or ' '
     * @param str
     * @return
     */
    std::vector<float> extractValueFromString(const std::string &str) const;
    bool validateMatrixElementValue(const std::string &str) const;

    /**
     * @brief sqrtHelper: return the integer whos square is less than or equal to the function parameter
     * @param val
     */
    unsigned int sqrtHelper(unsigned int val) const;
};

#endif // RRCCONFIG_H
