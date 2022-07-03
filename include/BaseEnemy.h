#ifndef BASEENEMY_H
#define BASEENEMY_H

#include <SDL2/SDL.h>

#include "BaseObject.h"

class AABB;

class BaseEnemy : public BaseObject
{
public:
    BaseEnemy(float x, float y);
    virtual ~BaseEnemy(); // derived enemies can add functionality

    AABB* collider;

    virtual void update(float dt); // derived enemies can add extra functionality
    virtual void render(SDL_Renderer* renderer) = 0; // derived enemies MUST provide an implementation for renderering

    int getHealth() const { return health; }
    int getMaxHealth() const { return maxHealth; }

    void doDamage(int damage);

private:
    enum
    {
        DEFAULT_W = 30,
        DEFAULT_H = 60,
        DEFAULT_COLLIDER_W = 50,
        DEFAULT_COLLIDER_H = 50,
        DEFAULT_MAX_HEALTH = 100,
        DEFAULT_IMMUNE_TIME = 1,
        DEFAULT_MOVE_SPEED = 200
    };

protected:
    int enemyW;
    int enemyH;
    int colliderW;
    int colliderH;
    int maxHealth;
    int health;
    bool damageable; // if not damageable then they are taking damage
    float immuneTimer;
    float immuneTime; // how many iframes (in seconds though)
    float moveSpeed;
};

#endif