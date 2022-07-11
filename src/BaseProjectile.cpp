#include "BaseProjectile.h"

#include "BaseDamageable.h"

BaseProjectile::BaseProjectile(float x, float y, int velX, int velY, ProjectileManager* projectileManager, BaseDamageable* damageable)
    : BaseObject(x, y)
{
    this->velX = velX;
    this->velY = velY;

    this->projectileManager = projectileManager;
    this->damageable = damageable;
    
    collider = new AABB(posX, posY, colliderRadius, colliderRadius);
}

BaseProjectile::~BaseProjectile()
{
    delete collider;
    printf("deleted %s\n", name.c_str());
}

void BaseProjectile::updateLifetime(float dt)
{
    if (lifeTime <= 0.0f)
        removeable = true;
    else
        lifeTime -= dt;
}

void BaseProjectile::updatePosition(float dt)
{
    // update the internal position
    posX += velX * moveSpeed * dt;
    posY += velY * moveSpeed * dt;

    // move the collider as well
    collider->upperBoundX = posX - (colliderRadius / 2);
    collider->upperBoundY = posY - (colliderRadius / 2);
    collider->lowerBoundX = posX + (colliderRadius / 2);
    collider->lowerBoundY = posY + (colliderRadius / 2);
}
