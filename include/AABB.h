#ifndef AABB_H
#define AABB_H

#include <SDL2/SDL.h>

#include "Point2f.h"

//simple aabb AABB
struct AABB
{
    AABB() {}
    inline AABB(float x, float y, float w, float h);

    Point2f upperBound;
    Point2f lowerBound;

    static inline bool testOverlap(const AABB& a, const AABB& b); // intersecting?
    inline void debugRender(SDL_Renderer* renderer);
    inline void move(float x, float y);
};


AABB::AABB(float x, float y, float w, float h)
{
    upperBound.x = x;
    upperBound.y = y;
    lowerBound.x = x + w;
    lowerBound.y = y + h;
}

// for collision response we will need to return a manifest with more information
bool AABB::testOverlap(const AABB& a, const AABB& b)
{
    float  d1X, d1Y, d2X, d2Y;
    d1X = b.upperBound.x - a.lowerBound.x;
    d1Y = b.upperBound.y - a.lowerBound.y;
    d2X = a.upperBound.x - b.lowerBound.x;
    d2Y = a.upperBound.y - b.lowerBound.y;
  
    if (d1X > 0.0f || d1Y > 0.0f)
    {
        
        return false;
    }
  
    if (d2X > 0.0f || d2Y > 0.0f)
    {
        
        return false;
    }
  
    return true;
}

void AABB::debugRender(SDL_Renderer* renderer)
{
    // draw a rect representing the collider
    SDL_Rect collider_rect;
    collider_rect.x = (int)upperBound.x;
    collider_rect.y = (int)upperBound.y;
    collider_rect.w = (int)(lowerBound.x - upperBound.x);
    collider_rect.h = (int)(lowerBound.y - upperBound.y);

    if (false) // never atm
        SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0x00, 0xff); // yellow
    else
        SDL_SetRenderDrawColor(renderer, 0xff, 0x00, 0x00, 0xff); // red

    SDL_RenderDrawRect(renderer, &collider_rect);
}

void AABB::move(float x, float y)
{
    // move the collider as well
    upperBound.x = x;
    upperBound.y = y;
    lowerBound.x = x + (lowerBound.x - upperBound.x);
    lowerBound.y = y + (lowerBound.y - upperBound.y);
}

#endif