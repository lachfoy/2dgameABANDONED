#ifndef AABB_H
#define AABB_H

#include <SDL2/SDL.h>

//simple aabb AABB
struct AABB
{
    AABB() {}
    inline AABB(float x, float y, float w, float h);

    float upperBound[2];
    float lowerBound[2];

    static inline bool testOverlap(const AABB& a, const AABB& b); // intersecting?
    inline void debugRender(SDL_Renderer* renderer);
    inline void move(float x, float y); // not used
};

AABB::AABB(float x, float y, float w, float h)
{
    upperBound[0] = x;
    upperBound[1] = y;
    lowerBound[0] = x + w;
    lowerBound[1] = y + h;
}

// for collision response we will need to return a manifest with more information
bool AABB::testOverlap(const AABB& a, const AABB& b)
{
    float  d1X, d1Y, d2X, d2Y;
    d1X = b.upperBound[0] - a.lowerBound[0];
    d1Y = b.upperBound[1] - a.lowerBound[1];
    d2X = a.upperBound[0] - b.lowerBound[0];
    d2Y = a.upperBound[1] - b.lowerBound[1];
  
    if (d1X > 0.0f || d1Y > 0.0f)
        return false;
  
    if (d2X > 0.0f || d2Y > 0.0f)
        return false;

    return true;
}

void AABB::debugRender(SDL_Renderer* renderer)
{
    // draw a rect representing the collider
    SDL_Rect collider_rect;
    collider_rect.x = (int)upperBound[0];
    collider_rect.y = (int)upperBound[1];
    collider_rect.w = (int)(lowerBound[0] - upperBound[0]);
    collider_rect.h = (int)(lowerBound[1] - upperBound[1]);

    SDL_SetRenderDrawColor(renderer, 0xff, 0x00, 0x00, 0xff); // red
    SDL_RenderDrawRect(renderer, &collider_rect);
}

// unused
void AABB::move(float x, float y)
{
    // move the collider as well
    upperBound[0] = x;
    upperBound[1] = y;
    lowerBound[0] = x + (lowerBound[0] - upperBound[0]);
    lowerBound[1] = y + (lowerBound[1] - upperBound[1]);
}

#endif