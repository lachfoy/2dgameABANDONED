#ifndef BASEDAMAGEABLE_H
#define BASEDAMAGEABLE_H

#include "BaseObject.h"
#include "AABB.h"
#include "Resistance.h"

class BaseDamageable : public BaseObject
{
public:
    BaseDamageable(float x, float y);

    // getters
    inline int getHealth() const { return health; }
    inline int getMaxHealth() const { return maxHealth; }
    inline int getWidth() const { return width; }
    inline int getHeight() const { return height; }
    inline AABB const& getCollider() const { return collider; }

    void takeDamage(const Damage& damage);
    void updateBurning(float dt);
    void push(int pushVelX, int pushVelY, float pushMoveSpeed);
    void updatePush(float dt);
    void updateImmuneTimer(float dt);
    void updatePosition(float dt);

protected:
    int velX = 0;
    int velY = 0;
    int width;
    int height;
    int colliderW;
    int colliderH;
    AABB collider;
    int maxHealth;
    int health;
    bool damageable; // if not damageable then they are taking damage
    float immuneTime; // how many iframes (in seconds though)
    float immuneTimer;
    float startingMoveSpeed;
    float moveSpeed;
    enum FacingDirection { FACING_LEFT, FACING_RIGHT } facingDirection;
    Resistance resistance;

    // fire
    bool canBeSetOnFire = true;
    bool onFire = false;
    float fireTime = 3.0f; // how many seconds of fire
    float fireTimer = fireTime;
    float fireTickTime = 0.4f; // how many seconds before each tick of fire damage
    float fireTickTimer = fireTickTime;

    // push
    bool beingPushed = false;
    float pushTime = 1.0f;
    float pushTimer = pushTime;
    int pushVelX;
    int pushVelY;
    float pushMoveSpeed;

};

#endif