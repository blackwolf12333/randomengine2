#include "main.h"
#include "gamescene.h"
#include "yaml_config.h"

#include <iostream>
#include <stdlib.h>

#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 768

#define INIT_FAILED             (-1)
#define WINDOW_INIT_FAILED      (-2)
#define RENDERER_INIT_FAILED    (-3)
#define IMAGE_INIT_FAILED       (-4)

Main::Main() {}
Main::~Main() {}

SDL_Renderer *Main::renderer;

/**
 * Initialize SDL2 and handle any errors that might pop up
 */
void Main::initSDL() {
    int init = SDL_Init(SDL_INIT_EVERYTHING);
    if (init != 0) {
        std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
        this->quit(INIT_FAILED);
    }

    this->window = SDL_CreateWindow("Hello World!", 100, 100, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (this->window == NULL || strlen(SDL_GetError()) != 0){
        std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        this->quit(WINDOW_INIT_FAILED);
    }

    printf("NumRenderDrivers: %d\n", SDL_GetNumRenderDrivers());
    /* Without this I can't make any renderer work, my best guess is that this is a bug and will
       be fixed sooner or later */
    SDL_GL_LoadLibrary("/usr/lib/libGL.so");
    std::cout << "SDL_GL_LoadLibrary: " << SDL_GetError() << std::endl;
    
    Main::renderer = SDL_CreateRenderer(this->window, 1, SDL_RENDERER_ACCELERATED);
    if (Main::renderer == NULL || strlen(SDL_GetError()) != 0){
        std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        this->quit(RENDERER_INIT_FAILED);
    }

    // load support for the JPG and PNG image formats
    int flags = IMG_INIT_JPG|IMG_INIT_PNG;
    int initted = IMG_Init(flags);
    if((initted&flags) != flags || strlen(IMG_GetError()) != 0) {
        printf("IMG_Init: Failed to init required jpg and png support!\n");
        printf("IMG_Init: %s\n", IMG_GetError());
        this->quit(IMAGE_INIT_FAILED); // we can't do shit like this...
    }

    // Set up the blank color
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    // any errors? display them now and quit.
    const char *errors = SDL_GetError();
    if(errors != NULL || strlen(errors) == 0) { // no problems at start up
        return;
    } else {
        printf("Initial errors: %s\n", errors);
        this->quit(INIT_FAILED);
    }
}

void Main::initGameScene() {
    scene = new GameScene();
}

/**
 * Main loop responsible for running updates on the scene and rendering the scene.
 * Keeps track of frame time as well for fancy graphs :)
 */
void Main::loop() {
    bool running = true;
    Uint32 current_time, old_time;
    current_time = SDL_GetTicks();
    SDL_Event e;
    while (running) {
        old_time = current_time;
        current_time = SDL_GetTicks();
        Uint32 delta = current_time - old_time;

        while (SDL_PollEvent(&e)){
            //If user closes the window
            if (e.type == SDL_QUIT){
                running = false;
                break;
            }
            if (e.type == SDL_KEYDOWN) {
                if(e.key.keysym.sym == SDLK_ESCAPE) {
                    running = false;
                    break;
                }
            }
            scene->onInput(e);
        }

        // clear the screen with black
        SDL_RenderClear(Main::renderer);

        // update
        this->scene->update(delta);
        this->scene->updatePhysics(delta);

        scene->renderScene();

        // Swap buffers
        SDL_RenderPresent(Main::renderer);
    }
}

/**
 * Clean up and quit. This should always be executed just before quiting the game.
 */
void Main::cleanup() {
    delete scene;
    SDL_DestroyRenderer(Main::renderer);
    SDL_DestroyWindow(this->window);
    IMG_Quit();
    SDL_Quit();
}

void Main::quit(int code) {
    cleanup();
    if (code == 0) {
        exit(EXIT_SUCCESS);
    } else {
        printf("Exit error code: %d\n", code);
        exit(EXIT_FAILURE);
    }
}

int main() {
    Main *main = new Main();
    main->initSDL();
    main->initGameScene();
    main->loop();
    main->cleanup();
    delete main;
}
