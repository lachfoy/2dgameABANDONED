#include "BaseEnemy.h"

#include "AABB.h"

BaseEnemy::BaseEnemy(float x, float y)
{
    // initialize everything
    pos.x = x;
    pos.y = y;
    velX = 0;
    velY = 0;

    enemyW = DEFAULT_W;
    enemyH = DEFAULT_H;
    colliderW = DEFAULT_COLLIDER_W;
    colliderH = DEFAULT_COLLIDER_H;
    collider = new AABB(pos.x, pos.y, colliderW, colliderH);
    
    maxHealth = DEFAULT_MAX_HEALTH;
    health = maxHealth;
    damageable = true;
    immuneTime = DEFAULT_IMMUNE_TIME; // how many seconds of iframes
    immuneTimer = immuneTime;

    moveSpeed = (float)DEFAULT_MOVE_SPEED;
}

BaseEnemy::~BaseEnemy()
{
    printf("Deleted enemy\n");
    delete collider;
}

void BaseEnemy::update(float dt)
{
    if (health <= 0) { printf("enemy is dieded :(\n"); removeable = true; } // if health is below zero, set removeable flag
    else
    {
        // update the internal position
        pos.x += velX * moveSpeed * dt;
        pos.y += velY * moveSpeed * dt;

        // move the collider as well
        collider->upperBound.x = pos.x - (colliderW / 2);
        collider->upperBound.y = pos.y - (colliderH / 2) - (enemyH / 2);
        collider->lowerBound.x = pos.x + (colliderW / 2);
        collider->lowerBound.y = pos.y + (colliderH / 2) - (enemyH / 2);

        // set up iframes
        if (!damageable) immuneTimer -= dt;
        if (immuneTimer <= 0.0f)
        {
            immuneTimer = immuneTime; // reset to the starting value
            damageable = true;
        }
    }
}

void BaseEnemy::doDamage(int damage)
{
    if(damageable)
    {
        health -= damage;
        printf("enemy took %i damage\n", damage);
        printf("enemy has %i/%i hp\n", health, maxHealth);
        damageable = false; // give iframes
    }
}
