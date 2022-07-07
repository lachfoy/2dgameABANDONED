#ifndef BASEOBJECT_H
#define BASEOBJECT_H

#include <string>

#include <SDL2/SDL.h>

#include "Point2f.h"

struct BaseObject
{
    BaseObject(float x, float y) { pos.x = x; pos.y = y; }

    Point2f pos;
    bool removeable = false;

    virtual void update(float dt) {};
    virtual void render(SDL_Renderer* renderer) = 0;

protected:
    std::string name = ""; // use for debug purposes ONLY!
};

#endif