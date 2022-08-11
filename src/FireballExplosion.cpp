#include "FireballExplosion.h"

FireballExplosion::FireballExplosion(float x, float y, SDL_Texture* texture)
    : BaseProjectile(x, y, 0, 0, texture)
{
    name = "FireballExplosion";
    colliderW = 200;
    colliderH = 200;
    damage = {0};
    damage = { .fire = 43, .setBurning = true };
    lifeTime = 0.3f;
    removeOnCollision = false;
    onlyDamageOnce = true;
}

void FireballExplosion::render(SDL_Renderer* renderer)
{
    // draw the origin position representing the actual x and y positions
    SDL_Rect fireball_explosion_rect;
    fireball_explosion_rect.w = 200;
    fireball_explosion_rect.h = 200;
    fireball_explosion_rect.x = (int)posX - (fireball_explosion_rect.w / 2);
    fireball_explosion_rect.y = (int)posY - (fireball_explosion_rect.h / 2);

    SDL_RenderCopy(renderer, texture, NULL, &fireball_explosion_rect);

    // draw collider
    //collider.debugRender(renderer);
}