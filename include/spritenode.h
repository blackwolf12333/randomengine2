#ifndef SPRITENODE_H
#define SPRITENODE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>

#include "node.h"

/**
 * Sprites are layered, the highest layer gets rendered on top of previous layers.
 * Layers are expected to be less than or equal to 0. Where layer 0 is the
 * background and other layers are drawn on top of that.
 */
class SpriteNode : public EngineNode
{
public:
    SpriteNode();
    SpriteNode(const SpriteNode &node);
    SpriteNode(std::string texture_path, Vector position);
    SpriteNode(std::string texture_path, float x, float y);
    ~SpriteNode();

    SDL_Texture *getTexture();
    std::string getTexturePath();
    void setTexturePath(std::string path);
    static SDL_Texture *loadTexture(std::string path);

    std::string texture_path;
private:
    SDL_Texture *texture;

    void init(std::string texture_path, float x, float y);
    void setupPhysicsBody();
};

#endif