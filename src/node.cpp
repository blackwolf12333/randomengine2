#include "node.h"

EngineNode::EngineNode() {
    this->rotation = 0.0f;
    this->velocity = {0};
    this->position = {0};
    this->parent = NULL;
    this->type = NODE;
    this->name = "";
}

EngineNode::EngineNode(const EngineNode &rhs) {
    this->rotation = rhs.rotation;
    this->velocity = rhs.velocity;
    this->position = rhs.position;
    this->parent = rhs.parent;
    this->type = rhs.type;
    this->name = rhs.name;
}

EngineNode::~EngineNode() {}

/**
 * Adds a node{child} to this nodes children.
 * It also has to set the parent of the child to this node, otherwise
 * the parent would stay NULL.
 */
void EngineNode::addChild(EngineNode *child) {
    if (child != nullptr) {
        this->children.push_back(child);
        child->parent = this;
    }
}

/**
 * Find a node with a certain name in this nodes children.
 * Through recursion we try to find a node in the children of
 * this nodes children, or their children etc.
 *
 * Returns NULL when no child with {name} is found
 */
EngineNode* EngineNode::getChildWithName(std::string name) {
    for (std::vector<EngineNode*>::iterator i = children.begin(); i != children.end(); ++i) {
        EngineNode *child = *i;
        if (child->name.compare(name) == 0) {
            return child;
        } else {
            EngineNode *n = NULL;
            if((n = child->getChildWithName(name)) != NULL) {
                return n;
            } else {
                continue;
            }
        }
    }
    return NULL;
}

bool EngineNode::hasChildren() {
    return this->children.size() != 0; // if size == 0 return false
}

EngineNode* EngineNode::getParent() {
    return this->parent;
}

Point EngineNode::getPosition() {
    return this->position;
}

float EngineNode::getRotation() {
    return this->rotation;
}

Velocity EngineNode::getVelocity() {
    return this->velocity;
}

void EngineNode::setPosition(Point position) {
    this->position = position;
}

void EngineNode::setRotation(float rotation) {
    this->rotation = rotation;
}

void EngineNode::setVelocity(Velocity velocity) {
    this->velocity = velocity;
}

void EngineNode::setName(std::string name) {
    this->name = name;
}