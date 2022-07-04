#ifndef HEALTHBAR_H
#define HEALTHBAR_H

#include <SDL2/SDL.h>

#include "Point2f.h"

// should probably inherit from a "BaseUIObject" or something like that.
class HealthBar
{
public:
    inline HealthBar(int x, int y, int length, int height);

    Point2f pos;

    // update the healthbar internal length and height as well as the rects
    inline void updateSize(const int& length, const int& height);

    // take a current health and a max health and update the UI rects
    inline void updateHealth(const int& health, const int& maxHealth);

    inline void render(SDL_Renderer* renderer);

private:
    int length;
    int height;
    SDL_Rect bg_rect;
    SDL_Rect health_rect;

    enum
    {
        DEFAULT_LENGTH = 400,
        DEFAULT_HEIGHT = 16
    };

};

HealthBar::HealthBar(int x, int y, int length = DEFAULT_LENGTH, int height = DEFAULT_HEIGHT)
{
    pos.x = x;
    pos.y = y;
    this->length = length;
    this->height = height;

    bg_rect.x = pos.x;
    bg_rect.y = pos.y;
    bg_rect.w = length;
    bg_rect.h = height;

    health_rect.x = pos.x;
    health_rect.y = pos.y;
    health_rect.w = length;
    health_rect.h = height;
}

void HealthBar::updateSize(const int& length, const int& height)
    // if i needed the % to update I could just pass in the health and maxHealth but I don't think its necessary
{
    this->length = length;
    this->height = height;

    bg_rect.w = length;
    bg_rect.h = height;

    health_rect.w = length;
    health_rect.h = height;
}

void HealthBar::updateHealth(const int& health, const int& maxHealth)
{
    // prevent health rect from renderering a negative width
    if (health <= 0)
        health_rect.w = 0;
    else
        // update the healthbar width using the players health %
        health_rect.w = (int)(((float)health / maxHealth) * length);
}

void HealthBar::render(SDL_Renderer* renderer)
{
    // draw the bg
    SDL_SetRenderDrawColor(renderer, 0xaa, 0xaa, 0xaa, 0xff); // dark grey
    SDL_RenderFillRect(renderer, &bg_rect);

    // draw the actual health bar over the bg
    SDL_SetRenderDrawColor(renderer, 0xd1, 0x15, 0x15, 0xff); // #d11515 darkish red
    SDL_RenderFillRect(renderer, &health_rect);
}

#endif