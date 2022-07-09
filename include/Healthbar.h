#ifndef HEALTHBAR_H
#define HEALTHBAR_H

#include <SDL2/SDL.h>

#include "BaseUiObject.h"

class BaseDamageable;

class Healthbar : public BaseUiObject
{
public:
    inline Healthbar(int x, int y, int length, int height, BaseDamageable* damageable);
    ~Healthbar() override {}

    // update the healthbar internal length and height as well as the rects
    inline void setSize(const int& length, const int& height);

    inline void updateHealth(); // take a current health and a max health and update the UI rects
    virtual void updatePosition() {} // this can be overridden by the moving healthbar variant

    inline void update(float dt) override;
    inline void render(SDL_Renderer* renderer) override;

protected:
// 20,20,400,16
    BaseDamageable* damageable; // reference to the object that will be taking damage
    int length;
    int height;
    SDL_Rect bg_rect;
    SDL_Rect health_rect;
};

#include "BaseDamageable.h"

Healthbar::Healthbar(int x, int y, int length, int height, BaseDamageable* damageable)
{
    this->x = x;
    this->x = y;

    this->length = length;
    this->height = height;

    this->damageable = damageable;

    bg_rect.x = x;
    bg_rect.y = y;
    bg_rect.w = length;
    bg_rect.h = height;

    health_rect.x = x;
    health_rect.y = y;
    health_rect.w = length;
    health_rect.h = height;
}

void Healthbar::setSize(const int& length, const int& height)
{
    this->length = length;
    this->height = height;

    bg_rect.w = length;
    bg_rect.h = height;

    health_rect.w = length;
    health_rect.h = height;
}

void Healthbar::updateHealth()
{
    // prevent health rect from renderering a negative width
    if (damageable->getHealth() <= 0)
        health_rect.w = 0;
    else
        // update the healthbar width using the players health %
        health_rect.w = (int)(((float)damageable->getHealth() / damageable->getMaxHealth()) * length);
}

void Healthbar::update(float dt)
{
    updatePosition();
    updateHealth();
}

void Healthbar::render(SDL_Renderer* renderer)
{
    // draw the bg
    SDL_SetRenderDrawColor(renderer, 0xaa, 0xaa, 0xaa, 0xff); // dark grey
    SDL_RenderFillRect(renderer, &bg_rect);

    // draw the actual health bar over the bg
    SDL_SetRenderDrawColor(renderer, 0xd1, 0x15, 0x15, 0xff); // #d11515 darkish red
    SDL_RenderFillRect(renderer, &health_rect);
}

#endif