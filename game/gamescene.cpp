#include "gamescene.h"
#include "yaml_config.h"

GameScene::GameScene() {
    this->setName("mainscene");
    this->bg = new SpriteNode("texture.png", 0, 0);
    this->sp = new SpriteNode("texture2.png", 150, 0);
    this->sp->setVelocity(Velocity { Vector{1.0f, 0}, 45 });
    this->bg->setName("background");
    this->sp->setName("otherstuff");
    this->addChild(this->bg);
    this->addChild(this->sp);

    YamlConfig *yaml = new YamlConfig();
    yaml->write("test.yaml", this);
    yaml->read("test.yaml");
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