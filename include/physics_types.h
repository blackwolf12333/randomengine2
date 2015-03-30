#ifndef PHYSICS_TYPES_H
#define PHYSICS_TYPES_H

#include "vectors.h"

typedef struct Velocity_t {
    Vector direction;
    float magnitude;
} Velocity;

typedef struct RectangleBody_t {
    Vector start;
    Vector size;
} RectangleBody;

typedef struct Body_t {
    RectangleBody rect;
    bool staticBody;
} Body;

#endif