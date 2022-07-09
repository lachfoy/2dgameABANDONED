#ifndef BASEUIOBJECT_H
#define BASEUIOBJECT_H

#include <SDL2/SDL.h>

struct BaseUiObject
{
    BaseUiObject() {}
    virtual ~BaseUiObject() {}

    bool removeable = false;
    int x;
    int y;

    virtual void update(float dt) = 0;
    virtual void render(SDL_Renderer* renderer) = 0;
};

#endif