#ifndef VECTORS_H
#define VECTORS_H

struct Vector {
    float x;
    float y;

    Vector(float x=0, float y=0) 
        : x(x), y(y)
    {
    }

    Vector& operator=(const Vector& a) {
        x=a.x;
        y=a.y;
        return *this;
    }

    Vector operator+(const Vector& a) const {
        return Vector(a.x+x, a.y+y);
    }

    Vector operator*(const float a) const {
        return Vector(x*a, y*a);
    }

    bool operator==(const Vector& a) const {
        return (x == a.x && y == a.y);
    }
};

#endif
