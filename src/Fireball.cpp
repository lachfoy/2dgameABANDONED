#include "Fireball.h"

Fireball::Fireball(float x, float y, int velX, int velY)
    : BaseProjectile(x, y, velX, velY)
{   
    colliderRadius = 24;
    moveSpeed = 220.0f;
    damage = 11;
    lifeTime = 1.6f;
}

Fireball::~Fireball()
{
    // Fireball should spawn a 'FireballExplosion' when it is destroyed
    //projectileManager->addProjectile(new FireballExplosion(pos.x, pos.y));
}

void Fireball::render(SDL_Renderer* renderer)
{
    // draw the origin position representing the actual x and y positions
    SDL_Rect debug_point_pos;
    debug_point_pos.w = 12;
    debug_point_pos.h = 12;
    debug_point_pos.x = (int)pos.x - (debug_point_pos.w / 2);
    debug_point_pos.y = (int)pos.y - (debug_point_pos.h / 2);
    SDL_SetRenderDrawColor(renderer, 0xfc, 0x90, 0x03, 0xff); // #fc9003 fire orange
    SDL_RenderFillRect(renderer, &debug_point_pos);

    // draw collider ig
    collider->debugRender(renderer);
}