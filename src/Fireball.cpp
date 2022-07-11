#include "Fireball.h"

#include "ProjectileManager.h"

Fireball::Fireball(float x, float y, int velX, int velY, ProjectileManager* projectileManager)
    : BaseProjectile(x, y, velX, velY, projectileManager, nullptr)
{
    name = "Fireball";
    colliderRadius = 24;
    moveSpeed = 220.0f;
    damage = {0};
    damage = { .fire = 11 };
    lifeTime = 0.8f;
}

Fireball::~Fireball()
{
    projectileManager->addFireballExplosion(posX, posY);
}

void Fireball::render(SDL_Renderer* renderer)
{
    // draw the origin position representing the actual x and y positions
    SDL_Rect debug_point_pos;
    debug_point_pos.w = 12;
    debug_point_pos.h = 12;
    debug_point_pos.x = (int)posX - (debug_point_pos.w / 2);
    debug_point_pos.y = (int)posY - (debug_point_pos.h / 2);
    SDL_SetRenderDrawColor(renderer, 0xfc, 0x90, 0x03, 0xff); // #fc9003 fire orange
    SDL_RenderFillRect(renderer, &debug_point_pos);

    // draw collider ig
    collider->debugRender(renderer);
}