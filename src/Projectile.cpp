#include "Projectile.h"

Projectile::Projectile(float x, float y, int velX, int velY)
{
    pos.x = x;
    pos.y = y;
    this->velX = velX;
    this->velY = velY;
    moveSpeed = 400.0f;

    collider = new AABB(pos.x, pos.y, 24, 24);
}

void Projectile::update(float dt)
{
    // update the internal position
    pos.x += velX * moveSpeed * dt;
    pos.y += velY * moveSpeed * dt;

    // move the collider as well
    collider->upperBound.x = pos.x - (24 / 2);
    collider->upperBound.y = pos.y - (24 / 2);
    collider->lowerBound.x = pos.x + (24 / 2);
    collider->lowerBound.y = pos.y + (24 / 2);
}

void Projectile::render(SDL_Renderer* renderer)
{
    // draw the origin position representing the actual x and y positions
    SDL_Rect debug_point_pos;
    debug_point_pos.w = 6;
    debug_point_pos.h = 6;
    debug_point_pos.x = (int)pos.x - (debug_point_pos.w / 2);
    debug_point_pos.y = (int)pos.y - (debug_point_pos.h / 2);
    SDL_SetRenderDrawColor(renderer, 0x1b, 0xf5, 0xc6, 0xff); // #1bf5c6
    SDL_RenderFillRect(renderer, &debug_point_pos);

    SDL_Color collider_color = { 0xff, 0x00, 0x00, 0xff };
    collider->debugRender(renderer, collider_color);
}