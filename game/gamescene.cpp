#include "gamescene.h"
#include "yaml_config.h"

GameScene::GameScene() {
    YamlConfig *yaml = new YamlConfig();
    EngineNode *scene = yaml->read("test.yaml");
    this->children = scene->children;
    this->velocity = scene->velocity;
    this->position = scene->position;
    this->rotation = scene->rotation;
    this->name = scene->name;
    this->type = scene->type;
}

GameScene::~GameScene() {}

void GameScene::onInput(SDL_Event e) {
    if (e.type == SDL_KEYDOWN) {
        Velocity v = this->getChildWithName("player")->getVelocity();
        if (e.key.keysym.sym == SDLK_w) {
            v.direction.y = -1;
        } else if (e.key.keysym.sym == SDLK_s) {
            v.direction.y = 1;
        } else if (e.key.keysym.sym == SDLK_a) {
            v.direction.x = -1;
        } else if (e.key.keysym.sym == SDLK_d) {
            v.direction.x = 1;
        }
        this->getChildWithName("player")->setVelocity(v);
    } else if (e.type == SDL_KEYUP) {
        Velocity v = this->getChildWithName("player")->getVelocity();
        v.direction = Vector {0, 0};
        this->getChildWithName("player")->setVelocity(v);
    }
    return Scene::onInput(e);
}

void GameScene::update(float delta) { //TODO: game logic
    return;
}
