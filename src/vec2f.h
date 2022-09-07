#ifndef VEC2F_H_
#define VEC2F_H_

class Vec2f
{
public:
    Vec2f();
    Vec2f(float x, float y);

    float x;
    float y;

    static Vec2f GetDirection(const Vec2f& a, const Vec2f& b); // get a normalized direction vector from a->b
    static float GetDistance(const Vec2f& a, const Vec2f& b); // get distance from a->b

};

#endif