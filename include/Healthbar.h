#ifndef HEALTHBAR_H_
#define HEALTHBAR_H_

#include <SDL2/SDL.h>

#include "BaseUiObject.h"

class BaseActor;

class Healthbar : public BaseUiObject
{
public:
    Healthbar(int x, int y, int length, int height, BaseActor* damageable);

    // update the healthbar internal length and height as well as the rects
    void setSize(const int& length, const int& height);

    void updateHealth(); // take a current health and a max health and update the UI rects
    virtual void updatePosition() {} // this can be overridden by the moving healthbar variant

    void update(float dt) override;
    void render(SDL_Renderer* renderer) override;

protected:
    BaseActor* damageable; // reference to the object that will be taking damage
    int length;
    int height;
    SDL_Rect bg_rect;
    SDL_Rect health_rect;

};

#endif