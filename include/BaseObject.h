#ifndef BASEOBJECT_H
#define BASEOBJECT_H

#include <string>

#include <SDL2/SDL.h>

class BaseObject
{
public:
    BaseObject(float x, float y) { posX = x; posY = y; }

    float posX;
    float posY;
    bool removeable = false;

    virtual void render(SDL_Renderer* renderer) = 0;

    std::string name = ""; // use for debug purposes ONLY!
};

#endif