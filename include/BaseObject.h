#ifndef BASEOBJECT_H
#define BASEOBJECT_H

#include <string>

#include <SDL2/SDL.h>

#include "Vec2f.h"

class BaseObject
{
public:
    inline BaseObject(float x, float y) { pos.x = x; pos.y = y; }
    inline BaseObject(const Vec2f& pos) : pos(pos) {}
    inline ~BaseObject();

    std::string name = ""; // use for debug purposes
    Vec2f pos;
    
    bool removable = false;

    virtual void render(SDL_Renderer* renderer) = 0;

    // debug
    inline void renderOrigin(SDL_Renderer* renderer);

};

BaseObject::~BaseObject()
{
    printf("deleting %s\n", name.c_str()); removable = true;
}

void BaseObject::renderOrigin(SDL_Renderer* renderer)
{
    // draw the origin position
    const int debugPointSize = 4;
    const SDL_Rect rect = { (int)pos.x - (debugPointSize / 2), (int)pos.y - (debugPointSize / 2), debugPointSize, debugPointSize };
    SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0x00, 0xff); // #ebd517 yellow
    SDL_RenderFillRect(renderer, &rect);

    // axis lines
    // SDL_SetRenderDrawColor(renderer, 0xff, 0x00, 0x00, 0xff);
    // SDL_RenderDrawLine(renderer, (int)posX, (int)posY, (int)posX + 8, (int)posY);
    // SDL_SetRenderDrawColor(renderer, 0x00, 0xff, 0x00, 0xff);
    // SDL_RenderDrawLine(renderer, (int)posX, (int)posY, (int)posX, (int)posY + 8);
}

#endif