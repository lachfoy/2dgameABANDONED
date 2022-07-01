#include "Projectile.h"

Projectile::Projectile(float x, float y, int velX, int velY)
{
    pos.x = x;
    pos.y = y;
    this->velX = velX;
    this->velY = velY;
    
    colliderW = 24;
    colliderH = 24;
    
    moveSpeed = (float)DEFAULT_MOVESPEED;
    damage = DEFAULT_DAMAGE;
    lifeTime = (float)DEFAULT_LIFETIME;

    collider = new AABB(pos.x, pos.y, colliderW, colliderH);
}

Projectile::~Projectile()
{
    delete collider;
}

void Projectile::update(float dt)
{
    if (lifeTime <= 0.0f) removeable = true;
    {
        // update the internal position
        pos.x += velX * moveSpeed * dt;
        pos.y += velY * moveSpeed * dt;

        // move the collider as well
        collider->upperBound.x = pos.x - (colliderW / 2);
        collider->upperBound.y = pos.y - (colliderH / 2);
        collider->lowerBound.x = pos.x + (colliderW / 2);
        collider->lowerBound.y = pos.y + (colliderH / 2);

        lifeTime -= dt;
    }
}
