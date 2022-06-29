#ifndef BASEOBJECT_H
#define BASEOBJECT_H

#include <SDL2/SDL.h>

#include "Point2f.h"

class BaseObject
{
public:
    BaseObject() { remove = false; }

    Point2f pos;
    int velX; // normalized x velocity
    int velY; // normalized y velocity
    bool remove;

    virtual void update(float dt) = 0;
    virtual void render(SDL_Renderer* renderer) = 0;
};

#endif