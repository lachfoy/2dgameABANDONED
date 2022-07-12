#ifndef BASEDAMAGEABLE_H
#define BASEDAMAGEABLE_H

#include "BaseObject.h"
#include "AABB.h"
#include "Resistance.h"

class BaseDamageable : public BaseObject
{
public:
    BaseDamageable(float x, float y);
    virtual ~BaseDamageable();

    // getters
    int getHealth() const { return health; }
    int getMaxHealth() const { return maxHealth; }
    int getWidth() const { return width; }
    int getHeight() const { return height; }
    AABB getCollider() const { return *collider; }

    void takeDamage(const Damage& damage);
    void updateBurning(float dt);
    void updateImmuneTimer(float dt);
    void updatePosition(float dt);

protected:
    int velX = 0;
    int velY = 0;
    int width;
    int height;
    int colliderW;
    int colliderH;
    AABB* collider;
    int maxHealth;
    int health;
    bool damageable; // if not damageable then they are taking damage
    float immuneTime; // how many iframes (in seconds though)
    float immuneTimer;
    float moveSpeed;
    Resistance resistance;
    enum FacingDirection { FACING_LEFT, FACING_RIGHT } facingDirection;
    bool canBeSetOnFire = true;
    bool onFire = false;
};

#endif