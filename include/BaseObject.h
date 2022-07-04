#ifndef BASEOBJECT_H
#define BASEOBJECT_H

#include <SDL2/SDL.h>

#include "Point2f.h"

struct BaseObject
{
    BaseObject(float x, float y) { pos.x = x; pos.y = y; }

    Point2f pos;
    int velX = 0; // normalized x velocity
    int velY = 0; // normalized y velocity
    bool removeable = false;

    virtual void update(float dt) = 0;
    virtual void render(SDL_Renderer* renderer) = 0;
};

#endif