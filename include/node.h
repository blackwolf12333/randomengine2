#ifndef NODE_H
#define NODE_H

#include <string>
#include <vector>

#define RAD(g) (g * (M_PI / 180))
#define DEG(r) (r * (180 / M_PI))

typedef struct Point_t {
    float x, y;
} Point;

typedef Point Vector;

typedef struct Velocity_t {
    Vector direction;
    float magnitude;
} Velocity;

typedef struct Body_t {
    Point p;
    float w, h;
    char categoryBitmask;
    char collisionBitmask;
    char contactBitmask;
    bool staticBody;
} Body;

#define NODE 0
#define SCENE 1
#define SPRITE 2
#define PARTICLE 3

class EngineNode {
public:
    EngineNode();
    EngineNode(const EngineNode &rhs);
    ~EngineNode();

    std::string name;
    void setName(std::string name);

    Body body;

    void addChild(EngineNode *child);
    EngineNode *getChildWithName(std::string name);
    std::vector<EngineNode*> children;
    int type;

    bool hasChildren();
    
    // getters
    EngineNode *getParent();
    Point getPosition();
    float getRotation();
    Velocity getVelocity();

    // setters
    void setPosition(Point position);
    void setRotation(float rotation);
    void setVelocity(Velocity velocity);

    Point position;
    float rotation;
    Velocity velocity; // in pixels per frame

private:
    EngineNode *parent;
};

#endif