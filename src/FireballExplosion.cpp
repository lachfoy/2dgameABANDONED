#include "FireballExplosion.h"

FireballExplosion::FireballExplosion(float x, float y, ProjectileManager* projectileManager)
    : BaseProjectile(x, y, 0, 0, projectileManager)
{
    name = "FireballExplosion";
    colliderRadius = 38;
    lifeTime = 0.2f;
    damage = { .standard = 60, .crushing = 10 };
}

void FireballExplosion::render(SDL_Renderer* renderer)
{
    // draw the origin position representing the actual x and y positions
    SDL_Rect debug_point_pos;
    debug_point_pos.w = 26;
    debug_point_pos.h = 26;
    debug_point_pos.x = (int)posX - (debug_point_pos.w / 2);
    debug_point_pos.y = (int)posY - (debug_point_pos.h / 2);
    SDL_SetRenderDrawColor(renderer, 0xff, 0x6a, 0x0d, 0xff); // #ff6a0d more intense fire orange
    SDL_RenderFillRect(renderer, &debug_point_pos);

    // draw collider ig
    collider->debugRender(renderer);
}