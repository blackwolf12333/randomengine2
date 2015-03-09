/* yaml_config.cpp */

#include "yaml_config.h"
#include "spritenode.h"

namespace YAML {
    template<>
    struct convert<Point> {
      static Node encode(const Point& rhs) {
        Node node;
        node["x"] = rhs.x;
        node["y"] = rhs.y;
        return node;
      }

      static bool decode(const Node& node, Point& rhs) {
        if(node.size() != 2) {
            printf("%f\n", node["x"].as<float>());
          return false;
        }

        
        rhs.x = node["x"].as<float>();
        rhs.y = node["y"].as<float>();
        return true;
      }
    };

    template<>
    struct convert<Velocity> {
      static Node encode(const Velocity& rhs) {
        Node node;
        node["direction"] = rhs.direction;
        node["magnitude"] = rhs.magnitude;
        return node;
      }

      static bool decode(const Node& node, Velocity& rhs) {
        if(node.size() != 2) {
          return false;
        }

        rhs.direction = node["direction"].as<Point>();
        rhs.magnitude = node["magnitude"].as<float>();
        return true;
      }
    };

    template<>
    struct convert<EngineNode*> {
      static Node encode(EngineNode *rhs) {
        Node node;
        std::string type;
        if(rhs->type == 0) {
            type = "node";
        } else if(rhs->type == 1) {
            type = "scene";
        } else if(rhs->type == 3) {
            type = "particle";
        }
        node[type]["name"] = rhs->name;
        node[type]["type"] = rhs->type;
        node[type]["velocity"] = rhs->getVelocity();
        node[type]["position"] = rhs->getPosition();
        node[type]["rotation"] = rhs->getRotation();

        for(unsigned i = 0; i < rhs->children.size(); i++) {
            if(rhs->children[i]->type == SPRITE) {
                node[type]["children"].push_back((SpriteNode*)rhs->children[i]);
            } else {
                node[type]["children"].push_back(rhs->children[i]);
            }
        }
        return node;
      }

      static bool decode(const Node& node, EngineNode *rhs) {
        if((!node["root"]["node"].IsDefined()) && (!node["root"]["scene"].IsDefined()) && (!node["particle"].IsDefined())) {
            return false;
        }
        std::string type;

        if(node["root"]["node"].IsDefined()) {
            type = "node";       
        } else if(node["root"]["scene"].IsDefined()) {
            type = "scene";
        }
        const Node n = node["root"][type];

        rhs->name = n["name"].as<std::string>();
        rhs->type = n["type"].as<int>();
        rhs->setVelocity(n["velocity"].as<Velocity>());
        rhs->setPosition(n["position"].as<Point>());
        rhs->setRotation(n["rotation"].as<float>());

        for(unsigned i = 0; i < n["children"].size(); i++) {
            if(n["children"]["type"].as<int>() == SPRITE) {
                rhs->addChild(n["children"].as<SpriteNode*>());
            } else {
                rhs->addChild(n["children"].as<EngineNode*>());
            }
        }

        return true;
      }
    };

    template<>
    struct convert<SpriteNode*> {
      static Node encode(SpriteNode *rhs) {
        Node node;

        node["sprite"]["name"] = rhs->name;
        node["sprite"]["type"] = rhs->type;
        node["sprite"]["velocity"] = rhs->getVelocity();
        node["sprite"]["position"] = rhs->getPosition();
        node["sprite"]["rotation"] = rhs->getRotation();
        node["sprite"]["texture_path"] = rhs->getTexturePath();

        for(unsigned i = 0; i < rhs->children.size(); i++) {
            if(rhs->children[i]->type == SPRITE) {
                //node["sprite"]["children"].push_back((casttospritenode)rhs->children[i]);
            } else {
                node["sprite"]["children"].push_back(rhs->children[i]);
            }
            
        }
        return node;
      }

      static bool decode(const Node& node, SpriteNode *rhs) {
        if(!node["root"]["sprite"].IsDefined()) {
            printf("no sprite\n");
            return false;
        }
        rhs->name = "test";
        //TODO fix
        return true;
      }
    };
}

YamlConfig::YamlConfig() {}
YamlConfig::~YamlConfig() {}

void YamlConfig::write(std::string path, EngineNode *node) {
    YAML::Node doc = YAML::LoadFile(path);

    doc["root"] = node;

    std::ofstream fout(path);
    fout << doc;
}

bool YamlConfig::writeNode(EngineNode *node) {
    return false;
}

EngineNode *YamlConfig::read(std::string path) {
    YAML::Node doc = YAML::LoadFile(path);
    EngineNode *node = readNode(doc);
    Point point = readPoint(doc);
    Velocity vel = readVelocity(doc);
    
    printf("%f\n", vel.magnitude);
    printf("%f, %f\n", point.x, point.y);
    printf("%s\n", node->name.c_str());
    return node;
}

EngineNode *YamlConfig::readNode(YAML::Node& yaml_node) {
    return yaml_node.as<EngineNode*>();
}

Velocity YamlConfig::readVelocity(YAML::Node& node) {
    return node["root"]["scene"]["velocity"].as<Velocity>();
}

Point YamlConfig::readPoint(YAML::Node& node) {
    return node["root"]["scene"]["position"].as<Point>();
}
