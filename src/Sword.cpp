#include "Sword.h"

#include "BaseDamageable.h"

Sword::Sword(float x, float y, float offsetX, float offsetY, BaseDamageable* damageable)
     : BaseProjectile(x, y, 0, 0, nullptr, damageable)
{
    name = "Sword";
    this->offsetX = offsetX;
    this->offsetY = offsetY;
    colliderRadius = 44;
    damage = {0};
    damage = { .standard = 11 };
    lifeTime = 0.4f;
}

Sword::~Sword() {}

void Sword::updatePosition(float dt)
{
    posX = damageable->posX + offsetX;
    posY = damageable->posY + offsetY;
    collider->upperBoundX = posX - (colliderRadius / 2);
    collider->upperBoundY = posY - (colliderRadius / 2);
    collider->lowerBoundX = posX + (colliderRadius / 2);
    collider->lowerBoundY = posY + (colliderRadius / 2);
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