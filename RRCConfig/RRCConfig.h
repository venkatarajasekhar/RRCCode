#ifndef RRCCONFIG_H
#define RRCCONFIG_H

#include <string>
#include <vector>

class Area;

class RRCConfig {
    static RRCConfig* ms_instance;

  public:
    static RRCConfig* Instance();
    static void Release();

    /**
     * @brief GetConfigFilePath
     * @return
     */
    std::string GetConfigFilePath();

    /**
     * @brief InitializeFromConfig
     * @param sectionName
     * @param configName
     * @param defaultValue
     * @return
     */
    float InitializeFromConfig(std::string sectionName, std::string configName, float defaultValue);

    /**
     * @brief InitializeObstaclesFromConfig
     * @return
     */
    std::vector<Area> InitializeObstaclesFromConfig();

  private:
    RRCConfig();
    virtual ~RRCConfig();
    const static std::string configFilePath;
};

#endif // RRCCONFIG_H
