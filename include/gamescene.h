#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "spritenode.h"
#include "scene.h"

/**
 * This is the main game scene. Here you do your updates, load nodes, handle input etc.
 */
class GameScene : public Scene
{
public:
    GameScene();
    ~GameScene();
    
    void update(float delta);

    void onInput(SDL_Event e);
private:
    bool jumping;
    bool onground;

    float gravity = 100;
    float jumpingSpeed = 200;
};

#endif