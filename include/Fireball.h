#ifndef FIREBALL_H
#define FIREBALL_H

#include "Projectile.h"

class Fireball : public Projectile
{
public:
    Fireball(float x, float y, int velX, int velY)
        : Projectile(x, y, velX, velY) {}

    //inline void update(float dt); // base class handles updating
    inline void render(SDL_Renderer* renderer);
};

void Fireball::render(SDL_Renderer* renderer)
{
    // draw the origin position representing the actual x and y positions
    SDL_Rect debug_point_pos;
    debug_point_pos.w = 14;
    debug_point_pos.h = 14;
    debug_point_pos.x = (int)pos.x - (debug_point_pos.w / 2);
    debug_point_pos.y = (int)pos.y - (debug_point_pos.h / 2);
    SDL_SetRenderDrawColor(renderer, 0x33, 0xe4, 0x33, 0xff); // #fc9003 fire orange
    SDL_RenderFillRect(renderer, &debug_point_pos);

    collider->debugRender(renderer);
}

#endif