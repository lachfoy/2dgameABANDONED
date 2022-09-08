#ifndef BASE_UI_OBJECT_H_
#define BASE_UI_OBJECT_H_

#include <SDL2/SDL.h>

struct BaseUiObject
{
    BaseUiObject() {}
    virtual ~BaseUiObject() { removable = true; }

    bool removable = false;
    int x;
    int y;

    virtual void Update(float dt) = 0;
    virtual void Render(SDL_Renderer* renderer) = 0;
};

#endif