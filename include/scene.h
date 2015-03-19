#ifndef SCENE_H
#define SCENE_H

#include <queue>
#include <cmath>

#include "spritenode.h"
#include "physics.h"

class Scene : public EngineNode
{
public:
    Scene();
    virtual ~Scene();

    void renderScene();
    void renderNode(EngineNode *node);

    virtual void update(float delta);
    virtual void onInput(SDL_Event e);

    void updatePhysics(float delta);
private:
    SDL_Renderer *renderer;
    Physics *physics;

    void updatePhysicsForChildrenOf(float delta, EngineNode *node);
};

#endif