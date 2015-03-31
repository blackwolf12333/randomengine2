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

    pause = false;
    player_size = SIZE_SMALL;
}

GameScene::~GameScene() {}

void GameScene::onInput(SDL_Event e) {
    if (pause) {
        return;
    }
    if (e.type == SDL_KEYDOWN) {
        Velocity v = this->getChildWithName("player")->getVelocity();
        if (e.key.keysym.sym == SDLK_w) {
            v.magY = -1 * v.defaultMagnitude;
        } else if (e.key.keysym.sym == SDLK_s) {
            v.magY = 1 * v.defaultMagnitude;
        } else if (e.key.keysym.sym == SDLK_a) {
            v.magX = -1 * v.defaultMagnitude;
        } else if (e.key.keysym.sym == SDLK_d) {
            v.magX = 1 * v.defaultMagnitude;
        }
        this->getChildWithName("player")->setVelocity(v);
    } else if (e.type == SDL_KEYUP) {
        Velocity v = this->getChildWithName("player")->getVelocity();
        if (e.key.keysym.sym == SDLK_w) {
            v.magY *= 0;
        } else if (e.key.keysym.sym == SDLK_s) {
            v.magY *= 0;
        } else if (e.key.keysym.sym == SDLK_a) {
            v.magX *= 0;
        } else if (e.key.keysym.sym == SDLK_d) {
            v.magX *= 0;
        }
        this->getChildWithName("player")->setVelocity(v);
    }
    return Scene::onInput(e);
}

void GameScene::fallToBits() {
    printf("BLUBLUBLBLUBL!!\n");
    deleteChild("player");
    pause = true;
}

void GameScene::grow() {
    if (player_size > 3) {
        return;
    }
    player_size += 1;
    SpriteNode *player = (SpriteNode*)getChildWithName("player");
    if(player_size == SIZE_SMALL) {
        player->setTexturePath(PLAYER_SMALL_TEXTURE);
    } else if (player_size == SIZE_MEDIUM) {
        player->setTexturePath(PLAYER_MEDIUM_TEXTURE);
    } else if (player_size >= SIZE_LARGE) {
        player->setTexturePath(PLAYER_LARGE_TEXTURE);
    }
}

void GameScene::eatJelly(std::string jelly) {
    deleteChild(jelly);
    grow();
}

int GameScene::getJellySize(std::string jelly) {
    if(jelly.compare(0, strlen("jelly_large"), "jelly_large") == 0) {
        return SIZE_LARGE;
    } else if (jelly.compare(0, strlen("jelly_medium"), "jelly_medium") == 0) {
        return SIZE_MEDIUM;
    } else if (jelly.compare(0, strlen("jelly_small"), "jelly_small") == 0) {
        return SIZE_SMALL;
    } else {
        return SIZE_LARGE; // return large if this is an error, the player should not see that
    }
}

void GameScene::collideWithJelly(std::string jelly) {
    if (getJellySize(jelly) > player_size) {
        fallToBits();
    } else {
        eatJelly(jelly);
    }
}

void GameScene::update(float delta) { //TODO: game logic
    if (!pause) {
        if (!physics->getCollision().handled) {
            if ((physics->getCollision().name1.compare("player")) == 0) {
                if (physics->getCollision().name2.compare(0, 5, "jelly") == 0) {
                    collideWithJelly(physics->getCollision().name2);
                    physics->resetCollision();
                }
            } else if (physics->getCollision().name2.compare("player") == 0) {
                if (physics->getCollision().name1.compare(0, 5, "jelly") == 0) {
                    collideWithJelly(physics->getCollision().name1);
                    physics->resetCollision();
                }
            }
        }
    }
    return;
}
