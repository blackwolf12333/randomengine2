#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "spritenode.h"
#include "scene.h"

#define SIZE_SMALL  1
#define SIZE_MEDIUM 2
#define SIZE_LARGE  3

#define PLAYER_SMALL_TEXTURE  "assets/jelly_player/jelly_player_small.png"
#define PLAYER_MEDIUM_TEXTURE "assets/jelly_player/jelly_player_medium.png"
#define PLAYER_LARGE_TEXTURE "assets/jelly_player/jelly_player_large.png"

/**
 * This is the main game scene. Here you do your updates, load nodes, handle input etc.
 */
class GameScene : public Scene
{
public:
    GameScene(std::string file);
    ~GameScene();
    
    void update(float delta);

    void onInput(SDL_Event e);
private:
    void collideWithJelly(std::string jelly);
    int getJellySize(std::string jelly);
    void eatJelly(std::string jelly);
    void fallToBits();
    void grow();

    int player_size;
    bool pause;
};

#endif