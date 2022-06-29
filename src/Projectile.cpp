#include "Projectile.h"

Projectile::Projectile(float x, float y, int velX, int velY)
{
    pos.x = x;
    pos.y = y;
    this->velX = velX;
    this->velY = velY;
    moveSpeed = 400.0f;
    colliderW = 24;
    colliderH = 24;
    collider = new AABB(pos.x, pos.y, colliderW, colliderH);
    damage = 11;
}

void Projectile::update(float dt)
{
    // update the internal position
    pos.x += velX * moveSpeed * dt;
    pos.y += velY * moveSpeed * dt;

    // move the collider as well
    collider->upperBound.x = pos.x - (colliderW / 2);
    collider->upperBound.y = pos.y - (colliderH / 2);
    collider->lowerBound.x = pos.x + (colliderW / 2);
    collider->lowerBound.y = pos.y + (colliderH / 2);
}

void Projectile::render(SDL_Renderer* renderer)
{
    // draw the origin position representing the actual x and y positions
    SDL_Rect debug_point_pos;
    debug_point_pos.w = 14;
    debug_point_pos.h = 14;
    debug_point_pos.x = (int)pos.x - (debug_point_pos.w / 2);
    debug_point_pos.y = (int)pos.y - (debug_point_pos.h / 2);
    SDL_SetRenderDrawColor(renderer, 0xfc, 0x90, 0x03, 0xff); // #fc9003 fire orange
    SDL_RenderFillRect(renderer, &debug_point_pos);

    collider->debugRender(renderer);
}