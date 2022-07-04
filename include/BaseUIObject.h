#ifndef BASEUIOBJECT_H
#define BASEUIOBJECT_H

#include <SDL2/SDL.h>

struct BaseUIObject
{
    BaseUIObject() {}

    bool removeable = false;

    virtual void render(SDL_Renderer* renderer) = 0;
};

#endif