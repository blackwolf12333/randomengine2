#ifndef PHYSICS_TYPES_H
#define PHYSICS_TYPES_H

#include "vectors.h"

typedef struct Velocity_t {
    float magX;
    float magY;

    float defaultMagnitude;

    void print() {
        printf("Velocity {size:(%f, %f) default:(%f)}\n", magX, magY, defaultMagnitude);
    }
} Velocity;

typedef struct RectangleBody_t {
    Vector start;
    Vector size;

    void print() {
        printf("RectangleBody {start:(%f,%f) size:(%f,%f)}\n", start.x, start.y, size.x, size.y);
    }
} RectangleBody;

typedef struct Body_t {
    RectangleBody rect;
    bool staticBody;

    void print() {
        printf("Body {RectangleBody {start:(%f,%f) size:(%f,%f)}, static: %d\n", rect.start.x, rect.start.y, rect.size.x, rect.size.y, staticBody);
    }
} Body;

typedef struct Collision_t {
    std::string name1;
    std::string name2;
    RectangleBody overlap;
    bool handled;

    void print() {
        printf("Collision {name1:(%s), name2(%s), overlap:(RectangleBody{start:(%f,%f) size:(%f,%f)}), handled:(%d)}\n",
                name1.c_str(), name2.c_str(), overlap.start.x, overlap.start.y, overlap.size.x, overlap.size.y, handled);    
    }
    
} Collision;

#endif