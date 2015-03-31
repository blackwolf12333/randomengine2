#include "gamescene.h"
#include "yaml_config.h"

GameScene::GameScene(std::string file) {
    YamlConfig *yaml = new YamlConfig();
    EngineNode *scene = yaml->read(file.c_str());
    this->children = scene->children;
    this->velocity = scene->velocity;
    this->position = scene->position;
    this->rotation = scene->rotation;
    this->name = scene->name;
    this->type = scene->type;

    this->jumping = false;
    this->onground = false;
}

GameScene::~GameScene() {}

void GameScene::onInput(SDL_Event e) {
    if (e.type == SDL_KEYDOWN) {
        Velocity v = this->getChildWithName("player")->getVelocity();
        if (e.key.keysym.sym == SDLK_w) {
            v.direction.y = -1;
            onground = false;
        } else if (e.key.keysym.sym == SDLK_s) {
            v.direction.y = 1;
        } else if (e.key.keysym.sym == SDLK_a) {
            v.direction.x = -1;
        } else if (e.key.keysym.sym == SDLK_d) {
            v.direction.x = 1;
        } else if (e.key.keysym.sym == SDLK_SPACE) {
            jumping = true;
        }
        this->getChildWithName("player")->setVelocity(v);
    } else if (e.type == SDL_KEYUP) {
        Velocity v = this->getChildWithName("player")->getVelocity();
        if (e.key.keysym.sym == SDLK_w) {
            v.direction.y = 0;
        } else if (e.key.keysym.sym == SDLK_s) {
            v.direction.y = 0;
        } else if (e.key.keysym.sym == SDLK_a) {
            v.direction.x = 0;
        } else if (e.key.keysym.sym == SDLK_d) {
            v.direction.x = 0;
        }
        this->getChildWithName("player")->setVelocity(v);
    }
    return Scene::onInput(e);
}

void GameScene::update(float delta) { //TODO: game logic
    if ((physics->getCollision().name1.compare("player")) == 0 || (physics->getCollision().name2.compare("player") == 0)) {
        if (!physics->getCollision().handled) { // if we touch the ground we have to reset everything related to jumping.
            jumping = false;
            onground = true;
            physics->resetCollision();
            jumpingSpeed = 200;
            //getChildWithName("object1")->getPosition().print();
        }
    }

    if (jumping) {
        EngineNode *player = getChildWithName("player");
        Vector direction = player->getVelocity().direction;
        float velocity = player->getVelocity().magnitude;
        Vector pos = player->getPosition();
        pos.y -= (jumpingSpeed * delta);
        direction.y = jumpingSpeed < 0 ? 1 : -1;
        jumpingSpeed -= (gravity * delta)+ (pos.y/10 * delta);
        player->setPosition(pos);
        player->setVelocity(Velocity{direction, velocity});
    }
    if (!onground && !jumping) {
        EngineNode *player = getChildWithName("player");
        Vector pos = player->getPosition();
        pos.print();
        pos.y += (gravity * delta) + (pos.y / 10 * delta);
        player->setPosition(pos);
    } else if (onground && !jumping) { // still want that gravity pulling it down.
        EngineNode *player = getChildWithName("player");
        Vector direction = player->getVelocity().direction;
        float velocity = player->getVelocity().magnitude;
        Vector pos = player->getPosition();
        pos.print();
        pos.y += (gravity * delta) + (pos.y / 10 * delta);
        direction.y = 1;
        player->setPosition(pos);
        player->setVelocity(Velocity{direction, velocity});
    }
    return;
}
