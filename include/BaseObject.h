#ifndef BASEOBJECT_H
#define BASEOBJECT_H

#include <string>

#include <SDL2/SDL.h>

class BaseObject
{
public:
    BaseObject(float x, float y) { posX = x; posY = y; }
    ~BaseObject() { printf("deleting %s\n", name.c_str()); removable = true; }

    std::string name = ""; // use for debug purposes
    float posX;
    float posY;
    
    bool removable = false;

    virtual void render(SDL_Renderer* renderer) = 0;

    // debug
    inline void renderOrigin(SDL_Renderer* renderer);

private:
    SDL_Rect debug_origin_rect;

};

void BaseObject::renderOrigin(SDL_Renderer* renderer)
{
    // draw the origin position
    debug_origin_rect.w = 4;
    debug_origin_rect.h = 4;
    debug_origin_rect.x = (int)posX - (debug_origin_rect.w / 2);
    debug_origin_rect.y = (int)posY - (debug_origin_rect.h / 2);
    SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0x00, 0xff); // #ebd517 yellow
    SDL_RenderFillRect(renderer, &debug_origin_rect);

    // axis lines
    // SDL_SetRenderDrawColor(renderer, 0xff, 0x00, 0x00, 0xff);
    // SDL_RenderDrawLine(renderer, (int)posX, (int)posY, (int)posX + 8, (int)posY);
    // SDL_SetRenderDrawColor(renderer, 0x00, 0xff, 0x00, 0xff);
    // SDL_RenderDrawLine(renderer, (int)posX, (int)posY, (int)posX, (int)posY + 8);
}

#endif