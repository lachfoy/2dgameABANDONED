#ifndef FIREBALL_H
#define FIREBALL_H

#include "Projectile.h"

class Fireball : public Projectile
{
public:
    inline Fireball(float x, float y, int velX, int velY);
        
    ~Fireball(); // Fireball should spawn a 'FireballExplosion' on removal.

    //inline void update(float dt); // base class handles updating
    inline void render(SDL_Renderer* renderer);
};

Fireball::Fireball(float x, float y, int velX, int velY)
    : Projectile(x, y, velX, velY)
{   
    colliderRadius = 24;
    moveSpeed = 200.0f;
    damage = 11;
    lifeTime = 2.0f;
}

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

    // draw collider ig
    collider->debugRender(renderer);
}

// when the fireball gets removed it spawns a new projectile. How tf I do this I do not know.
class FireballExplosion : public Projectile
{
public:
    FireballExplosion(float x, float y)
        : Projectile(x, y, velX = 0, velY = 0)
    {
        
    }

    inline void render(SDL_Renderer* renderer);
};

void FireballExplosion::render(SDL_Renderer* renderer) {}

#endif