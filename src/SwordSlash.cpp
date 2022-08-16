#include "SwordSlash.h"

#include "BaseDamageable.h"

SwordSlash::SwordSlash(const Vec2f& pos, float offsetX, float offsetY, SDL_Texture* texture, BaseDamageable* wielder)
     : BaseMeleeWeapon(pos, offsetX, offsetY, texture, wielder)
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
    sword_slash_rect.x = (int)pos.x - (sword_slash_rect.w / 2);
    sword_slash_rect.y = (int)pos.y - (sword_slash_rect.h / 2);

    const SDL_RendererFlip rendererFlip = flip ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
    SDL_RenderCopyEx(renderer, texture, NULL, &sword_slash_rect, (double)0, NULL, rendererFlip);

    //SDL_RenderCopy(renderer, texture, NULL, &sword_slash_rect);
}