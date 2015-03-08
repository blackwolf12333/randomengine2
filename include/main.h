#ifndef MAIN_H
#define MAIN_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "scene.h"

class Main {
public:
    Main();
    ~Main();
    
    void initSDL();
    void initGameScene();
    void loop();
    void cleanup();
    void quit(int code);

    static SDL_Renderer *renderer;

private:
    SDL_Window *window;
    Scene *scene;
};

#endif