#ifndef AABB2I_H_
#define AABB2I_H_

#include <SDL2/SDL.h>

struct AABB2i
{
    AABB2i()
    {
        minX = 0;
        minY = 0;
        maxX = 0;
        maxY = 0;
    }

    inline AABB2i(int x, int y, int w, int h);

    int minX;
    int minY;
    int maxX;
    int maxY;

    static inline bool testOverlap(const AABB2i& a, const AABB2i& b); // intersecting?
    inline void debugRender(SDL_Renderer* renderer);

};

AABB2i::AABB2i(int x, int y, int w, int h)
{
    minX = x;
    minY = y;
    maxX = x + w;
    maxY = y + h;
}

bool AABB2i::testOverlap(const AABB2i& a, const AABB2i& b)
{
    return (a.minX <= b.maxX && a.maxX >= b.minX) &&
           (a.minY <= b.maxY && a.maxY >= b.minY);
}

void AABB2i::debugRender(SDL_Renderer* renderer)
{
    // draw a rect representing the collider
    const SDL_Rect rect = {minX, minY, (maxX - minX), (maxY - minY)};
    SDL_SetRenderDrawColor(renderer, 0xff, 0x00, 0x00, 0xff); // red
    SDL_RenderDrawRect(renderer, &rect);
}

#endif