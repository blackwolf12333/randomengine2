#ifndef YAML_CONFIG_H
#define YAML_CONFIG_H

#include <fstream>
#include <yaml-cpp/yaml.h>
#include <string>

#include "node.h"

class YamlConfig
{
public:
    YamlConfig();
    ~YamlConfig();
    
    void write(std::string path, const EngineNode *node);
    bool writeNode(EngineNode *node);
    EngineNode *read(std::string path);

    EngineNode *readNode(YAML::Node& yaml_node);
    Velocity readVelocity(YAML::Node& node);
    Point readPoint(YAML::Node& node);
};

#endif