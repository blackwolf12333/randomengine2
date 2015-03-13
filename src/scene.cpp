#include "scene.h"
#include "main.h"

void renderSprite(SDL_Renderer *renderer, SpriteNode *node);
void updatePhysicsFor(float delta, EngineNode *node);

Scene::Scene() {
    this->type = SCENE;
    this->renderer = Main::renderer;
    this->position = Point {0, 0};
}

Scene::~Scene() {}

void Scene::renderScene() {
    this->renderNode(this);
}

/*
 * Gotta love recursion
 * Loops over the children of node and checks if it should render children
 * of the child.
 */
void Scene::renderNode(EngineNode *node) {
    for (std::vector<EngineNode*>::iterator i = node->children.begin(); i != node->children.end(); ++i) {
        EngineNode *child = *i;
        if (child->hasChildren()) {
            this->renderNode(child);
        } else {
            if(child->type == SPRITE) { // we can only handle sprite nodes at the moment
                SpriteNode *sprite = (SpriteNode*)child;
                renderSprite(renderer, sprite);
                this->renderNode(sprite);
            }
        }
    }
}

void renderSprite(SDL_Renderer *renderer, SpriteNode *sprite) {
    SDL_Rect rect;
    rect.x = sprite->getParent()->getPosition().x + sprite->getPosition().x;
    rect.y = sprite->getParent()->getPosition().y + sprite->getPosition().y;
    SDL_QueryTexture(sprite->getTexture(), NULL, NULL, &rect.w, &rect.h);
    SDL_RenderCopyEx(renderer, sprite->getTexture(), NULL, &rect, 
                     sprite->getParent()->getRotation() + sprite->getRotation(),
                     NULL, SDL_FLIP_NONE);
}

void Scene::update(float delta) {
    return; // TODO: do something here? eg. actions
}

void Scene::updatePhysics(float delta) {
    this->updatePhysicsForChildrenOf(delta, this);
}

void Scene::updatePhysicsForChildrenOf(float delta, EngineNode *node) {
    for (std::vector<EngineNode*>::iterator i = node->children.begin(); i != node->children.end(); ++i) {
        EngineNode *child = *i;
        if (child->type == NODE) {
            this->updatePhysicsForChildrenOf(delta, child);
        } else if (child->type == SPRITE) {
            updatePhysicsFor(delta, child);
        }
    }
}

void updatePhysicsFor(float delta, EngineNode *node) {
    Velocity velocity = node->getVelocity();
    Point position = node->getPosition();
    float velocity_dx = velocity.direction.x * velocity.magnitude;
    float velocity_dy = velocity.direction.y * velocity.magnitude;
    float x = position.x + (velocity_dx * delta);
    float y = position.y + (velocity_dy * delta);
    printf("node: %s x: %f, y: %f delta: %f\n", node->name.c_str(), x, y, delta);
    node->setPosition(Point { x, y });
}

void Scene::onInput(SDL_Event e) {
    return;
}