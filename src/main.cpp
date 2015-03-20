#include "main.h"
#include "gamescene.h"
#include "yaml_config.h"
#include "log.h"

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
        LOG("test.log", "SDL_Init Error: %s", SDL_GetError());
        this->quit(INIT_FAILED);
    }

    this->window = SDL_CreateWindow("Hello World!", 100, 100, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (this->window == NULL || strlen(SDL_GetError()) != 0){
        LOG("test.log", "SDL_CreateWindow Error: %s", SDL_GetError());
        this->quit(WINDOW_INIT_FAILED);
    }

    printf("NumRenderDrivers: %d\n", SDL_GetNumRenderDrivers());
    /* Without this I can't make any renderer work, my best guess is that this is a bug and will
       be fixed sooner or later */
    SDL_GL_LoadLibrary("/usr/lib/libGL.so");
    LOG("test.log", "SDL_GL_LoadLibrary: %s\n", SDL_GetError());
    
    Main::renderer = SDL_CreateRenderer(this->window, 1, SDL_RENDERER_ACCELERATED);
    if (Main::renderer == NULL || strlen(SDL_GetError()) != 0){
        LOG("test.log", "SDL_CreateRenderer Error: %s", SDL_GetError());
        this->quit(RENDERER_INIT_FAILED);
    }

    // load support for the JPG and PNG image formats
    int flags = IMG_INIT_JPG|IMG_INIT_PNG;
    int initted = IMG_Init(flags);
    if((initted&flags) != flags || strlen(IMG_GetError()) != 0) {
        LOG("test.log", "IMG_Init: Failed to init required jpg and png support!\n", 0);
        LOG("test.log", "IMG_Init: %s\n", IMG_GetError());
        this->quit(IMAGE_INIT_FAILED); // we can't do shit like this...
    }

    // Set up the blank color
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    // any errors? display them now and quit.
    const char *errors = SDL_GetError();
    if(errors != NULL || strlen(errors) == 0) { // no problems at start up
        return;
    } else {
        LOG("test.log", "Initial errors: %s\n", errors);
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
    bool paused = false;
    float current_time, old_time;
    current_time = SDL_GetTicks();
    SDL_Event e;
    while (running) {
        old_time = current_time;
        current_time = (float)SDL_GetTicks();
        float delta = (current_time - old_time) / 1000; // get milliseconds per second

        while (SDL_PollEvent(&e)){
            //If user closes the window
            if (e.type == SDL_QUIT){
                running = false;
                break;
            }
            if (e.type == SDL_KEYDOWN) {
                if(e.key.keysym.sym == SDLK_ESCAPE) { // change this to a paused state
                    running = false;
                    break;
                }
            }
            if (e.type == SDL_WINDOWEVENT) {
                switch(e.window.event) {
                case SDL_WINDOWEVENT_HIDDEN:
                case SDL_WINDOWEVENT_LEAVE:
                case SDL_WINDOWEVENT_FOCUS_LOST:
                case SDL_WINDOWEVENT_MINIMIZED:
                    printf("paused\n");
                    paused = true;
                    break;
                case SDL_WINDOWEVENT_SHOWN:
                case SDL_WINDOWEVENT_EXPOSED:
                case SDL_WINDOWEVENT_FOCUS_GAINED:
                case SDL_WINDOWEVENT_ENTER:
                case SDL_WINDOWEVENT_MAXIMIZED:
                    printf("unpaused\n");
                    paused = false;
                    break;
                default:
                    break;
                }
            }
            // should probably filter the input here so the scene won't have to deal with
            // window management, eg focus/quit
            scene->onInput(e);
        }

        // clear the screen with black
        SDL_RenderClear(Main::renderer);

        // update
        if (!paused) {
            this->scene->update(delta);
            this->scene->updatePhysics(delta);

            scene->renderScene();
        }

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
        LOG("test.log",  "Exit error code: %d\n", code);
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
