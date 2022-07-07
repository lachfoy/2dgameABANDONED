#include "BaseDamageable.h"

#include "UIManager.h"
#include "HealthBar.h"

BaseDamageable::BaseDamageable(float x, float y, UIManager* _UIManager, ProjectileManager* projectileManager)
    : BaseObject(x, y)
{
    // assign the references to managers
    this->_UIManager = _UIManager;
    this->projectileManager = projectileManager;

    colliderW = DEFAULT_COLLIDER_W;
    colliderH = DEFAULT_COLLIDER_H;
    collider = new AABB(pos.x, pos.y, colliderW, colliderH);

    maxHealth = DEFAULT_MAX_HEALTH;
    health = maxHealth;

    healthBar = new HealthBar();
    _UIManager->addUIObject(healthBar);

    damageable = true;
    immuneTime = 0.2f; // how many seconds of iframes
    immuneTimer = immuneTime;
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
