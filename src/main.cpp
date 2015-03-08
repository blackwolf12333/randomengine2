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
    if (init != 0){
        std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
        this->quit(INIT_FAILED);
    }

    this->window = SDL_CreateWindow("Hello World!", 100, 100, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (this->window == NULL){
        std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        this->quit(WINDOW_INIT_FAILED);
    }

    printf("NumRenderDrivers: %d\n", SDL_GetNumRenderDrivers());
    for (int i = 0; i < SDL_GetNumRenderDrivers(); i++) {
        SDL_Renderer *r = SDL_CreateRenderer(this->window, i, 0);
        SDL_RendererInfo info;
        SDL_GetRendererInfo(r, &info);
        printf("Renderer name: %s\n", info.name);
        SDL_DestroyRenderer(r);
    }

    renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_SOFTWARE);
    if (renderer == NULL){
        std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        this->quit(RENDERER_INIT_FAILED);
    }

    // load support for the JPG and PNG image formats
    int flags = IMG_INIT_JPG|IMG_INIT_PNG;
    int initted = IMG_Init(flags);
    if((initted&flags) != flags) {
        printf("IMG_Init: Failed to init required jpg and png support!\n");
        printf("IMG_Init: %s\n", IMG_GetError());
        this->quit(IMAGE_INIT_FAILED); // we can't do shit like this...
    }

    // Set up the blank color
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    // any errors? display them now and quit.
    const char *errors = SDL_GetError();
    if(errors == NULL) { // no problems at start up
        return;
    } else {
        printf("Initial errors: %s\n", errors);
        //this->quit(INIT_FAILED);
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
        SDL_RenderClear(renderer);

        // update
        this->scene->update(delta);
        this->scene->updatePhysics(delta);

        scene->renderScene();

        // Swap buffers
        SDL_RenderPresent(this->renderer);
    }
}

/**
 * Clean up and quit. This should always be executed just before quiting the game.
 */
void Main::cleanup() {
    delete scene;
    SDL_DestroyRenderer(this->renderer);
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