#include "physicsbody_manager.h"

PhysicsbodyManager::PhysicsbodyManager() {}

void PhysicsbodyManager::addBody(std::string name, Body body) {
    physicsBodies.insert(std::pair<std::string,Body>(name, body));
}

void PhysicsbodyManager::delBody(std::string name) {
    physicsBodies.erase(name);
}