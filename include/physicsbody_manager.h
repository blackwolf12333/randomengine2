#ifndef PHYSICSBODY_MANAGER_H
#define PHYSICSBODY_MANAGER_H

#include "physics_types.h"
#include <map>

class PhysicsbodyManager
{
public:
    PhysicsbodyManager();
    ~PhysicsbodyManager();
    
    void addBody(std::string name, Body body);
    void delBody(std::string name);

    std::map<std::string, Body> physicsBodies;
};

#endif