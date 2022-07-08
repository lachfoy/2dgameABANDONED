#ifndef BASEDAMAGEABLE_H
#define BASEDAMAGEABLE_H

#include "BaseObject.h"
#include "AABB.h"

class HealthBar;
class UiManager;
class ProjectileManager;

// create BaseDamagable class and refactor Player and BaseEnemy to inherit from this class.\
    BaseDamagable should have a concept of having health and resistances, must be able to be damaged,\
    and must have access to things like the ProjectileManager and UI Manager.
class BaseDamageable : public BaseObject
{
public:
    BaseDamageable(float x, float y, UiManager* uiManager, ProjectileManager* projectileManager);
    virtual ~BaseDamageable();

    // getters
    int getHealth() const { return health; }
    int getMaxHealth() const { return maxHealth; }
    AABB getCollider() const { return *collider; }

    void doDamage(int damage);
    void updateHealth(float dt);
    void updatePosition(float dt);

protected:
    UiManager* uiManager;
    ProjectileManager* projectileManager;

    int velX = 0;
    int velY = 0;

    int width;
    int height;
    int colliderW;
    int colliderH;
    AABB* collider;
    int maxHealth;
    int health;
    HealthBar* healthBar;
    bool damageable; // if not damageable then they are taking damage
    float immuneTime; // how many iframes (in seconds though)
    float immuneTimer;
    float moveSpeed;
};

#endif