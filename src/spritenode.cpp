#include "spritenode.h"
#include "main.h"

SpriteNode::SpriteNode() {
    this->type = SPRITE;
    this->name = "";
    this->rotation = 0.0f;
    this->velocity = {0};
    this->position = {0};
    this->texture = NULL;
    this->texture_path = "";
}

SpriteNode::~SpriteNode() {
    SDL_DestroyTexture(texture);
}

SpriteNode::SpriteNode(const SpriteNode& node) {
    this->type = node.type;
    this->rotation = node.rotation;
    this->velocity = node.velocity;
    this->texture = NULL;
    init(node.texture_path, node.position.x, node.position.y);
}

SpriteNode::SpriteNode(std::string texture_path, Point position) {
    init(texture_path, position.x, position.y);
}

SpriteNode::SpriteNode(std::string texture_path, float x, float y) {
    init(texture_path, x, y);
}

void SpriteNode::init(std::string texture_path, float x, float y) {
    this->type = SPRITE;

    this->texture_path = texture_path;
    this->texture = SpriteNode::loadTexture(texture_path);
    this->position = Point {x, y};

    /* Initialize physics body ->
       Default physics body will be the exact width and height
       of the texture. */
    int w, h;
    SDL_QueryTexture(texture, NULL, NULL, &w, &h);
    float width = static_cast<float>(w);
    float height = static_cast<float>(h);
    this->body = Body { position, width, height, 0, 0, 0 };
}

SDL_Texture *SpriteNode::getTexture() {
    if (this->texture == NULL) { // Try to load the texture again if it is still null at this point
        printf("Null texture: %s\n", this->texture_path.c_str());
        this->texture = SpriteNode::loadTexture(this->texture_path);
    }
    return this->texture;
}

std::string SpriteNode::getTexturePath() {
    return texture_path;
}

void SpriteNode::setTexturePath(std::string path) {
    this->texture_path = path;
}

/**
 * Load an image to an SDL_Texture*
 */
SDL_Texture *SpriteNode::loadTexture(std::string path) {
    SDL_Texture *texture = IMG_LoadTexture(Main::renderer, path.c_str());
    if (strlen(IMG_GetError()) != 0 || strlen(SDL_GetError()) != 0) {
        printf("Failed to load texture: %s\n", path.c_str());
        printf("Error: %s\n", IMG_GetError());
        printf("Error: %s\n", SDL_GetError());
        return NULL;
    }
    return texture;
}