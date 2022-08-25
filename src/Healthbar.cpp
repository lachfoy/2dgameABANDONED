#include "Healthbar.h"

#include "base_actor.h"

Healthbar::Healthbar(int x, int y, int length, int height, BaseActor* damageable)
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
    if (damageable->health() <= 0)
        removable = true;
    else
        // update the healthbar width using the players health %
        health_rect.w = (int)(((float)damageable->health() / damageable->max_health()) * length);
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