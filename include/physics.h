// physics.h
#ifndef PHYSICS_H
#define PHYSICS_H

#include "node.h"
#include "vectors.h"
#include "physicsbody_manager.h"

class Physics
{
public:
    Physics(EngineNode *scene);
    ~Physics();
    
    void updatePhysics(float delta);
private:
    EngineNode *scene;

    void updatePhysicsFor(float delta, EngineNode *node);
    void updatePhysicsForChildrenOf(float delta, EngineNode *node);

    bool rectanglesOverlap(RectangleBody b1, RectangleBody b2, RectangleBody& intersection);
};

#endif