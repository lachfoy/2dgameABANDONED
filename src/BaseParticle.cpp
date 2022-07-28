#include "BaseParticle.h"

BaseParticle::BaseParticle(float x, float y, float velX, float velY, SDL_Texture* texture)
    : BaseObject(x, y)
{
    this->velX = velX;
    this->velY = velY;
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
    posX += velX * moveSpeed * dt;
    posY += velY * moveSpeed * dt;
}
