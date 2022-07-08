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

private:
    enum
    {
        DEFAULT_W = 30,
        DEFAULT_H = 60,
        DEFAULT_COLLIDER_W = 50,
        DEFAULT_COLLIDER_H = 50,
        DEFAULT_MAX_HEALTH = 100,
        DEFAULT_IMMUNE_TIME = 1, // float
        DEFAULT_MOVE_SPEED = 100 // float
    };

protected:
    UiManager* uiManager;
    ProjectileManager* projectileManager;

    int velX = 0;
    int velY = 0;

    int width = DEFAULT_W;
    int height = DEFAULT_H;
    int colliderW = DEFAULT_COLLIDER_W;
    int colliderH = DEFAULT_COLLIDER_H;
    AABB* collider;
    int maxHealth = DEFAULT_MAX_HEALTH;
    int health = DEFAULT_MAX_HEALTH;
    HealthBar* healthBar;
    bool damageable = true; // if not damageable then they are taking damage
    float immuneTime = (float)DEFAULT_IMMUNE_TIME; // how many iframes (in seconds though)
    float immuneTimer = (float)DEFAULT_IMMUNE_TIME;
    float moveSpeed = (float)DEFAULT_MOVE_SPEED;
};

#endif