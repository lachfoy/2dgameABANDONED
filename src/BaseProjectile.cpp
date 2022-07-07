#include "BaseProjectile.h"

BaseProjectile::BaseProjectile(float x, float y, int velX, int velY, ProjectileManager* projectileManager)
    : BaseObject(x, y)
{
    this->velX = velX;
    this->velY = velY;

    this->projectileManager = projectileManager;
    
    colliderRadius = DEFAULT_COLLIDER_RADIUS;
    moveSpeed = (float)DEFAULT_MOVESPEED;
    damage = DEFAULT_DAMAGE;
    lifeTime = (float)DEFAULT_LIFETIME;

    collider = new AABB(pos.x, pos.y, colliderRadius, colliderRadius);
}

BaseProjectile::~BaseProjectile()
{
    delete collider;
    printf("deleted %s\n", name.c_str());
}

void BaseProjectile::update(float dt)
{
    if (lifeTime <= 0.0f) removeable = true;
    {
        // update the internal position
        pos.x += velX * moveSpeed * dt;
        pos.y += velY * moveSpeed * dt;

        // move the collider as well
        collider->upperBound.x = pos.x - (colliderRadius / 2);
        collider->upperBound.y = pos.y - (colliderRadius / 2);
        collider->lowerBound.x = pos.x + (colliderRadius / 2);
        collider->lowerBound.y = pos.y + (colliderRadius / 2);

        lifeTime -= dt;
    }
}
