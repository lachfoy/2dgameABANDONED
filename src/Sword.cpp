#include "Sword.h"

#include "BaseActor.h"
#include "ProjectileManager.h"

Sword::Sword(const Vec2f& pos, float offsetX, float offsetY, SDL_Texture* texture, BaseActor* actor)
     : BaseMeleeWeapon(pos, offsetX, offsetY, texture, actor)
{
    name = "Sword";
    colliderW = 50;
    colliderH = 26;
    damage = {0};
    damage = { .standard = 11 };
    lifeTime = 0.1f;

    angle = -80.0f; // starting angle
    rotationSpeed = 600.0f;
}

void Sword::destroy(ProjectileManager& projectileManager)
{
    projectileManager.addSwordSlash(pos, offsetX * 1.2f, offsetY, actor);
}

void Sword::render(SDL_Renderer* renderer)
{
    // draw the origin position representing the actual x and y positions
    SDL_Rect sword_rect;
    sword_rect.w = 52;
    sword_rect.h = 28;
    sword_rect.x = (int)pos.x - (sword_rect.w / 2);
    sword_rect.y = (int)pos.y - (sword_rect.h / 2);

    // draw texture
    //SDL_RenderCopy(renderer, texture, NULL, &sword_rect);

    SDL_Point rotationOrigin;
    rotationOrigin.x = 3;
    rotationOrigin.y = sword_rect.h / 2;
    const SDL_RendererFlip rendererFlip = flip ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
    SDL_RenderCopyEx(renderer, texture, NULL, &sword_rect, angle, &rotationOrigin, rendererFlip);
}