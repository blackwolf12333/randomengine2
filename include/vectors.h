#ifndef VECTORS_H
#define VECTORS_H

typedef struct Vector_t {
    float x;
    float y;
} Vector;

Vector vectorAdd(Vector v1, Vector v2);
Vector vectorMultiply(Vector v, float value);

#endif
