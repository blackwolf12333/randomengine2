#include "physics.h"

Physics::Physics(EngineNode *scene) {
    this->scene = scene;
}

Physics::~Physics() {}

void Physics::updatePhysics(float delta) {
    for (std::vector<EngineNode*>::iterator i = scene->children.begin(); i != scene->children.end(); ++i) {
        EngineNode *child = *i;
        if (child->type == NODE) {
            this->updatePhysicsForChildrenOf(delta, child);
        } else if (child->type == SPRITE) {
            updatePhysicsFor(delta, child);
        }

        // todo check collisions
        for (std::vector<EngineNode*>::iterator i2 = scene->children.begin(); i2 != scene->children.end(); ++i2) {
            EngineNode *another = *i2; // throws glass to the ground
            if (another->name == child->name) { // skip self
                continue;
            }
            RectangleBody intersection;
            bool overlap = rectanglesOverlap(child->body.rect, another->body.rect, intersection);
            if (overlap) { // TODO: now we have to do something about this collision
                printf("%f, %f, %f, %f\n", intersection.start.x, intersection.start.y, intersection.size.x, intersection.size.y);
                printf("overlap between: %s and %s\n", child->name.c_str(), another->name.c_str());
            }
        }
    }
}

void Physics::updatePhysicsForChildrenOf(float delta, EngineNode *node) {
    for (std::vector<EngineNode*>::iterator i = node->children.begin(); i != node->children.end(); ++i) {
        EngineNode *child = *i;
        if (child->type == NODE) {
            this->updatePhysicsForChildrenOf(delta, child);
        } else if (child->type == SPRITE) {
            updatePhysicsFor(delta, child);
        }
    }
}

void Physics::updatePhysicsFor(float delta, EngineNode *node) {
    Velocity velocity = node->getVelocity();
    Vector movement = velocity.direction * (velocity.magnitude * delta);
    Vector newPosition = node->getPosition() + movement;
    node->setPosition(newPosition);
}

bool Physics::rectanglesOverlap(RectangleBody b1, RectangleBody b2, RectangleBody& intersection) {
    float xmin = std::max(b1.start.x, b2.start.x);
    float xmax1 = b1.start.x + b1.size.x;
    float xmax2 = b2.start.x + b2.size.x;
    float xmax = std::min(xmax1, xmax2);
    if (xmax > xmin) {
        float ymin = std::max(b1.start.y, b2.start.y);
        float ymax1 = b1.start.y + b1.size.y;
        float ymax2 = b2.start.y + b2.size.y;
        float ymax = std::min(ymax1, ymax2);
        if (ymax > ymin) {
            intersection.start.x = 0; //xmin;
            intersection.start.y = 0; //ymin;
            intersection.size.x = xmax - xmin;
            intersection.size.y = ymax - ymin;
            return true;
        }
    }
    return false;
}