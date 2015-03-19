#ifndef NODE_H
#define NODE_H

#include <string>
#include <vector>

#include "physics_types.h"
#include "log.h"

#define RAD(g) (g * (M_PI / 180))
#define DEG(r) (r * (180 / M_PI))

#define NODE 0
#define SCENE 1
#define SPRITE 2
#define PARTICLE 3

class EngineNode {
public:
    EngineNode();
    EngineNode(const EngineNode &rhs);
    ~EngineNode();

    // identification
    /*
     * A unique name for this node, if it's not unique it can't be used
     */
    std::string name;
    void setName(std::string name);
    int type;

    // physics
    Body body;

    // children
    void addChild(EngineNode *child);
    EngineNode *getChildWithName(std::string name);
    std::vector<EngineNode*> children;
    bool hasChildren();
    
    // getters
    EngineNode *getParent();
    Vector getPosition();
    float getRotation();
    Velocity getVelocity();

    // setters
    void setPosition(Vector position);
    void setRotation(float rotation);
    void setVelocity(Velocity velocity);

    // properties
    Vector position;
    float rotation;
    Velocity velocity; // in pixels per frame

private:
    EngineNode *parent;
};

#endif
