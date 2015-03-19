#include "vectors.h"

Vector vectorAdd(Vector v1, Vector v2) {
    return Vector {v1.x + v2.x, v1.y, v2.y};
}

Vector vectorMultiply(Vector v, float value) {
    return Vector {v.x * value, v.y * value};
}
