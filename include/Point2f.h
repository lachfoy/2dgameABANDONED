#ifndef POINT2F_H
#define POINT2F_H

struct Point2f
{
    Point2f() {}
    Point2f(float x, float y) : x(x), y(y) {}

    float x;
    float y;
};

#endif