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
            EngineNode *another = *i2; // *throws glass to the ground*
            if (another->name == child->name) { // skip self
                continue;
            }
            RectangleBody intersection;
            bool overlap = rectanglesOverlap(child->body.rect, another->body.rect, intersection);
            if (overlap) {
                currentCollision = Collision {child->name, another->name, intersection, false};
                handleCollision(child, another, intersection);
            }
        }
    }
}

// TODO: make use of static and non-static bodies, currently all other bodies than the player are static
void Physics::handleCollision(EngineNode *node1, EngineNode *node2, RectangleBody overlap) {
    Vector move = overlap.size;
    Vector p = node1->getPosition();

    if (node1->getVelocity().direction.x != 0 && node1->getVelocity().direction.y != 0) {
        if (overlap.size.x < overlap.size.y) {
            move = overlap.size;
            if (node1->getVelocity().direction.x == 1) {
                p.x -= move.x;
            } else if (node1->getVelocity().direction.x == -1) {
                p.x += move.x;
            }
            node1->setPosition(p);

            if(rectanglesOverlap(node1->body.rect, node2->body.rect, overlap)) {
                move = overlap.size;
                if (node1->getVelocity().direction.y == 1) {
                    p.y -= move.y + 1;
                } else if (node1->getVelocity().direction.y == -1) {
                    p.y += move.y - 1;
                }
                node1->setPosition(p);
            }
        } else {
            if (node1->getVelocity().direction.y == 1) {
                p.y -= move.y + 1;
            } else if (node1->getVelocity().direction.y == -1) {
                p.y += move.y - 1;
            }
            node1->setPosition(p);

            if(rectanglesOverlap(node1->body.rect, node2->body.rect, overlap)) {
                move = overlap.size;
                if (node1->getVelocity().direction.x == 1) {
                    p.x -= move.x;
                } else if (node1->getVelocity().direction.x == -1) {
                    p.x += move.x;
                }
                node1->setPosition(p);
            }
        }
    } else {
        if (node1->getVelocity().direction.y == 1) {
            p.y -= move.y + 2;
        } else if (node1->getVelocity().direction.y == -1) {
            p.y += move.y - 1;
        } else if (node1->getVelocity().direction.y == 0) {
            // When an object collides with another object from the side
            // the move.y will be bigger than the move.x, but we will want it
            // to move on the x axis then. We only want to move on the y axis
            // when there is no move.x
            if (move.x < move.y) {
                
            }
            //p.y -= move.y + 2;
        }
        node1->setPosition(p);

        if(rectanglesOverlap(node1->body.rect, node2->body.rect, overlap)) {
            move = overlap.size;
            if (node1->getVelocity().direction.x == 1) {
                p.x -= move.x;
            } else if (node1->getVelocity().direction.x == -1) {
                p.x += move.x;
            }
            node1->setPosition(p);
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
    Vector movement = Vector {velocity.magX * delta, velocity.magY * delta};
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
            intersection.start.x = xmin;
            intersection.start.y = ymin;
            intersection.size.x = xmax - xmin;
            intersection.size.y = ymax - ymin;
            return true;
        }
    }
    return false;
}

Collision Physics::getCollision() {
    return currentCollision;
}

void Physics::resetCollision() {
    currentCollision.handled = true;
}