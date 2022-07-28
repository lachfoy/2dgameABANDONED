#include "Fireball.h"

#include "ProjectileManager.h"

Fireball::Fireball(float x, float y, float velX, float velY, SDL_Texture* texture)
    : BaseProjectile(x, y, velX, velY, texture)
{
    name = "Fireball";
    colliderW = 24;
    colliderH = 24;
    moveSpeed = 350.0f;
    damage = {0};
    damage = { .fire = 11 };
    lifeTime = 0.8f;
    removeOnCollision = true;
    onlyDamageOnce = true;
}

void Fireball::destroy(ProjectileManager& projectileManager)
{
    // when destroyed, create an explosion
    projectileManager.addFireballExplosion(posX, posY);
}

void Fireball::render(SDL_Renderer* renderer)
{
    // draw the origin position representing the actual x and y positions
    SDL_Rect fireball_rect;
    fireball_rect.w = 24;
    fireball_rect.h = 24;
    fireball_rect.x = (int)posX - (fireball_rect.w / 2);
    fireball_rect.y = (int)posY - (fireball_rect.h / 2);

    // draw the fireball
    if (texture)
    {
        SDL_RenderCopy(renderer, texture, NULL, &fireball_rect);
    }
    else
    {
        SDL_SetRenderDrawColor(renderer, 0xfc, 0x90, 0x03, 0xff); // #fc9003 fire orange
        SDL_RenderFillRect(renderer, &fireball_rect);
    }

    // draw collider
    //collider.debugRender(renderer);
}