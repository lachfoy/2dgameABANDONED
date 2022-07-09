#include "BaseProjectile.h"

BaseProjectile::BaseProjectile(float x, float y, int velX, int velY, ProjectileManager* projectileManager)
    : BaseObject(x, y)
{
    this->velX = velX;
    this->velY = velY;

    this->projectileManager = projectileManager;
    
    collider = new AABB(posX, posY, colliderRadius, colliderRadius);
}

BaseProjectile::~BaseProjectile()
{
    delete collider;
    printf("deleted %s\n", name.c_str());
}

void BaseProjectile::updatePosition(float dt)
{
    if (lifeTime <= 0.0f) removeable = true;
    {
        // update the internal position
        posX += velX * moveSpeed * dt;
        posY += velY * moveSpeed * dt;

        // move the collider as well
        collider->upperBoundX = posX - (colliderRadius / 2);
        collider->upperBoundY = posY - (colliderRadius / 2);
        collider->lowerBoundX = posX + (colliderRadius / 2);
        collider->lowerBoundY = posY + (colliderRadius / 2);

        lifeTime -= dt;
    }
}
