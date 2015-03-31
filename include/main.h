#ifndef MAIN_H
#define MAIN_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "scene.h"

class Main {
public:
    Main(char *argv[], int argc);
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
    std::string main_scene_file;
};

#endif