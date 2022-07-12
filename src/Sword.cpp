#include "Sword.h"

#include "BaseDamageable.h"
#include "ProjectileManager.h"

Sword::Sword(float x, float y, float offsetX, float offsetY, ProjectileManager* projectileManager, BaseDamageable* damageable)
     : BaseMeleeWeapon(x, y, offsetX, offsetY, projectileManager, damageable)
{
    name = "Sword";
    colliderW = 50;
    colliderH = 26;
    damage = {0};
    damage = { .standard = 11 };
    lifeTime = 0.1f;
}

Sword::~Sword()
{
    projectileManager->addSwordSlash(posX, posY, offsetX * 1.2f, offsetY, damageable);
}

void Sword::render(SDL_Renderer* renderer)
{
    // draw the origin position representing the actual x and y positions
    SDL_Rect sword_rect;
    sword_rect.w = 40;
    sword_rect.h = 8;
    sword_rect.x = (int)posX - (sword_rect.w / 2);
    sword_rect.y = (int)posY - (sword_rect.h / 2);
    SDL_SetRenderDrawColor(renderer, 0xe0, 0xe0, 0xe0, 0xff); // #ff6a0d more intense fire orange
    SDL_RenderFillRect(renderer, &sword_rect);

    // draw collider ig
    collider->debugRender(renderer);
}