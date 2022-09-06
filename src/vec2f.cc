#include "vec2f.h"

#include <cmath>

Vec2f::Vec2f()
{
    x = 0.0f;
    y = 0.0f;
}

Vec2f::Vec2f(float x, float y)
{
    this->x = x;
    this->y = y;
}

Vec2f Vec2f::GetDirection(const Vec2f& a, const Vec2f& b) // get a normalized direction vector from a->b
{
    Vec2f dir = { b.x - a.x, b.y - a.y };
    const float dist = sqrtf((dir.x * dir.x) + (dir.y * dir.y));
    dir.x /= dist;
    dir.y /= dist;
    return dir;
}

float GetDistance(const Vec2f& a, const Vec2f& b) // get distance from a->b
{
    const Vec2f dir = { b.x - a.x, b.y - a.y };
    return sqrtf((dir.x * dir.x) + (dir.y * dir.y));
}
