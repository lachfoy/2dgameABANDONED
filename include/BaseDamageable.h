#ifndef BASEDAMAGEABLE_H
#define BASEDAMAGEABLE_H

#include "BaseObject.h"
#include "AABB.h"

class HealthBar;
class UIManager;
class ProjectileManager;

// create BaseDamagable class and refactor Player and BaseEnemy to inherit from this class.\
    BaseDamagable should have a concept of having health and resistances, must be able to be damaged,\
    and must have access to things like the ProjectileManager and UI Manager.
class BaseDamageable : public BaseObject
{
public:
    BaseDamageable(UIManager& _UIManager, float x, float y);
    virtual ~BaseDamageable();

    // getters
    int getHealth() const { return health; }
    int getMaxHealth() const { return maxHealth; }
    AABB getCollider() const { return *collider; }

    virtual void onCreate(UIManager& _UIManager) = 0;
    virtual void onUpdate(ProjectileManager& projectileManager, float dt) = 0; // implement by derived class

    // deals damage to this object
    void doDamage(int damage);

    void update(ProjectileManager& projectileManager, float dt);
    // void render() can be implemented by any derived class

private:
    enum
    {
        DEFAULT_COLLIDER_W = 50,
        DEFAULT_COLLIDER_H = 50,
        DEFAULT_MAX_HEALTH = 100,
        DEFAULT_IMMUNE_TIME = 1 // float
    };

protected:
    int colliderW;
    int colliderH;
    AABB* collider;
    int maxHealth;
    int health;
    HealthBar* healthBar;
    bool damageable; // if not damageable then they are taking damage
    float immuneTimer;
    float immuneTime; // how many iframes (in seconds though)
};

#endif