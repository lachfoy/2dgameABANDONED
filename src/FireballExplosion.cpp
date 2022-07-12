#include "FireballExplosion.h"

FireballExplosion::FireballExplosion(float x, float y)
    : BaseProjectile(x, y, 0, 0, nullptr, nullptr)
{
    name = "FireballExplosion";
    colliderW = 98;
    colliderH = 98;
    damage = {0};
    damage = { .fire = 43, .setBurning = true };
    lifeTime = 0.2f;
    removeOnCollision = false;
    onlyDamageOnce = false;
}

void FireballExplosion::render(SDL_Renderer* renderer)
{
    // draw the origin position representing the actual x and y positions
    SDL_Rect fireball_explosion_rect;
    fireball_explosion_rect.w = 78;
    fireball_explosion_rect.h = 78;
    fireball_explosion_rect.x = (int)posX - (fireball_explosion_rect.w / 2);
    fireball_explosion_rect.y = (int)posY - (fireball_explosion_rect.h / 2);
    SDL_SetRenderDrawColor(renderer, 0xff, 0x6a, 0x0d, 0xff); // #ff6a0d more intense fire orange
    SDL_RenderFillRect(renderer, &fireball_explosion_rect);

    // draw collider ig
    collider->debugRender(renderer);
}