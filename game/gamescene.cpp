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
    if (e.type == SDL_MOUSEBUTTONDOWN) {
        float px = this->getChildWithName("otherstuff")->getPosition().x;
        float py = this->getChildWithName("otherstuff")->getPosition().y;
        float bx = (float)e.button.x;
        float by = (float)e.button.y;
        float dy = fmax(py, by) - fmin(py, by);
        float dx = fmax(px, bx) - fmin(px, bx);
        printf("dx: %f\n", dx);
        printf("dy: %f\n", dy);
        float coefficient = dy / dx;
        float rotation = DEG(atan(coefficient));
        printf("%f\n", rotation);
        Velocity v = this->getChildWithName("otherstuff")->getVelocity();
        this->getChildWithName("otherstuff")->setVelocity( Velocity{ Vector{dx, dy}, v.magnitude } );
        this->getChildWithName("otherstuff")->setRotation(rotation);
    }
    return Scene::onInput(e);
}

void GameScene::update(float delta) { //TODO: game logic
    return;
}