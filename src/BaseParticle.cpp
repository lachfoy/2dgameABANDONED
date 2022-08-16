#include "BaseParticle.h"

BaseParticle::BaseParticle(const Vec2f& pos, const Vec2f& dir, SDL_Texture* texture)
    : BaseObject(pos)
{
    this->dir.x = dir.x;
    this->dir.y = dir.y;
    this->texture = texture;
}

void BaseParticle::updateLifetime(float dt)
{
    if (lifeTime <= 0.0f)
        removable = true;
    else
        lifeTime -= dt;
}

void BaseParticle::updatePosition(float dt)
{
    // update the internal position
    pos.x += dir.x * moveSpeed * dt;
    pos.y += dir.y * moveSpeed * dt;
}
