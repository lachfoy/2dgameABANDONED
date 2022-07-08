#ifndef BASEUIOBJECT_H
#define BASEUIOBJECT_H

#include <SDL2/SDL.h>

struct BaseUiObject
{
    BaseUiObject() {}

    bool removeable = false;

    virtual void updatePosition() = 0;

    virtual void render(SDL_Renderer* renderer) = 0;
};

#endif