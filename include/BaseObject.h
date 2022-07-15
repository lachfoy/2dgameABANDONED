#ifndef BASEOBJECT_H
#define BASEOBJECT_H

#include <string>

#include <SDL2/SDL.h>

class BaseObject
{
public:
    BaseObject(float x, float y) { posX = x; posY = y; }
    ~BaseObject() { printf("deleted %s\n", name.c_str()); }

    float posX;
    float posY;
    
    bool const& getRemovable() const { return removable; }
    virtual void render(SDL_Renderer* renderer) = 0;

    std::string name = ""; // use for debug purposes ONLY!

protected:
    bool removable = false;

};

#endif