#include "BaseDamageable.h"

BaseDamageable::BaseDamageable(float x, float y)
    : BaseObject(x, y)
{
    collider = new AABB(posX, posY, colliderW, colliderH);
}

BaseDamageable::~BaseDamageable()
{
    delete collider;
    printf("deleted %s\n", name.c_str());
}

void BaseDamageable::doDamage(int damage)
{
    if(damageable)
    { 
        health -= damage;
        printf("%s took %i damage\n", name.c_str(), damage);
        printf("%s has %i/%i HP\n", name.c_str(), health, maxHealth);
        damageable = false; // give iframes
    }
}

void BaseDamageable::updateImmuneTimer(float dt)
{
    if (health <= 0) { printf("%s is dead\n", name.c_str()); removeable = true; }
    else
    {
        // set up iframes
        if (!damageable) immuneTimer -= dt;
        if (immuneTimer <= 0.0f)
        {
            immuneTimer = immuneTime; // reset to the starting value
            damageable = true;
        }
    }
}

void BaseDamageable::updatePosition(float dt)
{
    // update the internal position
    posX += velX * moveSpeed * dt;
    posY += velY * moveSpeed * dt;

    // reset velocity
    velX = 0;
    velY = 0;

    // move the collider as well
    // note: origin for NPCs/players is always bottom center
    collider->upperBoundX = posX - (colliderW / 2);
    collider->upperBoundY = posY - (colliderH / 2) - (height / 2);
    collider->lowerBoundX = posX + (colliderW / 2);
    collider->lowerBoundY = posY + (colliderH / 2) - (height / 2);
}
