#include "SwordSlash.h"

#include "BaseDamageable.h"

SwordSlash::SwordSlash(float x, float y, float offsetX, float offsetY, SDL_Texture* texture, BaseDamageable* wielder)
     : BaseMeleeWeapon(x, y, offsetX, offsetY, texture, wielder)
{
    name = "SwordSlash";
    colliderW = 40;
    colliderH = 78;
    damage = {0};
    damage = { .standard = 16 };
    lifeTime = 0.4f;
}

void SwordSlash::render(SDL_Renderer* renderer)
{
    // draw the origin position representing the actual x and y positions
    SDL_Rect sword_slash_rect;
    sword_slash_rect.w = 54;
    sword_slash_rect.h = 86;
    sword_slash_rect.x = (int)posX - (sword_slash_rect.w / 2);
    sword_slash_rect.y = (int)posY - (sword_slash_rect.h / 2);

    SDL_RenderCopy(renderer, texture, NULL, &sword_slash_rect);

    // draw collider
    //collider.debugRender(renderer);
}