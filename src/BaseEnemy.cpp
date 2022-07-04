#include "BaseEnemy.h"

#include "HealthBar.h"

BaseEnemy::BaseEnemy(HealthBar* healthBar, float x, float y) : BaseObject(x, y)
{
    collider = new AABB(pos.x, pos.y, colliderW, colliderH);
    this->healthBar = healthBar;
    if (healthBar) healthBar->updateSize(enemyW + 26, 5);
}

BaseEnemy::~BaseEnemy()
{
    printf("Deleted enemy\n");
    delete collider;
}

void BaseEnemy::update(float dt)
{
    if (health <= 0) // if health is below zero, set removeable flag
    {
        printf("Enemy is dead\n");
        removeable = true;
        if (healthBar) healthBar->removeable = true;
    }
    else
    {
        // update the internal position
        pos.x += velX * moveSpeed * dt;
        pos.y += velY * moveSpeed * dt;

        // update the healthbar position
        if (healthBar)
        {
            healthBar->updatePos((int)pos.x, (int)pos.y - enemyH - 6);
        }

        // move the collider as well
        collider->upperBound.x = pos.x - (colliderW / 2);
        collider->upperBound.y = pos.y - (colliderH / 2) - (enemyH / 2);
        collider->lowerBound.x = pos.x + (colliderW / 2);
        collider->lowerBound.y = pos.y + (colliderH / 2) - (enemyH / 2);

        // update AI
        updateAI(dt);

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
        healthBar->updateHealth(health, maxHealth);
        printf("Enemy took %i damage\n", damage);
        printf("Enemy has %i/%i HP\n", health, maxHealth);
        damageable = false; // give iframes
    }
}
