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
        collider->upperBound[0] = posX - (colliderRadius / 2);
        collider->upperBound[1] = posY - (colliderRadius / 2);
        collider->lowerBound[0] = posX + (colliderRadius / 2);
        collider->lowerBound[1] = posY + (colliderRadius / 2);

        lifeTime -= dt;
    }
}
