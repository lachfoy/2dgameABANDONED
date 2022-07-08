#include "BaseDamageable.h"

#include "UiManager.h"
#include "HealthBar.h"

BaseDamageable::BaseDamageable(float x, float y, UiManager* uiManager, ProjectileManager* projectileManager)
    : BaseObject(x, y)
{
    // assign the references to managers
    this->uiManager = uiManager;
    this->projectileManager = projectileManager;

    collider = new AABB(pos.x, pos.y, colliderW, colliderH);

    healthBar = new HealthBar();
    uiManager->addUiObject(healthBar);
}

BaseDamageable::~BaseDamageable()
{
    delete collider;
    delete healthBar;
    printf("deleted %s\n", name.c_str());
}

void BaseDamageable::doDamage(int damage)
{
    if(damageable)
    { 
        health -= damage;
        healthBar->updateHealth(health, maxHealth);
        printf("%s took %i damage\n", name.c_str(), damage);
        printf("%s has %i/%i HP\n", name.c_str(), health, maxHealth);
        damageable = false; // give iframes
    }
}

void BaseDamageable::updateHealth(float dt)
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
    pos.x += velX * moveSpeed * dt;
    pos.y += velY * moveSpeed * dt;

    // reset velocity
    velX = 0;
    velY = 0;

    // move the collider as well
    // note: origin for NPCs/players is always bottom center
    collider->upperBound.x = pos.x - (colliderW / 2);
    collider->upperBound.y = pos.y - (colliderH / 2) - (height / 2);
    collider->lowerBound.x = pos.x + (colliderW / 2);
    collider->lowerBound.y = pos.y + (colliderH / 2) - (height / 2);
}
