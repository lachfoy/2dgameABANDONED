#ifndef VEC2F_H_
#define VEC2F_H_

#include <math.h>

struct Vec2f
{
    inline Vec2f() : x(0.0f), y(0.0f) {}
    inline Vec2f(float x, float y) : x(x), y(y) {}

    float x;
    float y;

    static inline Vec2f getDirection(const Vec2f& a, const Vec2f& b) // get a normalized direction vector from a->b
    {
        Vec2f dir = { b.x - a.x, b.y - a.y };
        const float dist = sqrtf((dir.x * dir.x) + (dir.y * dir.y));
        dir.x /= dist;
        dir.y /= dist;
        return dir;
    }

    static inline float getDistance(const Vec2f& a, const Vec2f& b) // get distance from a->b
    {
        const Vec2f dir = { b.x - a.x, b.y - a.y };
        return sqrtf((dir.x * dir.x) + (dir.y * dir.y));
    }

};

#endif