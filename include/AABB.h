#ifndef AABB_H
#define AABB_H

#include <SDL2/SDL.h>

//simple aabb
class AABB
{
public:
    AABB() {}
    inline AABB(float x, float y, float w, float h);

    float upperBoundX = 0.0f;
    float upperBoundY = 0.0f;
    float lowerBoundX = 0.0f;
    float lowerBoundY = 0.0f;

    static inline bool testOverlap(const AABB& a, const AABB& b); // intersecting?
    inline void debugRender(SDL_Renderer* renderer);

private:
    SDL_Rect collider_debug_rect;

};

AABB::AABB(float x, float y, float w, float h)
{
    upperBoundX = x;
    upperBoundY = y;
    lowerBoundX = x + w;
    lowerBoundY = y + h;
}

// for collision response we will need to return a manifest with more information
bool AABB::testOverlap(const AABB& a, const AABB& b)
{
    float  d1X, d1Y, d2X, d2Y;
    d1X = b.upperBoundX - a.lowerBoundX;
    d1Y = b.upperBoundY - a.lowerBoundY;
    d2X = a.upperBoundX - b.lowerBoundX;
    d2Y = a.upperBoundY - b.lowerBoundY;
  
    if (d1X > 0.0f || d1Y > 0.0f)
        return false;
  
    if (d2X > 0.0f || d2Y > 0.0f)
        return false;

    return true;
}

void AABB::debugRender(SDL_Renderer* renderer)
{
    // draw a rect representing the collider
    collider_debug_rect.x = (int)upperBoundX; // have to update the x and y
    collider_debug_rect.y = (int)upperBoundY;
    collider_debug_rect.w = (int)(lowerBoundX - upperBoundX);
    collider_debug_rect.h = (int)(lowerBoundY - upperBoundY);

    SDL_SetRenderDrawColor(renderer, 0xff, 0x00, 0x00, 0xff); // red
    SDL_RenderDrawRect(renderer, &collider_debug_rect);
}

#endif